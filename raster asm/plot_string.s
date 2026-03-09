;----- SUBROUTINE: plot_string -----
;
; PURPOSE: Plots a string, as a sequence of bitmaps from a font table, to the screen.
;
; INPUT: Address(UINT32*): to the start of the screen
;        Position(row,col): the coordinates of the top left pixel of the string
;        ch(c-string): the string to be written to the screen
;
; OUTPUT: None