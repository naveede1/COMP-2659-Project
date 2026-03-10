SCREEN_HEIGHT           equ     400
SCREEN_WIDTH            equ     640
SCREEN_BYTES_PER_ROW    equ     80
SCREEN_WORDS_PER_ROW    equ     40

p8_base         equ     8
p8_row          equ     12
p8_col          equ     14
p8_height       equ     16
p8_bitmap       equ     18

lv8_x_skip      equ     -2
lv8_y_skip      equ     -4
lv8_visible     equ     -6
lv8_byte_col    equ     -8
lv8_bit_shift   equ     -10
lv8_r           equ     -12


;----------------------------------------------------------------
; clip offsets
;----------------------------------------------------------------
row_ptr         equ     8
col_ptr         equ     12
height_ptr      equ     16
sprite_width    equ     20
x_skip_ptr      equ     22
y_skip_ptr      equ     26

;----------------------------------------------------------------
; plot16 stack offsets
;----------------------------------------------------------------
p16_base        equ     8
p16_row         equ     12
p16_col         equ     14
p16_height      equ     16
p16_bitmap      equ     18

;----------------------------------------------------------------
; plot16 local variables
;----------------------------------------------------------------
lv16_x_skip     equ     -2
lv16_y_skip     equ     -4
lv16_visible    equ     -6
lv16_word_col   equ     -8
lv16_bit_shift  equ     -10
lv16_r          equ     -12

;----------------------------------------------------------------
; plot32 stack offsets
;----------------------------------------------------------------
p32_base        equ     8
p32_row         equ     12
p32_col         equ     14
p32_height      equ     16
p32_bitmap      equ     18

;----------------------------------------------------------------
; plot32 local variables
;----------------------------------------------------------------
lv32_x_skip     equ     -2
lv32_y_skip     equ     -4
lv32_visible    equ     -6
lv32_byte_col   equ     -8
lv32_bit_shift  equ     -10
lv32_r          equ     -12

        text

;================================================================
; ENTRY POINT
;================================================================
start:
        move.w  #3,-(sp)
        trap    #14
        addq.l  #2,sp
        move.l  d0,screen_base

        movea.l d0,a0
        move.w  #8000-1,d1
clear_loop:
        clr.l   (a0)+
        dbra    d1,clear_loop

        ; plot_bitmap_32(base,row,col,height,bitmap)
        ; push right-to-left: bitmap, height, col, row, base
        move.l  #block_bitmap,-(sp)
        move.w  #32,-(sp)
        move.w  #200,-(sp)
        move.w  #150,-(sp)
        move.l  screen_base,-(sp)
        jsr     plot_bitmap_32
        adda.l  #14,sp

        move.l  #2000000,d0
delay:
        subq.l  #1,d0
        bne     delay

        clr.w   -(sp)
        move.w  #$4c,-(sp)
        trap    #1

;================================================================
; clip_left_top_right_bottom
;================================================================
clip_left_top_right_bottom:
        link    a6,#0
        movem.l d1-d7/a0-a4,-(sp)

        movea.l row_ptr(a6),a0
        movea.l col_ptr(a6),a1
        movea.l height_ptr(a6),a2
        movea.l x_skip_ptr(a6),a3
        movea.l y_skip_ptr(a6),a4

        move.w  (a0),d0
        move.w  (a1),d1
        move.w  (a2),d2

        clr.w   (a3)
        clr.w   (a4)

        tst.w   d0
        bge.s   check_bottom
        move.w  d0,d3
        neg.w   d3
        cmp.w   d2,d3
        bge.s   return_zero
        move.w  d3,(a4)
        sub.w   d3,d2
        move.w  d2,(a2)
        clr.w   d0

check_bottom:
        cmp.w   #SCREEN_HEIGHT,d0
        bge.s   return_zero
        move.w  d0,d3
        add.w   d2,d3
        cmp.w   #SCREEN_HEIGHT,d3
        ble.s   check_left
        move.w  #SCREEN_HEIGHT,d2
        sub.w   d0,d2
        move.w  d2,(a2)

