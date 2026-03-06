#include <stdio.h>
#include "model.h"

void testBarrel(Barrel barrel) {

    if (barrel.visible == 1) {
        printf("This Barrel is Visible onscreen \n");
    }
    else {
        printf("This Barrel is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", barrel.posX);
    printf("Current y pos: %d \n", barrel.posY);
    printf("Current x speed: %d \n", barrel.deltX);
    printf("Current y speed: %d \n", barrel.deltY);

    if (barrel.state == 1) {
        printf("This Barrel is rolling down a ladder \n");
    }
    else {
        printf("This Barrel is rolling on the ground \n");
    }

    if (barrel.type == 1) {
        printf("This is a Fire Barrel \n");
    }
    else {
        printf("This is NOT a Fire Barrel \n");
    }
}

void testGirder(Girder girder) {
   
    if (girder.visible == 1) {
        printf("This Girder is Visible onscreen \n");
    }
    else {
        printf("This Girder is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", girder.posX);
    printf("Current y pos: %d \n", girder.posY);
    printf("This girder spans from %d to %d \n", girder.colLeft, girder.colRight);
}

void testHammer(Hammer hammer) {

    if (hammer.visible == 1) {
        printf("This Hammer is Visible onscreen \n");
    }
    else {
        printf("This Hammer is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", hammer.posX);
    printf("Current y pos: %d \n", hammer.posY);

    if (hammer.state == 1) {
        printf("This Hammer has been used \n");
    }
    else {
        printf("This Hammer has NOT been used \n");
    }
}

void testHeart(Heart heart) {

    if (heart.visible == 1) {
        printf("The Heart is Visible onscreen \n");
    }
    else {
        printf("The Heart is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", heart.posX);
    printf("Current y pos: %d \n", heart.posY);
   
    if (heart.broken == 1) {
        printf("The Heart is Broken \n");
    }
    else {
        printf("The Heart is NOT Broken \n");
    }

    printf("Current Animation Timer: %f \n", heart.animTimer);
}

void testItem(Item item) {

    if (item.visible == 1) {
        printf("This Item is Visible onscreen \n");
    }
    else {
        printf("This Item is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", item.posX);
    printf("Current y pos: %d \n", item.posY);

    if (item.type == 1) {
        printf("This is a Purse \n");
    }
    else if (item.type == 2) {
        printf("This is a Hat \n");
    }
    else {
        printf("This is an Umbrella \n");
    }

    printf("This Item has been visible for %f \n", item.lifetime);

}

void testKong(Kong kong){

        if (kong.visible == 1) {
        printf("DK is Visible onscreen \n");
    }
    else {
        printf("DK is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", kong.posX);
    printf("Current y pos: %d \n", kong.posY);
    
    if (kong.state == 1) {
        printf("DK is currently Grabbing a Barrel \n");
    }
    else if (kong.state == 2) {
        printf("Kong is currently Throwing a Barrel \n");
    }
    else {
        printf("Kong is currently Idle \n");
    }

    printf("The next Barrel will be thrown in %d \n", kong.barrelCooldown);
}

void testLadder(Ladder ladder) {
   
    if (ladder.visible == 1) {
        printf("This Ladder is Visible onscreen \n");
    }
    else {
        printf("This Ladder is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", ladder.posX);
    printf("Current y pos: %d \n", ladder.posY);
    printf("This ladder spans horizontally from %d to %d \n", ladder.left, ladder.right);
    printf("This ladder spans vertically from %d to %d \n", ladder.top, ladder.bottom);

    if (ladder.broken == 1) {
        printf("This Ladder is Broken \n");
    }
    else {
        printf("This Ladder is NOT Broken \n");
    }
}

void testLady(Lady lady) {

    if (lady.visible == 1) {
        printf("Pauline is Visible onscreen \n");
    }
    else {
        printf("Pauline is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", lady.posX);
    printf("Current y pos: %d \n", lady.posY);
    printf("The Victory Zone falls between %d (Left) and %d (Right) \n", lady.topL, lady.bottomR);
}

void testLives(Lives lives) {

    if (lives.visible == 1) {
        printf("The Lives UI is Visible onscreen \n");
    }
    else {
        printf("The Lives UI is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", lives.posX);    
    printf("Current y pos: %d \n", lives.posY);
    printf("The Player currently has %d lives \n", lives.value);
}

void testMario (Mario mario) {
    
    if (mario.visible == 1) {
        printf("Mario is Visible onscreen \n");
    }
    else {
        printf("Mario is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", mario.posX);
    printf("Current y pos: %d \n", mario.posY);
    printf("Current x speed: %d \n", mario.deltX);
    printf("Current y speed: %d \n", mario.deltY);

    if (mario.state == 1) {
        printf("Mario is currently Walking \n");
    }
    else if (mario.state == 2) {
        printf("Mario is currently Climbing \n");
    }
    else if (mario.state == 3) {
        printf("Mario is currently Jumping \n");
    }
    else if (mario.state == 4) {
        printf("Mario is currently Dead/Falling Offscreen \n");
    }
    else {
        printf("Mario is currently Standing \n");
    }

    if (mario.direction == 1) {
        printf("Mario is facing Right \n");
    }
    else {
        printf("Mario is facing Left \n");
    }

    if (mario.climbDir == 1) {
        printf(" Mario is climbing Down \n");
    }
    else {
        printf("Mario is climbing Up \n");
    }

    if (mario.onGround == 1) {
        printf("Mario is on the Ground \n");
    }
    else {
        printf("Mario is in the Air \n");
    }

    if (mario.hammerActive == 1) {
        printf("Mario is using a Hammer \n");

        printf("The hammer has %f left \n" , mario.hammerTimer);

    }
    else {
        printf("Mario is not using a Hammer \n");
    }
}

void testOil(Oil oil) {

    if (oil.visible == 1) {
        printf("The Oil Barrel is Visible onscreen \n");
    }
    else {
        printf("The Oil Barrel is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", oil.posX);
    printf("Current y pos: %d \n", oil.posY);

    if (oil.fireCheck == 1) {
        printf("There is a Fire Spirit Alive \n");
    }
    else {
        printf("There is is NOT an alive Fire Spirit \n");
        printf("There has not been one for %d seconds \n", oil.noFireTimer);
    }
    
    if (oil.state == 1) {
        printf("The Oil Barrel is in an Ignited state \n");
    }
    else {
        printf("The Oil Barrel is in a non-ignited state \n");
    }
}

void testScore(Score score) {

    if (score.visible == 1) {
        printf("The Score UI is Visible onscreen \n");
    }
    else {
        printf("The Score UI is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", score.posX);
    printf("Current y pos: %d \n", score.posY);
    
    printf("The Player currently has a score of %d \n", score.value);
}

void testSpirit(Spirit spirit) {

    if (spirit.visible == 1) {
        printf("The Spirit is Visible onscreen \n");
    }
    else {
        printf("The Spirit is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", spirit.posX);
    printf("Current y pos: %d \n", spirit.posY);

    printf("Current x speed: %d \n", spirit.deltX);
    printf("Current y speed: %d \n", spirit.deltY);
    
    if (spirit.state == 1) {
        printf("The Spirit is currently Climbing \n");
    }
    else {
        printf("The Spirit is currently Walking \n");
    }

    if (spirit.direction == 1) {
        printf("The Spirit is facing Right \n");
    }
    else {
        printf("The Spirit is facing Left \n");
    }
}

void testTimer(Timer timer) {

    if (timer.visible == 1) {
        printf("The Timer UI is Visible onscreen \n");
    }
    else {
        printf("The Timer UI is NOT Visible onscreen \n");
    }    

    printf("Current x pos: %d \n", timer.posX);
    printf("Current y pos: %d \n", timer.posY);
    printf("The Timer has a current value of %d \n", timer.value);
}
