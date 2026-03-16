;----- SUBROUTINE: clear_region -----
;
; PURPOSE: Clear a region of the screen. The section is specified by the coordinates of the top left corner, 
;          and the height and width of the region.
;
; INPUT: Address(UINT32*): to the start of the screen
;        Position(row,col): the coordinates of the top left pixel of the region
;        Length: the lenth (number of rows) in pixels of the region
;        Width: the width (number of columns) in pixels of the region
;
; OUTPUT: None
		
		xdef _clear_region
		xdef _clip_left_top_right_bottom

SCREEN_BYTES_PER_ROW    equ     80

; Stack offsets 
base_ptr        equ      8
row_arg         equ     12
col_arg         equ     14
length_arg      equ     16
width_arg       equ     18

; Local variable offsets 
r0_local        equ     -2
c0_local        equ     -4
h_local         equ     -6
xs_local        equ     -8
ys_local        equ     -10
end_bit_local   equ     -9              ; byte: low byte of ys_local word (big-endian)


_clear_region:
        link    a6,#-10
        movem.l d1-d7/a0-a4,-(sp)

        ; Copy arguments into locals for clip call 
        move.w  row_arg(a6),d0
        move.w  col_arg(a6),d1
        move.w  length_arg(a6),d2
        move.w  d0,r0_local(a6)
        move.w  d1,c0_local(a6)
        move.w  d2,h_local(a6)
        clr.w   xs_local(a6)
        clr.w   ys_local(a6)

        ; Call _clip_left_top_right_bottom 
        pea     ys_local(a6)                    ; &y_skip
        pea     xs_local(a6)                    ; &x_skip
        move.w  width_arg(a6),-(sp)             ; width
        pea     h_local(a6)                     ; &height
        pea     c0_local(a6)                    ; &col
        pea     r0_local(a6)                    ; &row
        jsr     _clip_left_top_right_bottom
        add.l   #22,sp

        ; Check visible width (d0) and clipped height 
        tst.w   d0
        beq     clear_done
        move.w  h_local(a6),d2
        tst.w   d2
        beq     clear_done

        ; d6 = visible width
        move.w  d0,d6

        ; Reload clipped row/col 
        move.w  r0_local(a6),d4                 ; d4 = r0
        move.w  c0_local(a6),d5                 ; d5 = c0


        ; start_byte = c0 >> 3 
        move.w  d5,d0
        lsr.w   #3,d0                           ; d0 = start_byte

        ; end_byte = (c0 + visible - 1) >> 3 
        move.w  d5,d1
        add.w   d6,d1
        subq.w  #1,d1
        lsr.w   #3,d1                           ; d1 = end_byte

        ; start_bit = c0 & 7
        move.w  d5,d3
        and.w   #7,d3                           ; d3 = start_bit

        ; end_bit = (c0 + visible - 1) & 7 
        move.w  d5,d7
        add.w   d6,d7
        subq.w  #1,d7
        and.w   #7,d7                           ; d7 = end_bit
        move.w  d7,ys_local(a6)                 ; save: high byte unused, low byte = end_bit

        ; Base pointer 
        movea.l base_ptr(a6),a0

        clr.w   d5                              ; d5 = r = 0

row_loop:
        cmp.w   d2,d5
        bge     clear_done 						; row is done 

        move.w  d4,d6
        add.w   d5,d6                           ; d6 = r0 + r
        mulu    #SCREEN_BYTES_PER_ROW,d6
        movea.l a0,a1
        adda.l  d6,a1                           ; a1 = line

        movea.l a1,a2
        adda.w  d0,a2                           ; a2 = start

        movea.l a1,a3
        adda.w  d1,a3                           ; a3 = end

        movea.l a2,a4                           ; a4 = curr

byte_loop:
        cmpa.l  a3,a4
        bgt     byte_done

        ; single byte: curr == start && curr == end 
        cmpa.l  a2,a4
        bne     not_single
        cmpa.l  a3,a4
        bne     not_single

        ; right = 0xFF << (7 - end_bit), left = 0xFF >> start_bit
        ; mask = left & right  ;  *curr &= ~mask
        moveq   #7,d7
        sub.b   end_bit_local(a6),d7            ; d7 = 7 - end_bit
        move.b  #-1,d6
        lsl.b   d7,d6                           ; d6 = right
        move.b  #-1,d7
        lsr.b   d3,d7                           ; d7 = left
        and.b   d7,d6                           ; d6 = mask
        not.b   d6
        and.b   d6,(a4)
        bra    next_byte

not_single:
        ; start byte only 
        cmpa.l  a2,a4
        bne	    not_start

        move.b  #-1,d6
        lsr.b   d3,d6                           ; d6 = 0xFF >> start_bit
        not.b   d6
        and.b   d6,(a4)
        bra     next_byte

not_start:
        ; end byte only 
        cmpa.l  a3,a4
        bne     not_end

        moveq   #7,d7
        sub.b   end_bit_local(a6),d7            ; d7 = 7 - end_bit
        move.b  #$FF,d6
        lsl.b   d7,d6                           ; d6 = 0xFF << (7 - end_bit)
        not.b   d6
        and.b   d6,(a4)
        bra     next_byte

not_end:
        ; interior byte
        clr.b   (a4)

next_byte:
        addq.l  #1,a4
        bra   byte_loop

byte_done:
        addq.w  #1,d5
        bra   row_loop

clear_done:
        movem.l (sp)+,d1-d7/a0-a4
        unlk    a6
        rts
		