check_left:
        tst.w   d1
        bge.s   check_right
        move.w  d1,d3
        neg.w   d3
        move.w  sprite_width(a6),d4
        cmp.w   d4,d3
        bge.s   return_zero
        move.w  d3,(a3)
        clr.w   d1

check_right:
        cmp.w   #SCREEN_WIDTH,d1
        bge.s   return_zero

        move.w  #SCREEN_WIDTH,d3
        sub.w   d1,d3
        move.w  sprite_width(a6),d4
        move.w  (a3),d5
        sub.w   d5,d4
        cmp.w   d4,d3
        ble.s   write_back
        move.w  d4,d3

write_back:
        move.w  d0,(a0)
        move.w  d1,(a1)
        move.w  d2,(a2)
        move.w  d3,d0
        bra.s   clip_done

return_zero:
        clr.w   d0

clip_done:
        movem.l (sp)+,d1-d7/a0-a4
        unlk    a6
        rts

plot_bitmap_8:
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

        jsr     clip_left_top_right_bottom
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

;================================================================
; plot_bitmap_16
;================================================================
plot_bitmap_16:
        link    a6,#-12
        movem.l d0-d7/a0-a5,-(sp)

        lea     lv16_y_skip(a6),a0
        move.l  a0,-(sp)
        lea     lv16_x_skip(a6),a0
        move.l  a0,-(sp)
        move.w  #16,-(sp)
        lea     p16_height(a6),a0
        move.l  a0,-(sp)
        lea     p16_col(a6),a0
        move.l  a0,-(sp)
        lea     p16_row(a6),a0
        move.l  a0,-(sp)

        jsr     clip_left_top_right_bottom
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
        move.w  #$FFFF,d7
        lsr.w   d6,d7
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

;================================================================
; plot_bitmap_32
;================================================================
plot_bitmap_32:
        link    a6,#-12
        movem.l d0-d7/a0-a5,-(sp)

        ; clip_left_top_right_bottom(&row,&col,&height,32,&x_skip,&y_skip)
        lea     lv32_y_skip(a6),a0
        move.l  a0,-(sp)
        lea     lv32_x_skip(a6),a0
        move.l  a0,-(sp)
        move.w  #32,-(sp)
        lea     p32_height(a6),a0
        move.l  a0,-(sp)
        lea     p32_col(a6),a0
        move.l  a0,-(sp)
        lea     p32_row(a6),a0
        move.l  a0,-(sp)

        jsr     clip_left_top_right_bottom
        adda.l  #22,sp

        tst.w   d0
        beq     p32_done

        move.w  d0,lv32_visible(a6)

        ; bitmap += y_skip
        movea.l p32_bitmap(a6),a1
        move.w  lv32_y_skip(a6),d0
        ext.l   d0
        lsl.l   #2,d0
        adda.l  d0,a1
        move.l  a1,p32_bitmap(a6)

        ; byte_col = col >> 3
        ; bit_shift = col & 7
        move.w  p32_col(a6),d0
        move.w  d0,d1
        lsr.w   #3,d0
        move.w  d0,lv32_byte_col(a6)
        andi.w  #7,d1
        move.w  d1,lv32_bit_shift(a6)

        clr.w   lv32_r(a6)

p32_row_loop:
        move.w  lv32_r(a6),d0
        cmp.w   p32_height(a6),d0
        bge     p32_done

        ; dest = base8 + (row+r)*80 + byte_col
        move.w  p32_row(a6),d1
        add.w   lv32_r(a6),d1
        ext.l   d1
        mulu.w  #SCREEN_BYTES_PER_ROW,d1

        move.w  lv32_byte_col(a6),d2
        ext.l   d2
        add.l   d2,d1

        movea.l p32_base(a6),a0
        adda.l  d1,a0

        ; src = bitmap[r]
        movea.l p32_bitmap(a6),a1
        move.w  lv32_r(a6),d0
        ext.l   d0
        lsl.l   #2,d0
        move.l  0(a1,d0.l),d3

        ; left clipping
        move.w  lv32_x_skip(a6),d4
        tst.w   d4
        beq.s   p32_right_clip
        lsl.l   d4,d3

