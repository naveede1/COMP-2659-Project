#include <stdio.h>
#include "input.h"
#include <osbind.h>

int main() {
    return 0;
}

boolean has_input() {
    return (Cconis()) ? TRUE : FALSE;
}

char get_input() {
    return Cnecin();
}

boolean is_held() {
    return FALSE;
}

boolean is_released() {
    return FALSE;
}