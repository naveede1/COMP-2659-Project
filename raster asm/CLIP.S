;----- SUBROUTINE: clip_left_top_right_bottom -----
;
; PURPOSE:
;
; INPUT: 
;
; OUTPUT:

SCREEN_HEIGHT equ 400
SCREEN_WIDTH equ 640

;----------------------------------------------------------------
; clip offsets
;----------------------------------------------------------------
row_ptr equ     8
col_ptr equ     12
height_ptr equ  16
sprite_width equ 20
x_skip_ptr equ  22
y_skip_ptr equ  26

        
        xdef    _clip_left_top_right_bottom

_clip_left_top_right_bottom:
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
