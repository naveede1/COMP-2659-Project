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

SCREEN_BYTES_PER_ROW    equ     80

; stack offsets 
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

_plot_bitmap_8:
        link    a6,#-12                        
        movem.l d0-d7/a0-a5,-(sp)              

        ;----------------------------------------------------------
        ; Call clip_left_top_right_bottom(&row, &col, &height,
        ;                                 sprite_width, &x_skip, &y_skip)

        lea     lv8_y_skip(a6),a0
        move.l  a0,-(sp)                        ; y_skip  
        lea     lv8_x_skip(a6),a0
        move.l  a0,-(sp)                        ; x_skip
        move.w  #8,-(sp)                        ; sprite_width = 8
        lea     p8_height(a6),a0
        move.l  a0,-(sp)                        ; height
        lea     p8_col(a6),a0
        move.l  a0,-(sp)                        ; col
        lea     p8_row(a6),a0
        move.l  a0,-(sp)                        ; row     
        jsr     _clip_left_top_right_bottom
        adda.l  #22,sp                          

        tst.w   d0                              ; if visible == 0, nothing to draw
        beq     p8_done

        move.w  d0,lv8_visible(a6)              


        movea.l p8_bitmap(a6),a1
        move.w  lv8_y_skip(a6),d0
        ext.l   d0                              ; sign extend to long 
        adda.l  d0,a1                           ; advance by y_skip bytes
        move.l  a1,p8_bitmap(a6)                ; save advanced pointer back to stack

        ;   byte_col  = col >> 3  
        ;   bit_shift = col & 7   

        move.w  p8_col(a6),d0
        move.w  d0,d1
        lsr.w   #3,d0
        move.w  d0,lv8_byte_col(a6)             ; save byte column
        andi.w  #7,d1
        move.w  d1,lv8_bit_shift(a6)            ; save bit shift

        clr.w   lv8_r(a6)                       ; r = 0, loop_index

p8_row_loop:
        move.w  lv8_r(a6),d0
        cmp.w   p8_height(a6),d0                ; if r >= height, we are done
        bge     p8_done

        move.w  p8_row(a6),d1
        add.w   lv8_r(a6),d1                    ; d1 = row + r
        ext.l   d1
        mulu.w  #SCREEN_BYTES_PER_ROW,d1        ; d1 = (row + r) * 80
        move.w  lv8_byte_col(a6),d2
        ext.l   d2
        add.l   d2,d1                           ; d1 = byte offset into screen

        movea.l p8_base(a6),a0
        adda.l  d1,a0                           

        movea.l p8_bitmap(a6),a1
        move.w  lv8_r(a6),d0
        ext.l   d0
        move.b  0(a1,d0.l),d3                   ; d3 = bitmap[r]

        move.w  lv8_x_skip(a6),d4
        tst.w   d4
        beq.s   p8_right_clip                   ; no left clip needed
        lsl.b   d4,d3                           ; shift out clipped left bits

p8_right_clip:
        move.w  lv8_visible(a6),d5
        move.w  #8,d6
        sub.w   d4,d6                           ; d6 = 8 - x_skip (unclipped width)
        cmp.w   d6,d5                           ; if visible >= unclipped width, no right clip
        bge.s   p8_do_print
        move.w  #8,d6
        sub.w   d5,d6                           ; d6 = 8 - visible 
        move.b  #-1,d7                          
        lsl.b   d6,d7                           
        and.b   d7,d3                           ; zero out right clipped bits

p8_do_print:
        ; If bit_shift == 0: byte aligned, OR directly
        move.w  lv8_bit_shift(a6),d6
        tst.w   d6
        bne.s   p8_unaligned

        or.b    d3,(a0)                         ; aligned: OR source byte directly
        bra.s   p8_next_row

p8_unaligned:
        move.b  d3,d7
        lsr.b   d6,d7                           
        or.b    d7,(a0)                         ; write high part to current byte

        move.w  lv8_visible(a6),d7				; writing
        add.w   d6,d7
        cmp.w   #8,d7
        ble.s   p8_next_row                     ; no overflow, skip

        move.w  lv8_byte_col(a6),d7
        addq.w  #1,d7
        cmp.w   #SCREEN_BYTES_PER_ROW,d7
        bge.s   p8_next_row                     ; next byte is off screen, skip

        move.w  #8,d7
        sub.w   d6,d7                           ; d7 = 8 - bit_shift
        move.b  d3,d6
        lsl.b   d7,d6                           
        or.b    d6,1(a0)                        ; write low part to next byte

p8_next_row:
        addq.w  #1,lv8_r(a6)                    ; r++
        bra     p8_row_loop                     ; next row

p8_done:
        movem.l (sp)+,d0-d7/a0-a5              
        unlk    a6                             
        rts
                                   