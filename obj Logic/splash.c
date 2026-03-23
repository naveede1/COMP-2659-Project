#include "splash.h"
#include "input.c"

void render_splash(UINT16 *base, UINT16 *block) {
    /* Test bit map */
    plot_bitmap_16(base, 200, 200, 14, block);
}

void render_d(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Left vertical line */
    plot_bitmap_16(base, row, col, 14, block);
    plot_bitmap_16(base, row+15, col, 14, block);
    plot_bitmap_16(base, row+30, col, 14, block);
    plot_bitmap_16(base, row+45, col, 14, block);
    plot_bitmap_16(base, row+60, col, 14, block);
    /* Top horizontal line */
    plot_bitmap_16(base, row, col+15, 14, block);
    plot_bitmap_16(base, row, col+30, 14, block);
    /* Right vertical line */
    plot_bitmap_16(base, row+15, col+45, 14, block);
    plot_bitmap_16(base, row+30, col+45, 14, block);
    plot_bitmap_16(base, row+45, col+45, 14, block);
    /* Bottom horizontal line */
    plot_bitmap_16(base, row+60, col+15, 14, block);
    plot_bitmap_16(base, row+60, col+30, 14, block);
}

void render_o(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Top horizontal line */
    plot_bitmap_16(base, row, col+15, 14, block);
    plot_bitmap_16(base, row, col+30, 14, block);
    /* Left vertical line */
    plot_bitmap_16(base, row+15, col, 14, block);
    plot_bitmap_16(base, row+30, col, 14, block);
    plot_bitmap_16(base, row+45, col, 14, block);
    /* Right vertical line */
    plot_bitmap_16(base, row+15, col+45, 14, block);
    plot_bitmap_16(base, row+30, col+45, 14, block);
    plot_bitmap_16(base, row+45, col+45, 14, block);
    /* Bottom horizontal line */
    plot_bitmap_16(base, row+60, col+15, 14, block);
    plot_bitmap_16(base, row+60, col+30, 14, block);
}

void render_n(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Left vertical line */
    plot_bitmap_16(base, row, col, 14, block);
    plot_bitmap_16(base, row+15, col, 14, block);
    plot_bitmap_16(base, row+30, col, 14, block);
    plot_bitmap_16(base, row+45, col, 14, block);
    plot_bitmap_16(base, row+60, col, 14, block);
    /* Diagonal */
    plot_bitmap_16(base, row+15, col+15, 14, block);
    plot_bitmap_16(base, row+30, col+30, 14, block);
    plot_bitmap_16(base, row+45, col+45, 14, block);
    /* Right vertical line */
    plot_bitmap_16(base, row, col+60, 14, block);
    plot_bitmap_16(base, row+15, col+60, 14, block);
    plot_bitmap_16(base, row+30, col+60, 14, block);
    plot_bitmap_16(base, row+45, col+60, 14, block);
    plot_bitmap_16(base, row+60, col+60, 14, block);
}

void render_k(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Left vertical line */
    plot_bitmap_16(base, row, col, 14, block);
    plot_bitmap_16(base, row+15, col, 14, block);
    plot_bitmap_16(base, row+30, col, 14, block);
    plot_bitmap_16(base, row+45, col, 14, block);
    plot_bitmap_16(base, row+60, col, 14, block);
    /* Middle joint */
    plot_bitmap_16(base, row+30, col+15, 14, block);
    /* Upper diagonal */
    plot_bitmap_16(base, row+15, col+30, 14, block);
    plot_bitmap_16(base, row, col+45, 14, block);
    /* Lower diagonal */
    plot_bitmap_16(base, row+45, col+30, 14, block);
    plot_bitmap_16(base, row+60, col+45, 14, block);
}

void render_e(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Left vertical line */
    plot_bitmap_16(base, row, col, 14, block);
    plot_bitmap_16(base, row+15, col, 14, block);
    plot_bitmap_16(base, row+30, col, 14, block);
    plot_bitmap_16(base, row+45, col, 14, block);
    plot_bitmap_16(base, row+60, col, 14, block);
    /* Top horizontal line */
    plot_bitmap_16(base, row, col+15, 14, block);
    plot_bitmap_16(base, row, col+30, 14, block);
    plot_bitmap_16(base, row, col+45, 14, block);
    /* Middle horizontal line */
    plot_bitmap_16(base, row+30, col+15, 14, block);
    plot_bitmap_16(base, row+30, col+30, 14, block);
    /* Bottom horizontal line */
    plot_bitmap_16(base, row+60, col+15, 14, block);
    plot_bitmap_16(base, row+60, col+30, 14, block);
    plot_bitmap_16(base, row+60, col+45, 14, block);
}

void render_y(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Upper left diagonal */
    plot_bitmap_16(base, row, col, 14, block);
    plot_bitmap_16(base, row+15, col+15, 14, block);
    /* Upper right diagonal */
    plot_bitmap_16(base, row, col+60, 14, block);
    plot_bitmap_16(base, row+15, col+45, 14, block);
    /* Centre stem */
    plot_bitmap_16(base, row+30, col+30, 14, block);
    plot_bitmap_16(base, row+45, col+30, 14, block);
    plot_bitmap_16(base, row+60, col+30, 14, block);
}

void render_g(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block) {
    /* Top horizontal line */
    plot_bitmap_16(base, row, col+15, 14, block);
    plot_bitmap_16(base, row, col+30, 14, block);
    plot_bitmap_16(base, row, col+45, 14, block);
    /* Left vertical line */
    plot_bitmap_16(base, row+15, col, 14, block);
    plot_bitmap_16(base, row+30, col, 14, block);
    plot_bitmap_16(base, row+45, col, 14, block);
    /* Mid right stub */
    plot_bitmap_16(base, row+30, col+30, 14, block);
    plot_bitmap_16(base, row+30, col+45, 14, block);
    plot_bitmap_16(base, row+45, col+45, 14, block);
    /* Bottom horizontal line */
    plot_bitmap_16(base, row+60, col+15, 14, block);
    plot_bitmap_16(base, row+60, col+30, 14, block);
    plot_bitmap_16(base, row+60, col+45, 14, block);
}

void render_menu_buttons(UINT32 *base) {
    plot_rectangle(base, 300, 225, 20, 150);
    plot_rectangle(base, 325, 225, 20, 150);

    linea0();
    plot_string((UINT8 *)base, 302, 270, "Player 1");
    plot_string((UINT8 *)base, 327, 282, "Quit");
}

void render_title(UINT16 *base, UINT16 *block) {

    render_d(base, 60,  65,  block);
    render_o(base, 60,  140, block);
    render_n(base, 60,  215, block);
    render_k(base, 60,  305, block);
    render_e(base, 60,  380, block);
    render_y(base, 60,  455, block);

    render_k(base, 180, 185, block);
    render_o(base, 180, 260, block);
    render_n(base, 180, 335, block);
    render_g(base, 180, 425, block);

    render_menu_buttons((UINT32 *)base);
}

int splash_screen(UINT16 *base, UINT16 *block) {
    
    int start_game;
    clear_screen((UINT32 *)base);
    render_title(base, block);

    while(!has_input()) {
        char input;
        input = get_input();

        if (input == '\r') {
            return 1;
        } else if (input == 'q') {
            return 0;
        }
    } 
}