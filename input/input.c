#include <stdio.h>
#include "input.h"
#include <osbind.h>

static boolean held = FALSE;
static boolean released = FALSE;


int main() {
    while(1){
        if(has_input()){
            char input = get_input();
            printf("Input: %c\n", input);
            
            if(is_held()) printf("held\n");
            if(is_released()) printf("released\n");
            if(input =='q') break;        
        }
    }
    return 0;
}

boolean has_input(){
    return (Cconis() != 0) ? TRUE : FALSE;
}

char get_input() {    
    held = TRUE;
    released = FALSE;
    return Cnecin();
}

boolean is_held(){
    return held;
}

boolean is_released(){
    if (held == TRUE) {
        held = FALSE;
        released = TRUE;
        return TRUE;
    }
    released = FALSE;
    return FALSE;
}