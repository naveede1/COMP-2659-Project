#ifndef MODEL_H
#define MODEL_H

#include "mario.h"
#include "girder.h"
#include "ladder.h"
#include "kong.h"
#include "oil.h"
#include "hammer.h"
#include "lady.h"
#include "barrel.h"
#include "spirit.h"
#include "item.h"
#include "heart.h"
#include "timer.h"
#include "score.h"
#include "lives.h"

/*
Main Model of the game. 
-> Any created instance must follow this pattern
ex.

Model testDKsnapshot = {
    {0, 320, 200, 0, 0, 0, 1, 0, 0}  (Visible, PosX, PosY, DeltX, DeltY, State, Grounded?, Hammer?, Dead?)
    ...
}
*/
typedef struct {

    Mario mario;
    Girder girders[9];
    Ladder ladders[13];
    Kong kong;
    Oil oil;
    Hammer hammers[2];
    Lady lady;
    Barrel barrels[7];
    Spirit spirit;
    Item items[3];
    Heart heart;
    Timer timer;
    Score score;
    Lives lives;

} Model;

#endif