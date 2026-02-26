#include "timer.h"

void updateTimer(Timer *timer, float deltaTime)
{
    if (!timer->active || !timer->visible)
        return;

    timer->tickTimer += deltaTime;

    if (timer->tickTimer >= timer->tickRate)
    {
        timer->tickTimer = 0.0f;

        if (timer->value > 0)
            timer->value -= 100;   /* The timer decreases in chunks that match the OG arcade */
    }
}
