;----- SUBROUTINE: clear_screen -----
;
; PURPOSE: Clears the entire screen.
;
; INPUT: Address(UINT32*): to the start of the screen
;
; OUTPUT: None

		xdef	_clear_screen		

SCREEN_WIDTH	equ	8000
BASE_32		equ	8

_clear_screen:
		link	a6,#0
		movem.l	d0-d2/a0-a2,-(sp)

		clr 	d0
		move.l	BASE_32(a6),a0

while:		cmpi.w	#SCREEN_WIDTH+1,d0
		beq	loop_end
		move.l	#0,(a0)+
		addq.w	#1,d0
		bra	while			

loop_end:	movem.l	(sp)+,d0-d2/a0-a2
		unlk	a6
		rts
