	xdef	clear_screen

start:
	move.w	#2,-(sp)
	trap	#14
	addq.l	#2,sp
	move.l	d0,a0

	pea	(a0)
	jsr	clear_screen		

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

while:		cmpi.w	#SCREEN_WIDTH+1,d0
		beq	end
		move.b	#0,(a0)+
		addq.w	#1,d0
		bra	while			

end:		movem.l	(sp)+,d0-d2/a0-a2
		unlk	a6
		rts
