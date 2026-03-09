;----- SUBROUTINE: plot_triangle -----
;
; PURPOSE: Plots a triangle on the screen given by the coordinate of the 90° angle, the length of the base, the length of the height, and the direction of the triangle.
;
; INPUT: Address(UINT8*): to the start of the screen
;        Position(row,col): the coordinates of the pixel of the 90° angle of the triangle
;        Height: the lenth (number of rows) of the height in pixels of the triangle
;        Direction: Describes where the coordinate is relative to the rest of the triangle
;              0 - Coordinate is the top left point of the triangle
;              1 - Coordinate is the top right point of the triangle
;              2 - Coordinate is the bottom left point of the triangle
;              3 - Coordinate is the bottom right point of the triangle
;
;
; OUTPUT: None