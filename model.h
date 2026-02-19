#ifndef MODEL_H
#define MODEL_H

/*
Main Model of the game. 
-> Any created instance must follow this pattern
ex.

Model testDKsnapshot = {
    {320, 200, 0, 0, 0, 0, 0}  (PosX, PosY, DeltX, DeltY, State, Hammer?,Alive?)
    ...
}
*/
typedef struct {

    Mario mario;
    Girder girders[9];
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