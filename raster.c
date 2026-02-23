#include "raster.h"
#include <osbind.h>

void plot_rectangle(UINT32 *base, UINT16 row, UINT16 col, UINT16 length, UINT16 width) {
    UINT16 right_vertical_line_row = row + width - 1;    
    UINT16 bottom_horizontal_line_col = col + length - 1;
                                                  
    plot_horizontal_line(base, row, col, width);
    plot_horizontal_line(base, row, bottom_horizontal_line_col, width);
    plot_vertical_line(base, row, col, length);
    plot_vertical_line(base, right_vertical_line_row, col, length);
}

void plot_square(UINT32 *base, UINT16 row, UINT16 col, UINT16 side) {
    UINT16 right_vertical_line_row = row + side - 1;    
    UINT16 bottom_horizontal_line_col = col + side - 1;

    plot_horizontal_line(base, row, col, side);
    plot_horizontal_line(base, row, bottom_horizontal_line_col, side);
    plot_vertical_line(base, row, col, side);
    plot_vertical_line(base, right_vertical_line_row, col, side);
}

void plot_triangle(UINT32 *baseptr, UINT16 row, UINT16 col, UINT16 base, UINT16 height, UINT8 direction) {
    UINT16 diag_start_row, diag_start_col;
    UINT16 diag_end_row, diag_end_col;
    
    if (direction == 0) {
        plot_vertical_line(baseptr, row, col, height);
        plot_horizontal_line(baseptr, row, col, base);
        
        diag_start_row = row + base - 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col + height - 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 1) {
        plot_vertical_line(baseptr, row, col, height);
        plot_horizontal_line(baseptr, row - base + 1, col, base);
        
        diag_start_row = row - base + 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col + height - 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 2) {
        plot_vertical_line(baseptr, row, col - height + 1, height);
        plot_horizontal_line(baseptr, row, col, base);

        diag_start_row = row + base - 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col - height + 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
        
    } else if (direction == 3) {
        plot_vertical_line(baseptr, row, col - height + 1, height);
        plot_horizontal_line(baseptr, row - base + 1, col, base);
        
        diag_start_row = row - base + 1;
        diag_start_col = col;
        diag_end_row = row;
        diag_end_col = col - height + 1;
        plot_line(baseptr, diag_start_row, diag_start_col, diag_end_row, diag_end_col);
    }
}