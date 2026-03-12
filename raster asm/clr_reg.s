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