#include <stdio.h>
#include "input.h"

int main() {
    char ch;
    printf("Press keys to test. Press 'q' to quit.\n\n");

    while (1) {
        /* Only read when input is available - never blocks the loop */
        if (has_input()) {
            ch = get_input();
            printf("Input was: %c\n", ch);
            /* is_held should be TRUE immediately after get_input */
            printf("  is_held    : %s\n", is_held()? "TRUE" : "FALSE");
            /* is_released consumes the held state - TRUE only on first call */
            printf("  is_released: %s\n", is_released()? "TRUE" : "FALSE");
            /* Second call must return FALSE (state consumed) */
            printf("  is_released (2nd call): %s\n", is_released() ? "TRUE" : "FALSE");
            printf("  is_held (2nd call): %s\n", is_held() ? "TRUE" : "FALSE");
            printf("\n");
            if (ch == 'q') break;
        }
    }

    printf("Test complete.\n");
    return 0;
}