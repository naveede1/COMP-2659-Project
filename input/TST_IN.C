#include <stdio.h>
#include "input.h"

int main() {
    char u_input; 
    printf("Press a key or just hold it. Press ESC to quit.\n");
    while (1) {
        is_released();  /* must be called every cycle to update state */

        if (has_input()) {  
            /*check if input is available*/
            u_input = get_input();

            if (u_input == 'q') {
                printf("Quiting.\n");
                break;
            }
            /*print the input and the state of held and released*/
            printf("Key '%c' | held: %d | released: %d\n", u_input, is_held(), is_released());
         } else {
            /*check if the key was just released should give held 0(False) and released 1(True)*/
            if (is_released()) {
                printf("Key released | held: %d | released: %d\n", is_held(), is_released());
            }   
        }
    }

    return 0;
}
