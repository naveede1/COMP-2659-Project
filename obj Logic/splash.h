#ifndef SPLASH_H
#define SPLASH_H

#include <osbind.h>
#include <linea.h>

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

void render_d(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);
void render_o(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);
void render_n(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);
void render_k(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);
void render_e(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);
void render_y(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);
void render_g(UINT16 *base, UINT16 row, UINT16 col, UINT16 *block);

void render_menu_buttons(UINT32 *base);

void render_title(UINT16 *base, UINT16 *block);

int splash_screen(UINT16 *base, UINT16 *block);

#endif