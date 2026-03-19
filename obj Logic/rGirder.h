#include "girder.h"
#include "raster.h"

#define SPRITE_HEIGHT 8

char girder_BM[8] = /* Piece together as needed to form the Girders */
{
0xFF,
0x10,
0x38,
0x6C,
0xC6,
0x83,
0X01,
0xFF,
};

void renderGirder(Girder girder, UINT32 base);