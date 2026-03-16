;----- SUBROUTINE: clip_left_top_right_bottom -----
;
; PURPOSE: Clips a sprite to all four screen boundaries, adjusting its position, dimensions, and
;          bitmap offset to only render the visible portion.
;
;INPUT: Position(row, col): Pointer to the top left row and column of the sprite
;        height: Pointer to the height of the sprite in pixels
;        sprite_width: The width of the sprite in pixels
;        skip_x: Pointer to the number of columns to skip in the bitmap
;        skip_y: Pointer to the number of rows to skip in the bitmap
;
; OUTPUT: UINT16 bitmask of which edges were clipped (left, top, right, bottom)
       
SCREEN_HEIGHT 	equ 	400
SCREEN_WIDTH 	equ 	640

; clip offsets

row_ptr 	equ     8
col_ptr 	equ     12
height_ptr 	equ  	16
sprite_width 	equ 	20
x_skip_ptr 	equ  	22
y_skip_ptr 	equ  	26

        
        xdef    _clip_left_top_right_bottom

_clip_left_top_right_bottom:
        link    a6,#0
        movem.l d1-d7/a0-a4,-(sp)

        ; Load pointers from stack
        movea.l row_ptr(a6),a0
        movea.l col_ptr(a6),a1
        movea.l height_ptr(a6),a2
        movea.l x_skip_ptr(a6),a3
        movea.l y_skip_ptr(a6),a4

        ; Load values: d0=row, d1=col, d2=height
        move.w  (a0),d0
        move.w  (a1),d1
        move.w  (a2),d2

        ; Clear skip values; will be set if clipping occurs
        clr.w   (a3)
        clr.w   (a4)

	; --- Clip Top ---

        tst.w   d0                              ; is row < 0?
        bge.s   check_bottom
        move.w  d0,d3
        neg.w   d3                              ; d3 = numbers of rows above screen
        cmp.w   d2,d3                           ; if rows above >= height, sprite is fully off screen
        bge.s   return_zero
        move.w  d3,(a4)                         ; skip_y = rows above screen
        sub.w   d3,d2                           ; reduce height by clipped rows
        move.w  d2,(a2)
        clr.w   d0                              ; clamp row to 0

        ; --- Clip Bottom ---

check_bottom:
        cmp.w   #SCREEN_HEIGHT,d0               ; if row >= screen height, sprite is fully off screen
        bge.s   return_zero
        move.w  d0,d3
        add.w   d2,d3                           ; d3 = row + height (bottom edge)
        cmp.w   #SCREEN_HEIGHT,d3               ; does sprite extend past bottom?
        ble.s   check_left
        move.w  #SCREEN_HEIGHT,d2               ; clamp height so bottom edge = screen height
        sub.w   d0,d2
        move.w  d2,(a2)

        ; --- Clip Left ---

check_left:
        tst.w   d1                              ; is col < 0?
        bge.s   check_right
        move.w  d1,d3
        neg.w   d3                              ; d3 = number of columns left of screen
        move.w  sprite_width(a6),d4
        cmp.w   d4,d3                           ; if columns off screen >= width, sprite is fully off screen
        bge.s   return_zero
        move.w  d3,(a3)                         ; skip_x = columns left of screen
        clr.w   d1                              ; clamp col to 0

        ; --- Clip Right ---

check_right:
        cmp.w   #SCREEN_WIDTH,d1                ; if col >= screen width, sprite is fully off screen
        bge.s   return_zero

        move.w  #SCREEN_WIDTH,d3
        sub.w   d1,d3                           ; d3 = columns remaining on screen from col
        move.w  sprite_width(a6),d4
        move.w  (a3),d5
        sub.w   d5,d4                           ; d4 = visible width after left clip
        cmp.w   d4,d3                           ; use whichever is smaller: visible or remaining
        ble.s   write_back
        move.w  d4,d3                           ; clamp to visible width

        ; --- Write back clipped values, return visible width in d0 ---

write_back:
        move.w  d0,(a0)                         ; write clipped row
        move.w  d1,(a1)                         ; write clipped col
        move.w  d2,(a2)                         ; write clipped height
        move.w  d3,d0                           ; return visible width
        bra.s   clip_done

        ; Draw nothing 
return_zero:
        clr.w   d0

clip_done:
        movem.l (sp)+,d1-d7/a0-a4
        unlk    a6
        rts
