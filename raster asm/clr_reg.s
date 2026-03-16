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

; Argument offsets from a6
base_ptr        equ      8
row_arg         equ     12
col_arg         equ     14
length_arg      equ     16
width_arg       equ     18

; Local variable offsets from a6
r0_local        equ     -2
c0_local        equ     -4
h_local         equ     -6
xs_local        equ     -8
ys_local        equ     -10
end_bit_local   equ     -9              ; byte: low byte of ys_local word (big-endian)


_clear_region:
        link    a6,#-10
        movem.l d1-d7/a0-a4,-(sp)

        ; --- Copy arguments into locals for clip call ---
        move.w  row_arg(a6),d0
        move.w  col_arg(a6),d1
        move.w  length_arg(a6),d2
        move.w  d0,r0_local(a6)
        move.w  d1,c0_local(a6)
        move.w  d2,h_local(a6)
        clr.w   xs_local(a6)
        clr.w   ys_local(a6)

        ; --- Call clip_left_top_right_bottom ---
        pea     ys_local(a6)                    ; &y_skip
        pea     xs_local(a6)                    ; &x_skip
        move.w  width_arg(a6),-(sp)             ; width
        pea     h_local(a6)                     ; &height
        pea     c0_local(a6)                    ; &col
        pea     r0_local(a6)                    ; &row
        jsr     _clip_left_top_right_bottom
        add.l   #22,sp

        ; --- Check visible width (d0) and clipped height ---
        tst.w   d0
        beq.s   clear_done
        move.w  h_local(a6),d2
        tst.w   d2
        beq.s   clear_done

        ; d6 = visible width
        move.w  d0,d6

        ; --- Reload clipped row/col ---
        move.w  r0_local(a6),d4                 ; d4 = r0
        move.w  c0_local(a6),d5                 ; d5 = c0

clear_done:
        movem.l (sp)+,d1-d7/a0-a4
        unlk    a6
        rts
		