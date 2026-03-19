#ifndef GRAVITY_H
#define GRAVITY_H
#include "model.h"

typedef enum { FALSE, TRUE } boolean;

/*----- Function: is_mario_grounded -----

PURPOSE: Check if Mario is on a surface

INPUT:

OUTPUT: Return true if Mario is on a surface, otherwise false

*/
boolean is_mario_grounded(Mario *mario, Model *model);

/*----- Function: apply_gravity_mario -----

PURPOSE:  Increment the position if Mario is not on the grounded on a surface

INPUT:

OUTPUT:

*/
void apply_gravity_mario(Mario *mario);

/*----- Function: is_barrel_grounded -----

PURPOSE: Check if a barrel is on a surface

INPUT: 

OUTPUT: Return true if a barrel is on a surface, otherwise false

*/
boolean is_barrel_grounded(Barrel *barrel, Model *model);

/*----- Function: apply_gravity_barrel -----

PURPOSE:  Increment the position if Mario is not on the grounded on a surface

INPUT:

OUTPUT:

*/
void apply_gravity_barrel(Barrel barrel);

#endif