#ifndef ASYNCH_H
#define ASYNCH_H

#include "model.h"

int handle_asynch_events(Model *model);

int checkHorizontal(Model *model, char input_char);
int checkVertical(Model *model, char input_char);
int checkJump (Model *model, char input_char);
int checkQuit (Model *model, char input_char);

#endif