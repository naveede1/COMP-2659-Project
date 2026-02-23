#include <stdio.h>
#include "model.h"

void testBarrel(Barrel *barrel) {

    if (barrel->visible == 1) {
        printf("This Barrel is Visible onscreen \n");
    }
    else {
        printf("This Barrel is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(barrel->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(barrel->posY);
    printf("\n");

    printf("Current x speed: ");
    printf(barrel->deltX);
    printf("\n");
    
    printf("Current y speed: ");
    printf(barrel->deltY);
    printf("\n");

    if (barrel->state == 1) {
        printf("This Barrel is rolling down a ladder \n");
    }
    else {
        printf("This Barrel is rolling on the ground \n");
    }

    if (barrel->type == 1) {
        printf("This is a Fire Barrel \n");
    }
    else {
        printf("This is NOT a Fire Barrel \n");
    }
}

void testGirder(Girder *girder) {
   
    if (girder->visible == 1) {
        printf("This Girder is Visible onscreen \n");
    }
    else {
        printf("This Girder is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(girder->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(girder->posY);
    printf("\n");

    printf("This girder spans from ");
    printf(girder->left);
    printf(" to ");
    printf(girder->right);
    printf("\n");
}

void testHammer(Hammer *hammer) {

    if (hammer->visible == 1) {
        printf("This Hammer is Visible onscreen \n");
    }
    else {
        printf("This Hammer is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(hammer->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(hammer->posY);
    printf("\n");

    if (hammer->state == 1) {
        printf("This Hammer has been used \n");
    }
    else {
        printf("This Hammer has NOT been used \n");
    }
}

void testHeart(Heart *heart) {

    if (heart->visible == 1) {
        printf("The Heart is Visible onscreen \n");
    }
    else {
        printf("The Heart is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(heart->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(heart->posY);
    printf("\n");

    if (heart->broken == 1) {
        printf("The Heart is Broken \n");
    }
    else {
        printf("The Heart is NOT Broken \n");
    }

    printf("Current Animation Timer: ");
    printf(heart->animTimer);
    printf("\n");    
}

void testItem(Item *item) {

    if (item->visible == 1) {
        printf("This Item is Visible onscreen \n");
    }
    else {
        printf("This Item is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(item->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(item->posY);
    printf("\n");

    if (item->type == 1) {
        printf("This is a Purse \n");
    }
    else if (item->type == 2) {
        printf("This is a Hat \n");
    }
    else {
        printf("This is an Umbrella \n");
    }

    printf("This Item has been visible for ");
    printf(item->lifetime);
    printf("\n"); 

}

void testKong(Kong *kong){

        if (kong->visible == 1) {
        printf("DK is Visible onscreen \n");
    }
    else {
        printf("DK is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(kong->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(kong->posY);
    printf("\n");

    if (kong->state == 1) {
        printf("DK is currently Grabbing a Barrel \n");
    }
    else if (kong->state == 2) {
        printf("Kong is currently Throwing a Barrel \n");
    }
    else {
        printf("Kong is currently Idle \n");
    }

    printf("The next Barrel will be thrown in ");
    printf(kong->barrelCooldown);
    printf("\n"); 

}

void testLadder(Ladder *ladder) {
   
    if (ladder->visible == 1) {
        printf("This Ladder is Visible onscreen \n");
    }
    else {
        printf("This Ladder is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(ladder->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(ladder->posY);
    printf("\n");

    printf("This ladder spans horizontally from ");
    printf(ladder->left);
    printf(" to ");
    printf(ladder->right);
    printf("\n");
    printf("This ladder spans vertically from ");
    printf(ladder->top);
    printf(" to ");
    printf(ladder->bottom);
    printf("\n");

    if (ladder->broken == 1) {
        printf("This Ladder is Broken \n");
    }
    else {
        printf("This Ladder is NOT Broken \n");
    }
}

void testLady(Lady *lady) {

    if (lady->visible == 1) {
        printf("Pauline is Visible onscreen \n");
    }
    else {
        printf("Pauline is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(Lady->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(lady->posY);
    printf("\n");

    printf("The Victory Hitbox falls between");
    printf(lady->topL);
    printf(" (Top-Left) and ");
    printf(lady->bottomR);
    printf(" (Bottom-Right) \n");
}

void testLives(Lives *lives) {

    if (lives->visible == 1) {
        printf("The Lives UI is Visible onscreen \n");
    }
    else {
        printf("The Lives UI is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(lives->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(lives->posY);
    printf("\n");

    printf("The Player currently has ");
    printf(lives->value);
    printf(" lives \n");
}

void testMario (Mario *mario) {
    
    if (mario->visible == 1) {
        printf("Mario is Visible onscreen \n");
    }
    else {
        printf("Mario is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(mario->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(mario->posY);
    printf("\n");

    printf("Current x speed: ");
    printf(mario->deltX);
    printf("\n");
    
    printf("Current y speed: ");
    printf(mario->deltY);
    printf("\n");

    if (mario->state == 1) {
        printf("Mario is currently Walking \n");
    }
    else if (mario->state == 2) {
        printf("Mario is currently Climbing");
    }
    else if (mario->state == 3) {
        printf("Mario is currently Jumping");
    }
    else if (mario->state == 4) {
        printf("Mario is currently Dead/Falling Offscreen");
    }
    else {
        printf("Mario is currently Standing \n");
    }

    if (mario->direction == 1) {
        printf("Mario is facing Right \n");
    }
    else {
        printf("Mario is facing Left \n");
    }

    if (mario->climbDir == 1) {
        printf(" Mario is climbing Down \n");
    }
    else {
        printf("Mario is climbing Up \n");
    }

    if (mario->onGround == 1) {
        printf("Mario is on the Ground \n");
    }
    else {
        printf("Mario is in the Air \n");
    }

    if (mario->hammerActive == 1) {
        printf("Mario is using a Hammer \n");

        printf("The hammer has ");
        printf(mario->hammerTimer);
        printf(" left \n");

    }
    else {
        printf("Mario is not using a Hammer \n");
    }
}

void testOil(Oil *oil) {

    if (oil->visible == 1) {
        printf("The Oil Barrel is Visible onscreen \n");
    }
    else {
        printf("The Oil Barrel is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(oil->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(oil->posY);
    printf("\n");

    if (oil->fireCheck == 1) {
        printf("There is a Fire Spirit Alive \n");
    }
    else {
        printf("There is is NOT an alive Fire Spirit \n");
        printf("There has not been one for ");
        printf(oil->noFireTimer);
        printf(" seconds \n");  
    }
    
    if (oil->state == 1) {
        printf("The Oil Barrel is in an Ignited state \n");
    }
    else {
        printf("The Oil Barrel is in a non-ignited state \n");
    }
}

void testScore(Score *score) {

    if (score->visible == 1) {
        printf("The Score UI is Visible onscreen \n");
    }
    else {
        printf("The Score UI is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(score->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(score->posY);
    printf("\n");

    printf("The Player currently has a score of ");
    printf(score->value);
    printf("\n");
}

void testSpirit(Spirit *spirit) {

    if (spirit->visible == 1) {
        printf("The Spirit is Visible onscreen \n");
    }
    else {
        printf("The Spirit is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(spirit->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(spirit->posY);
    printf("\n");

    printf("Current x speed: ");
    printf(spirit->deltX);
    printf("\n");
    
    printf("Current y speed: ");
    printf(spirit->deltY);
    printf("\n");

    if (spirit->state == 1) {
        printf("The Spirit is currently Climbing \n");
    }
    else {
        printf("The Spirit is currently Walking \n");
    }

    if (spirit->direction == 1) {
        printf("The Spirit is facing Right \n");
    }
    else {
        printf("The Spirit is facing Left \n");
    }
}

void testTimer(Timer *timer) {

    if (timer->visible == 1) {
        printf("The Timer UI is Visible onscreen \n");
    }
    else {
        printf("The Timer UI is NOT Visible onscreen \n");
    }    

    printf("Current x pos: ");
    printf(timer->posX);
    printf("\n");
    
    printf("Current y pos: ");
    printf(timer->posY);
    printf("\n");

    printf("The Timer has a current value of ");
    printf(timer->value);
    printf("\n");
}
