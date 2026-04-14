#include <osbind.h>
#include "vbl.h"
#include "music.h"


extern void vbl_isr(void);

volatile int render_request = 0;
volatile unsigned long vbl_ticks = 0;

static Vector old_vbl = 0;

static Vector install_vector(int num, Vector vector) { /* From lab 08*/
    Vector orig;
    Vector *vectp;
    long old_ssp;

    vectp = (Vector *)((long)num << 2);
    old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);

    return orig;
}

void init_vbl() {
    render_request = 0;
    vbl_ticks = 0;
    old_vbl = install_vector(28, vbl_isr);
}

void shutdown_vbl() {
    if (old_vbl != 0) /*Prevents for storing or using an invalid vector*/
        install_vector(28, old_vbl);
}

void do_vbl_isr() {
    vbl_ticks++;
    update_music(vbl_ticks);
    render_request = 1;
}
