#ifndef INPUT_H
#define INPUT_H

typedef enum { FALSE, TRUE } boolean;

static boolean held = FALSE;
static boolean released = FALSE;

/*----- Function: has_input -----

PURPOSE: Checks if there is an input processed

INPUT: NONE

OUTPUT: TRUE if input was processed
        FALSE if no input was processed

*/
boolean has_input();

/*----- Function: get_input -----

PURPOSE: Get input processed

INPUT: NONE

OUTPUT: Character processed

*/
char get_input();

/*----- Function: is_held -----

PURPOSE: Checks if the current input is being held

INPUT: NONE

OUTPUT: TRUE if the input processed was held
        FALSE if not

*/
void is_held();

/*----- Function: is_released -----

PURPOSE: Check if the held input was released

INPUT: NONE

OUTPUT: TRUE if the held input was released
        FALSE if the input is still being held

*/
boolean is_released();

#endif