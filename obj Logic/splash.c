#include "splash.h"

void render_splash(UINT16 *base, UINT16 *block) {
    plot_bitmap_16(base, 200, 200, 14, block);
}

int main() {
    UINT16 *base = Physbase();
    
    clear_screen(base);
    render_splash(base, title_block);

    return 0;
}