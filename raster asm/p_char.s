;----- SUBROUTINE: plot_character -----
;
; PURPOSE: Plots a single character, as a bitmap from a font table, to the screen.
;
; INPUT: Address(UINT32*): to the start of the screen
;        Position(row,col): the coordinates of the top left pixel of the character
;        ch(char): the character to be written to the screen
;
; OUTPUT: None