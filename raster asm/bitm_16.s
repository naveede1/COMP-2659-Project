;----- SUBROUTINE: plot_bitmap_16 -----
;
; PURPOSE: Plots a bitmap to the screen given by the top left pixel of the bitmap and the height of bitmap.
;
; INPUT: Address(UINT16*): to the start of the screen
;        Position(row,col): the coordinates of the top left pixel of the bitmap
;        Height: the lenth (number of rows) of the height in pixels of the bitmap
;
; OUTPUT: None
      
        xdef    _clip_left_top_right_bottom
        xdef    _plot_bitmap_16

SCREEN_WORDS_PER_ROW equ 40

;----------------------------------------------------------------
; plot16 stack offsets
;----------------------------------------------------------------
p16_base equ    8
p16_row equ     12
p16_col equ     14
p16_height equ  16
p16_bitmap equ  18

;----------------------------------------------------------------
; plot16 local variables
;----------------------------------------------------------------
lv16_x_skip equ -2
lv16_y_skip equ -4
lv16_visible equ -6
lv16_word_col equ -8
lv16_bit_shift equ -10
lv16_r  equ     -12


_plot_bitmap_16:
        link    a6,#-12
        movem.l d0-d7/a0-a5,-(sp)

        lea     lv16_y_skip(a6),a0
        move.l  a0,-(sp)                        ; y_skip  
        lea     lv16_x_skip(a6),a0
        move.l  a0,-(sp)                        ; x_skip
        move.w  #16,-(sp)                       ; sprite_width
        lea     p16_height(a6),a0
        move.l  a0,-(sp)                        ; height
        lea     p16_col(a6),a0
        move.l  a0,-(sp)                        ; col
        lea     p16_row(a6),a0
        move.l  a0,-(sp)                        ; row     
        jsr     _clip_left_top_right_bottom
        adda.l  #22,sp

        tst.w   d0
        beq     p16_done

        move.w  d0,lv16_visible(a6)

        movea.l p16_bitmap(a6),a1
        move.w  lv16_y_skip(a6),d0
        ext.l   d0
        lsl.l   #1,d0
        adda.l  d0,a1
        move.l  a1,p16_bitmap(a6)

        move.w  p16_col(a6),d0
        move.w  d0,d1
        lsr.w   #4,d0
        move.w  d0,lv16_word_col(a6)
        andi.w  #15,d1
        move.w  d1,lv16_bit_shift(a6)

        clr.w   lv16_r(a6)

p16_row_loop:
        move.w  lv16_r(a6),d0
        cmp.w   p16_height(a6),d0
        bge     p16_done

        move.w  p16_row(a6),d1
        add.w   lv16_r(a6),d1
        ext.l   d1
        mulu.w  #SCREEN_WORDS_PER_ROW,d1
        move.w  lv16_word_col(a6),d2
        ext.l   d2
        add.l   d2,d1
        lsl.l   #1,d1

        movea.l p16_base(a6),a0
        adda.l  d1,a0

        movea.l p16_bitmap(a6),a1
        move.w  lv16_r(a6),d0
        ext.l   d0
        lsl.l   #1,d0
        move.w  0(a1,d0.l),d3

        move.w  lv16_x_skip(a6),d4
        tst.w   d4
        beq.s   p16_right_clip
        lsl.w   d4,d3

p16_right_clip:
        move.w  lv16_visible(a6),d5
        move.w  #16,d6
        sub.w   d4,d6
        cmp.w   d6,d5
        bge.s   p16_do_print
        move.w  #16,d6
        sub.w   d5,d6
        move.w  #-1,d7
        lsl.w   d6,d7
        and.w   d7,d3

p16_do_print:
        move.w  lv16_bit_shift(a6),d6
        tst.w   d6
        bne.s   p16_unaligned

        or.w    d3,(a0)
        bra.s   p16_next_row

p16_unaligned:
        move.w  d3,d7
        lsr.w   d6,d7
        or.w    d7,(a0)

        move.w  lv16_visible(a6),d7
        add.w   d6,d7
        cmp.w   #16,d7
        ble.s   p16_next_row

        move.w  lv16_word_col(a6),d7
        addq.w  #1,d7
        cmp.w   #SCREEN_WORDS_PER_ROW,d7
        bge.s   p16_next_row

        move.w  #16,d7
        sub.w   d6,d7
        move.w  d3,d6
        lsl.w   d7,d6
        or.w    d6,2(a0)

p16_next_row:
        addq.w  #1,lv16_r(a6)
        bra     p16_row_loop

p16_done:
        movem.l (sp)+,d0-d7/a0-a5
        unlk    a6
        rts
