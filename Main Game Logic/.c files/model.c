#include <stdio.h>
#include "model.h"
#include "asynch.h"
#include "synch.h"
#include "cond.h"


Model model; /* Global Model Instance */

typedef enum { /* Game State Model */
    STATE_PLAYING,
    STATE_PLAYER_DEAD,
    STATE_LEVEL_COMPLETE,
    STATE_GAME_OVER
} GameState;

static GameState gameState;

void model_init() {
    
    gameState = STATE_PLAYING; /* Game State Reset*/

    /* Score */
    model.score.visible = 1;
    model.score.posX = 20;
    model.score.posY = 20;
    model.score.value = 0;

    /* Lives */
    model.lives.visible = 1;
    model.lives.posX = 20;
    model.lives.posY = 40;
    model.lives.value = 3;

    /* Timer */
    model.timer.visible = 1;
    model.timer.posX = 300;
    model.timer.posY = 20;
    model.timer.startValue = 5000;
    model.timer.value = 5000;
    model.timer.tickRate = 1.0f;
    model.timer.tickTimer = 0.0f;
    model.timer.active = 1;

    /* Heart */
    model.heart.visible = 0;
    model.heart.broken = 0;

}

/* Main Update Function */
void model_update(float deltaTime)
{
    if (gameState == STATE_PLAYING)
    {
        handle_synch_events(&model, deltaTime);
        handle_conditional_events(&model);
    }
    else if (gameState == STATE_PLAYER_DEAD)
    {
        /* Respawn logic */
        if (model.lives.value > 0)
        {
            /* Reset Mario position */
            model.mario.dead = 0;
            gameState = STATE_PLAYING;
        }
        else
        {
            gameState = STATE_GAME_OVER;
        }
    }
    else if (gameState == STATE_LEVEL_COMPLETE)
    {
        /* Wait for heart animation to finish */
        if (model.heart.broken)
        {
            /* Advance level here if we decide to add more levels. For now just "YOU WIN" */
            gameState = STATE_PLAYING;
        }
    }
}


/* Asynchronnuos Input*/
void model_handle_input(int event)
{
    handle_asynch_event(&model, event);
}


/* Helper Functions to Handle Events */
void model_add_score(int amount)
{
    model.score.value += amount;
}

void model_lose_life()
{
    if (model.lives.value > 0)
        model.lives.value--;

    if (model.lives.value <= 0)
        gameState = STATE_GAME_OVER;
    else
        gameState = STATE_PLAYER_DEAD;
}

GameState model_get_state()
{
    return gameState;
}