;----- SUBROUTINE: plot_bitmap_8 -----
;
; PURPOSE: Plots a bitmap to the screen given by the top left pixel of the bitmap and the height of bitmap.
;
; INPUT: Address(UINT16*): to the start of the screen
;        Position(row,col): the coordinates of the top left pixel of the bitmap
;        Height: the lenth (number of rows) of the height in pixels of the bitmap
;
; OUTPUT: None
        xdef    _plot_bitmap_8
        xdef    _clip_left_top_right_bottom

SCREEN_BYTES_PER_ROW equ 80

p8_base equ     8
p8_row  equ     12
p8_col  equ     14
p8_height equ   16
p8_bitmap equ   18

lv8_x_skip equ  -2
lv8_y_skip equ  -4
lv8_visible equ -6
lv8_byte_col equ -8
lv8_bit_shift equ -10
lv8_r   equ     -12


_plot_bitmap_8:
        link    a6,#-12
        movem.l d0-d7/a0-a5,-(sp)

        ; clip_left_top_right_bottom(&row,&col,&height,8,&x_skip,&y_skip)
        lea     lv8_y_skip(a6),a0
        move.l  a0,-(sp)
        lea     lv8_x_skip(a6),a0
        move.l  a0,-(sp)
        move.w  #8,-(sp)
        lea     p8_height(a6),a0
        move.l  a0,-(sp)
        lea     p8_col(a6),a0
        move.l  a0,-(sp)
        lea     p8_row(a6),a0
        move.l  a0,-(sp)

        jsr     _clip_left_top_right_bottom
        adda.l  #22,sp

        tst.w   d0
        beq     p8_done

        move.w  d0,lv8_visible(a6)

        ; bitmap += y_skip
        movea.l p8_bitmap(a6),a1
        move.w  lv8_y_skip(a6),d0
        ext.l   d0
        adda.l  d0,a1
        move.l  a1,p8_bitmap(a6)

        ; byte_col = col >> 3
        ; bit_shift = col & 7
        move.w  p8_col(a6),d0
        move.w  d0,d1
        lsr.w   #3,d0
        move.w  d0,lv8_byte_col(a6)
        andi.w  #7,d1
        move.w  d1,lv8_bit_shift(a6)

        clr.w   lv8_r(a6)

p8_row_loop:
        move.w  lv8_r(a6),d0
        cmp.w   p8_height(a6),d0
        bge     p8_done

        ; dest = base8 + (row+r)*80 + byte_col
        move.w  p8_row(a6),d1
        add.w   lv8_r(a6),d1
        ext.l   d1
        mulu.w  #SCREEN_BYTES_PER_ROW,d1

        move.w  lv8_byte_col(a6),d2
        ext.l   d2
        add.l   d2,d1

        movea.l p8_base(a6),a0
        adda.l  d1,a0

        ; src = bitmap[r]
        movea.l p8_bitmap(a6),a1
        move.w  lv8_r(a6),d0
        ext.l   d0
        move.b  0(a1,d0.l),d3

        ; left clipping
        move.w  lv8_x_skip(a6),d4
        tst.w   d4
        beq.s   p8_right_clip
        lsl.b   d4,d3

p8_right_clip:
        ; if (visible < 8 - x_skip) mask right side
        move.w  #8,d5
        sub.w   d4,d5
        move.w  lv8_visible(a6),d6
        cmp.w   d5,d6
        bge.s   p8_do_print

        move.w  #8,d7
        sub.w   d6,d7
        moveq   #-1,d5
        lsr.b   d7,d5
        lsl.b   d7,d5
        and.b   d5,d3

p8_do_print:
        move.w  lv8_bit_shift(a6),d6
        tst.w   d6
        bne.s   p8_unaligned

        or.b    d3,(a0)
        bra.s   p8_next_row

p8_unaligned:
        move.b  d3,d7
        lsr.b   d6,d7
        or.b    d7,(a0)

        move.w  lv8_visible(a6),d7
        add.w   d6,d7
        cmp.w   #8,d7
        ble.s   p8_next_row

        move.w  lv8_byte_col(a6),d7
        addq.w  #1,d7
        cmp.w   #SCREEN_BYTES_PER_ROW,d7
        bge.s   p8_next_row

        move.w  #8,d7
        sub.w   d6,d7
        move.b  d3,d6
        lsl.b   d7,d6
        or.b    d6,1(a0)

p8_next_row:
        addq.w  #1,lv8_r(a6)
        bra     p8_row_loop

p8_done:
        movem.l (sp)+,d0-d7/a0-a5
        unlk    a6
        rts

        
