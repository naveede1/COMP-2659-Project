#include "lives.h"

void loseLife(Lives *lives)
{
    if (lives->value > 0)
        lives->value--;
}