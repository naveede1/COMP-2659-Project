#include <stdio.h>
#include "input.h"
#include <osbind.h>

static boolean held = FALSE;
static boolean released = FALSE;


boolean has_input() {
    return (Cconis() != 0) ? TRUE : FALSE;
}

char get_input() {
    long raw = Cnecin(); /* blocks; upper bytes = scan code */
    held     = TRUE;
    released = FALSE;
    /*https://freemint.github.io/tos.hyp/en/gemdos_chrinout.html#Cneci*/
    /*since Cnecin return a long value have to isolate get the char val.*/
    return raw & 0xFF;
}

boolean is_held() {
    return held;
}

/*
 * Call once to consume a key-press event.
 * First call after get_input() returns TRUE and flips state to released.
 * Every call after that returns FALSE until the next get_input().
 */
boolean is_released() {
    if (held == TRUE) {
        held     = FALSE;
        released = TRUE;
        return TRUE;
    }
    released = FALSE;
    return FALSE;
}