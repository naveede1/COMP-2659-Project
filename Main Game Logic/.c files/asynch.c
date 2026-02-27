#include "asynch.h"
#include "mario.h"

void handle_asynch_event(Model *model, int event)
{
    switch(event)
    {
        case 0: /* Move Left */
            model->mario.deltX = -MOVE_SPEED;
            model->mario.direction = 0;
            break;

        case 1: /* Move Right */
            model->mario.deltX = MOVE_SPEED;
            model->mario.direction = 1;
            break;

        case 2: /* Stop Moving */
            model->mario.deltX = 0;
            break;

        case 3:
        /* Cannot jump while hammer is active */
            if (model->mario.hammerActive)
                return;

            if (model->mario.onGround) {  
                model->mario.deltY = JUMP_FORCE;
                model->mario.onGround = 0;
                model->mario.state = 3;
            }
            break;

        case 4:
            requestClimbUp(&model->mario);
            break;

        case 5:
            requestClimbDown(&model->mario);
            break;
    }
}