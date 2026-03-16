;----- SUBROUTINE: plot_bitmap_32 -----
;
; PURPOSE: Plots a bitmap to the screen given by the top left pixel of the bitmap and the height of bitmap.
;
; INPUT: Address(UINT32*): to the start of the screen
;        Position(row,col): the coordinates of the top left pixel of the bitmap
;        Height: the lenth (number of rows) of the height in pixels of the bitmap
;
; OUTPUT: None

        xdef    _plot_bitmap_32
        xdef    _clip_left_top_right_bottom

SCREEN_BYTES_PER_ROW    equ     80

; plot32 stack offsets 
p32_base 		equ     8
p32_row         equ     12
p32_col         equ     14
p32_height      equ     16
p32_bitmap      equ     18

lv32_x_skip     equ     -2
lv32_y_skip     equ     -4
lv32_visible    equ     -6
lv32_byte_col   equ     -8
lv32_bit_shift  equ     -10
lv32_r          equ     -12

_plot_bitmap_32:
        link    a6,#-12                        
        movem.l d0-d7/a0-a5,-(sp)              

        ; Call clip_left_top_right_bottom(&row, &col, &height,
        ;                                 sprite_width, &x_skip, &y_skip)
        lea     lv32_y_skip(a6),a0
        move.l  a0,-(sp)                        ; y_skip  
        lea     lv32_x_skip(a6),a0
        move.l  a0,-(sp)                        ; x_skip
        move.w  #32,-(sp)                       ; sprite_width = 32
        lea     p32_height(a6),a0
        move.l  a0,-(sp)                        ; height
        lea     p32_col(a6),a0
        move.l  a0,-(sp)                        ; col
        lea     p32_row(a6),a0
        move.l  a0,-(sp)                        ; row     
        jsr     _clip_left_top_right_bottom
        adda.l  #22,sp                          

        tst.w   d0                              ; if visible == 0, nothing to draw
        beq     p32_done

        move.w  d0,lv32_visible(a6)             ; save visible width

        movea.l p32_bitmap(a6),a1
        move.w  lv32_y_skip(a6),d0
        ext.l   d0                              ; sign extend to long
        lsl.l   #2,d0                           ; multiply by 4
        adda.l  d0,a1                           ; advance by y_skip rows
        move.l  a1,p32_bitmap(a6)               

        ;   byte_col  = col >> 3  
        ;   bit_shift = col & 7   
        move.w  p32_col(a6),d0
        move.w  d0,d1
        lsr.w   #3,d0
        move.w  d0,lv32_byte_col(a6)            ; save byte column
        andi.w  #7,d1
        move.w  d1,lv32_bit_shift(a6)           ; save bit shift

        clr.w   lv32_r(a6)                      ; r = 0, start of row loop

p32_row_loop:
        move.w  lv32_r(a6),d0
        cmp.w   p32_height(a6),d0              ; if r >= height, we are done
        bge     p32_done

        ;   offset = (row + r) * SCREEN_BYTES_PER_ROW + byte_col
        move.w  p32_row(a6),d1
        add.w   lv32_r(a6),d1                  ; d1 = row + r
        ext.l   d1
        mulu.w  #SCREEN_BYTES_PER_ROW,d1       ; d1 = (row + r) * 80
        move.w  lv32_byte_col(a6),d2
        ext.l   d2
        add.l   d2,d1                          ; d1 = byte offset into screen

        movea.l p32_base(a6),a0
        adda.l  d1,a0                          

        movea.l p32_bitmap(a6),a1
        move.w  lv32_r(a6),d0
        ext.l   d0
        lsl.l   #2,d0                          ; multiply by 4 (bytes per longword)
        move.l  0(a1,d0.l),d3                  ; d3 = bitmap[r]

        move.w  lv32_x_skip(a6),d4
        tst.w   d4
        beq.s   p32_right_clip                 ; no left clip needed
        lsl.l   d4,d3                          ; shift out clipped left bits

