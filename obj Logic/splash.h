#ifndef SPLASH_H
#define SPLASH_H

#include <osbind.h>
#include "raster.c"

UINT16 title_block[16] =
{
  0xFFFF,
  0xC003,
  0xC003,
  0xCFF3,
  0xCFF3,
  0xCC33,
  0xCC33,
  0xCC33,
  0xCC33,
  0xCFF3,
  0xCFF3,
  0xC003,
  0xC003,
  0xFFFF,
  0xFFFF,
  0xFFFF,
};

void render_splash(UINT16 *base, UINT16 *block);

#endif