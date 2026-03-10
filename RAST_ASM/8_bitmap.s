		xref    plot_bitmap_8
        xref    clip_left_top_right_bottom

SCREEN_BYTES_PER_ROW    equ     80

pb_base         equ     8
pb_row          equ     12
pb_col          equ     14
pb_height       equ     16
pb_bitmap       equ     18

lv_x_skip       equ     -2
lv_y_skip       equ     -4
lv_visible      equ     -6
lv_byte_col     equ     -8
lv_bit_shift    equ     -10
lv_r            equ     -12

        text

plot_bitmap_8:
        link    a6,#-12
        movem.l d0-d7/a0-a5,-(sp)

        lea     lv_y_skip(a6),a0
        move.l  a0,-(sp)
        lea     lv_x_skip(a6),a0
        move.l  a0,-(sp)
        move.w  #8,-(sp)
        lea     pb_height(a6),a0
        move.l  a0,-(sp)
        lea     pb_col(a6),a0
        move.l  a0,-(sp)
        lea     pb_row(a6),a0
        move.l  a0,-(sp)

        jsr     clip_left_top_right_bottom
        adda.l  #22,sp

        tst.w   d0
        beq     pb_done

        move.w  d0,lv_visible(a6)

        movea.l pb_bitmap(a6),a1
        move.w  lv_y_skip(a6),d0
        ext.l   d0
        adda.l  d0,a1
        move.l  a1,pb_bitmap(a6)

        move.w  pb_col(a6),d0
        move.w  d0,d1
        lsr.w   #3,d0
        move.w  d0,lv_byte_col(a6)
        andi.w  #7,d1
        move.w  d1,lv_bit_shift(a6)

        clr.w   lv_r(a6)

row_loop:
        move.w  lv_r(a6),d0
        cmp.w   pb_height(a6),d0
        bge     pb_done

        move.w  pb_row(a6),d1
        add.w   lv_r(a6),d1
        ext.l   d1
        mulu.w  #SCREEN_BYTES_PER_ROW,d1
        move.w  lv_byte_col(a6),d2
        ext.l   d2
        add.l   d2,d1

        movea.l pb_base(a6),a0
        adda.l  d1,a0

        movea.l pb_bitmap(a6),a1
        move.w  lv_r(a6),d0
        ext.l   d0
        move.b  0(a1,d0.l),d3

        move.w  lv_x_skip(a6),d4
        tst.w   d4
        beq     check_right_clip
        lsl.b   d4,d3

check_right_clip:
        move.w  lv_visible(a6),d5
        move.w  #8,d6
        sub.w   d4,d6
        cmp.w   d6,d5
        bge     do_print
        move.w  #8,d6
        sub.w   d5,d6
        move.b  #$FF,d7
        lsl.b   d6,d7
        and.b   d7,d3

do_print:
        move.w  lv_bit_shift(a6),d6
        tst.w   d6
        bne     unaligned_print

        or.b    d3,(a0)
        bra     next_row

unaligned_print:
        move.b  d3,d7
        lsr.b   d6,d7
        or.b    d7,(a0)

        move.w  lv_visible(a6),d7
        add.w   d6,d7
        cmp.w   #8,d7
        ble     next_row

        move.w  lv_byte_col(a6),d7
        addq.w  #1,d7
        cmp.w   #SCREEN_BYTES_PER_ROW,d7
        bge     next_row

        move.w  #8,d7
        sub.w   d6,d7
        move.b  d3,d6
        lsl.b   d7,d6
        or.b    d6,1(a0)

next_row:
        addq.w  #1,lv_r(a6)
        bra     row_loop

pb_done:
        movem.l (sp)+,d0-d7/a0-a5
        unlk    a6
        rts

        data
        even
smiley:
        dc.b    $3C     ; 00111100
        dc.b    $42     ; 01000010
        dc.b    $A5     ; 10100101
        dc.b    $81     ; 10000001
        dc.b    $A5     ; 10100101
        dc.b    $99     ; 10011001
        dc.b    $66     ; 01100110
        dc.b    $3C     ; 00111100

        even
screen_base:
        dc.l    0

        end     start