p32_right_clip:
        ; if (visible < 32 - x_skip) then mask off right side
        move.w  #32,d5
        sub.w   d4,d5
        move.w  lv32_visible(a6),d6
        cmp.w   d5,d6
        bge.s   p32_do_bytes

        move.w  #32,d7
        sub.w   d6,d7
        moveq   #-1,d5
        lsr.l   d7,d5
        lsl.l   d7,d5
        and.l   d5,d3

p32_do_bytes:
        move.l  d3,d4
        lsr.l   #24,d4              ; b0

        move.l  d3,d5
        lsr.l   #16,d5              ; b1

        move.l  d3,d6
        lsr.l   #8,d6               ; b2

        move.l  d3,d7               ; b3

        move.w  lv32_bit_shift(a6),d0
        tst.w   d0
        bne.s   p32_unaligned

        or.b    d4,(a0)
        or.b    d5,1(a0)
        or.b    d6,2(a0)
        or.b    d7,3(a0)
        bra     p32_next_row

p32_unaligned:
        move.l  d4,d1
        lsr.l   d0,d1
        or.b    d1,(a0)

        moveq   #8,d2
        sub.w   d0,d2
        move.l  d4,d1
        lsl.l   d2,d1
        move.l  d5,d3
        lsr.l   d0,d3
        or.l    d3,d1
        or.b    d1,1(a0)

        moveq   #8,d2
        sub.w   d0,d2
        move.l  d5,d1
        lsl.l   d2,d1
        move.l  d6,d3
        lsr.l   d0,d3
        or.l    d3,d1
        or.b    d1,2(a0)

        moveq   #8,d2
        sub.w   d0,d2
        move.l  d6,d1
        lsl.l   d2,d1
        move.l  d7,d3
        lsr.l   d0,d3
        or.l    d3,d1
        or.b    d1,3(a0)

        ; overflow byte
        move.w  lv32_visible(a6),d1
        add.w   lv32_bit_shift(a6),d1
        cmp.w   #32,d1
        ble.s   p32_next_row

        move.w  lv32_byte_col(a6),d1
        addq.w  #4,d1
        cmp.w   #SCREEN_BYTES_PER_ROW,d1
        bge.s   p32_next_row

        moveq   #8,d2
        sub.w   d0,d2
        move.l  d7,d1
        lsl.l   d2,d1
        or.b    d1,4(a0)

p32_next_row:
        addq.w  #1,lv32_r(a6)
        bra     p32_row_loop

p32_done:
        movem.l (sp)+,d0-d7/a0-a5
        unlk    a6
        rts

;================================================================
;================================================================
; 8x8 bitmap data
;================================================================
		data
smiley_bitmap:
        dc.b    %00111100
        dc.b    %01000010
        dc.b    %10100101
        dc.b    %10000001
        dc.b    %10100101
        dc.b    %10011001
        dc.b    
        dc.b    
        even
 
invader: 
		dc.w $0000 
		dc.w $0810 
		dc.w $0810 
		dc.w $0420 
		dc.w $0240 
		dc.w $1FF8 
		dc.w $2004 
		dc.w $4662 
		dc.w $4002 
		dc.w $43C2 
		dc.w $2424 
		dc.w $1008 
		dc.w $0FF0 
		dc.w $0240 
		dc.w $0E70 
		dc.w $0000  

	   data
        even

screen_base:
        dc.l    0

block_bitmap:
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF
        dc.l    $FFFFFFFF

        end     start