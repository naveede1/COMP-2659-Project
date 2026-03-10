;----- SUBROUTINE: clear_screen -----
;
; PURPOSE: Clears the entire screen.
;
; INPUT: Address(UINT32*): to the start of the screen
;
; OUTPUT: None

SCREEN_WIDTH	equ	8000
BASE_32		equ	8

clear_screen:
		link	a6,#0
		movem.l	d0-d2/a0-a2,-(sp)

		clr 	d0
		move.l	BASE_32(a6),a0

		cmpi.w	#SCREEN_WIDTH,d0