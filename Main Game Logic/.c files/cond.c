#include "cond.h"

void handle_conditional_events(Model *model)
{
    /* Barrel Collision */
    if (checkBarrelCollision(&model->mario, model->barrels, 7))
    {
        model->mario.dead = 1;
    }

    /* Spirit Collision */
    if (checkSpiritCollision(&model->mario, &model->spirit))
    {
        model->mario.dead = 1;
    }

    /* Hammer Smash */
    if (model->mario.hammerActive)
    {
        smashBarrels(&model->mario, model->barrels, 7, &model->score);
    }

    /* Item Pickup */
    int itemType = checkItemPickup(model->items, 3, model->mario.posX,model->mario.posY);

    if (itemType != -1)
    {
        switch(itemType)
        {
            case 0: model->score.value += 300; break;
            case 1: model->score.value += 500; break;
            case 2: model->score.value += 800; break;
        }
    }

    /* Victory */
    if (checkVictory(&model->lady, model->mario.posX, model->mario.posY))
    {
        model->timer.active = 0;
        model->score.value += model->timer.value;
        model->heart.visible = 1;
    }

    /* Timer Expired */
    if (model->timer.value <= 0)
    {
        model->mario.dead = 1;
    }
}