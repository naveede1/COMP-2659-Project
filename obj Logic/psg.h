#ifndef PSG_H
#define PSG_H

#include <osbind.h>
#include <stdio.h>

#include "types.h"

/*----- Function: write_psg -----

Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper
routine to be used by the other functions in this module

*/
void write_psg(int reg, UINT8 val);

/*----- Function: read_psg -----

Selects a register and then prints/reads back the value currently stored in it

*/
UINT8 read_psg(int reg);

/*----- Function: set_tone -----

Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C) with the
given 12-bit tuning

*/
void set_tone(int channel, int tuning);

/*----- Function: set_volume -----

Loads the volume register for the given channel

*/
void set_volume(int channel, int volume);

/*----- Function: enable_channels -----

Turns the given channel’s tone/noise signals on/off (0=off, 1=on)

*/
void enable_channels(int channel, int tone_on, int noise_on);

/*----- Function: stop_sound -----

Silences all PSG sound production

*/
void stop_sound();

/*----- Function: toggle_keyboard_sound -----
        
Toggles on/off sound of keyboard input. 

This function is written by Parker Hutcherson.

*/
void toggle_keyboard_sound();

#endif