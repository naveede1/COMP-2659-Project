#include "effects.h"
#include "psg.c"

/* From Parker */
static void wait(unsigned int cycles) {
  volatile unsigned int i;
  for (i = 0; i < cycles; i++) {
    /* Do nothing, just waste time */
  }
}

void play_jump_effect() {
    set_tone(2, 450);
    set_envelope(9, 8000);
    set_volume(2, 16);
    enable_channels(2, 1, 0);
}

void play_hammer_effect() {
    set_noise(16);
    set_envelope(8, 600);
    set_volume(2, 16);
    enable_channels(2, 0, 1);
}

int main() {
    long old_ssp;

	old_ssp = Super(0);

    play_jump_effect();

    while (!Cconis())
        ;   
    
	Super(old_ssp);

    return 0;
}