#include <stdio.h>
#include "music.h"

/*

Remove super from each of the calls and move them to main

*/

int i = 0;

Note *current_note = intro_melody;

UINT32 time_note_started;

void start_music() {

    i = 0;
    current_note = &intro_melody[0];
    time_note_started = 0;

    set_tone(0, current_note->tuning);
    enable_channels(0, 1, 0);
    set_volume(0, 8);
}

void update_music(UINT32 time_elapsed) {
    

    if ((time_elapsed - time_note_started) >= current_note->duration) {

        i = (i + 1) % INTRO_MELODY_LENGTH;
        current_note = &intro_melody[i];
        time_note_started = time_elapsed;
        set_tone(0, current_note->tuning);  
        set_volume(0, 8);
        
    }


}

