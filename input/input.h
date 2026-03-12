#ifndef INPUT_H
#define INPUT_H

typedef enum { FALSE, TRUE } boolean;

/*----- Function: has_input -----

 PURPOSE: Returns true if there is pending input to be processed and false otherwise

 INPUT: NONE

*/
boolean has_input();

/*----- Function: get_input -----

 PURPOSE: Returns the next character to be processed

 INPUT: NONE

*/
char get_input();

#endif