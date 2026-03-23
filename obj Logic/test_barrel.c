#include "barrel.c"
#include "rBarrel.c"

#include <osbind.h>

Barrel t_barrel[1] = {
    {1, 200, 200, 0, 0, 0, 0, 0, 0, 0, 1}
};

int main() {
    UINT16 *base = Physbase();

    int i;

    clear_screen((UINT32 *)base);

    renderBarrel(t_barrel[0], base);

    for (i = 0; i < 30; i++) {
        roll_barrel(&t_barrel[0]);
        clear_screen((UINT32 *)base);
        renderBarrel(t_barrel[0], base);
    }

    return 0;
}