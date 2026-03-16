#include <stdio.h>
#include "input.h"
#include <osbind.h>

boolean has_input() {
    return (Cconis() != 0) ? TRUE : FALSE;
}

char get_input() {
    return (char)Cnecin();
}

void is_held() {
    /*

    Case 1: Nothing in the buffer, so the user does not press an input or the key was released 
    Case 2: Input in buffer. Users current input == next input, therefore it is held
    Case 3: Input in buffer. Users current input != next input, therefore it is released

    */

    char current_input;
    char next_input;

    /* Waiting loop for the first input */
    printf("Waiting for first input...\n");
    while (!has_input());

    current_input = get_input();
    printf("First input is: %c\n", current_input);

    while(TRUE) {
        printf("Waiting for next input...\n");
        if (has_input()) {
            next_input = get_input();
            printf("Next input is: %c\n", next_input);
            if (current_input != next_input) {
                printf("Input released, different character pressed.\n");
                return;
            }
        } else {
            printf("Input released.\n");
            return;
        }
    }
}

/* 
    I think this function will be removed as it is pretty useless with is_held() existing.
    Additionally might change the name of is_held().
*/
boolean is_released() {
    return FALSE;
}