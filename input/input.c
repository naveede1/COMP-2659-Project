#include <stdio.h>
#include "input.h"
#include <osbind.h>


boolean has_input() {
    return (Cconis() != 0) ? TRUE : FALSE;
}

char get_input() {
    return (char)Cnecin(); /*Type cast to char*/
}

boolean is_held() {
    return held;
}

boolean is_released() {
    if (Cconis() != 0) {
        /* If there is input, we consider it held as true*/
        held = TRUE;
        released = FALSE;
    } else {
        /* If there is no input, we check if the key was previously held*/
        if (held) {
            released = TRUE;
            held = FALSE;
        }
    }
    return released;
}