p32_right_clip:
        move.w  #32,d5
        sub.w   d4,d5                          ; d5 = 32 - x_skip (unclipped width)
        move.w  lv32_visible(a6),d6
        cmp.w   d5,d6                          ; if visible >= unclipped width, no right clip
        bge.s   p32_do_bytes
        move.w  #32,d7
        sub.w   d6,d7                          ; d7 = 32 - visible (bits to mask off)
        moveq   #-1,d5                         
        lsr.l   d7,d5
        lsl.l   d7,d5                          ; to keep visible bits
        and.l   d5,d3                          ; zero out right clipped bits

p32_do_bytes:
        move.l  d3,d4
        lsr.l   #8,d4
        lsr.l   #8,d4
        lsr.l   #8,d4                          ; d4 = b0 (bits 31-24)

        move.l  d3,d5
        lsr.l   #8,d5
        lsr.l   #8,d5                          ; d5 = b1 (bits 23-16)

        move.l  d3,d6
        lsr.l   #8,d6                          ; d6 = b2 (bits 15-8)

        move.l  d3,d7                          ; d7 = b3 (bits 7-0)

        move.w  lv32_bit_shift(a6),d0		   ; If bit_shift ==0: byte aligned or  
        tst.w   d0
        bne.s   p32_unaligned

        or.b    d4,(a0)                        ; aligned: OR all 4 bytes directly
        or.b    d5,1(a0)
        or.b    d6,2(a0)
        or.b    d7,3(a0)
        bra     p32_next_row

p32_unaligned:
        ;----------------------------------------------------------
        ; Each source byte is split across two destination bytes
        ; high part = src >> bit_shift  ORed into dest[n]
        ; low part  = src << (8 - bit_shift) ORed into dest[n+1]
        ;----------------------------------------------------------
        move.l  d4,d1
        lsr.l   d0,d1
        or.b    d1,(a0)                        ; b0 high part

        moveq   #8,d2
        sub.w   d0,d2                          ; d2 = 8 - bit_shift
        move.l  d4,d1
        lsl.l   d2,d1
        move.l  d5,d3
        lsr.l   d0,d3
        or.l    d3,d1
        or.b    d1,1(a0)                       ; b0 low part | b1 high part

        moveq   #8,d2
        sub.w   d0,d2
        move.l  d5,d1
        lsl.l   d2,d1
        move.l  d6,d3
        lsr.l   d0,d3
        or.l    d3,d1
        or.b    d1,2(a0)                       ; b1 low part | b2 high part

        moveq   #8,d2
        sub.w   d0,d2
        move.l  d6,d1
        lsl.l   d2,d1
        move.l  d7,d3
        lsr.l   d0,d3
        or.l    d3,d1
        or.b    d1,3(a0)                       ; b2 low part | b3 high part

        ; Write overflow byte to dest[4] if:
        ;   visible + bit_shift > 32  
        ;   byte_col + 4 < SCREEN_BYTES_PER_ROW 
        move.w  lv32_visible(a6),d1
        add.w   lv32_bit_shift(a6),d1
        cmp.w   #32,d1
        ble.s   p32_next_row                   ; no overflow, skip

        move.w  lv32_byte_col(a6),d1
        addq.w  #4,d1
        cmp.w   #SCREEN_BYTES_PER_ROW,d1
        bge.s   p32_next_row                   ; next byte is off screen, skip

        moveq   #8,d2
        sub.w   d0,d2                          ; d2 = 8 - bit_shift
        move.l  d7,d1
        lsl.l   d2,d1
        or.b    d1,4(a0)                       ; b3 low part into overflow byte

p32_next_row:
        addq.w  #1,lv32_r(a6)                  ; r++
        bra     p32_row_loop                   ; next row

p32_done:
        movem.l (sp)+,d0-d7/a0-a5             
        unlk    a6                             
        rts
	