#include "rItem.h"

void renderItem(Item item, UINT32 base) {

    if (item.visible == 1) {
        if (item.type == 0){
            plot_bitmap_16(base, item.posY, item.posX, 16, umbrella_BM);
        }
        else if (item.type == 1){
            plot_bitmap_16(base, item.posY, item.posX, 16, purse_BM);
        }
        else {
            plot_bitmap_16(base, item.posY, item.posX, 16, hat_BM);
        }
    }
} 