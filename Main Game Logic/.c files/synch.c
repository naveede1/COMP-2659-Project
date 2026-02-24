#include "synch.h"

void handle_synch_events(Model *model, float deltaTime)
{
    updateMario(&model->mario, model->girders, 9, model->ladders, 13, deltaTime);

    updateKong(&model->kong, deltaTime);

    updateBarrels(model->barrels, 7, deltaTime, model->girders, 9, model->ladders, 13);

    updateSpirit(&model->spirit, deltaTime, model->girders, 9, model->ladders, 13);

    updateOil(&model->oil, deltaTime);

    updateHammers(model->hammers, 2, deltaTime);

    updateItems(model->items, 3, deltaTime);

    updateTimer(&model->timer, deltaTime);

    updateHeart(&model->heart, deltaTime);
}