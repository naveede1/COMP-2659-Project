#include <stdio.h>
#include "raster.h"
#include <osbind.h>

int main() {
    UINT32 *base = Physbase();
    clear_screen(base);
    return 0;
}
