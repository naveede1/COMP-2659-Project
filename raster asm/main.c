#include <stdio.h>
#include "raster.h"
#include <osbind.h>

int main() {
    int *r = 10;
    int *c = 10;
    int *w = 32;
    int *x_s = 0;
    int *y_s = 0; 
    int clip = clip_left_top_right_bottom(&r, &c, &w, 32, &x_s, &y_s);
    return  clip;
}
