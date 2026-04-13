#include "music.h"

/*
    Purpose:
    Handles song playback state for the intro melody.

    Notes:
    - This version is intended to be called from the VBL ISR.
    - Do NOT use Super() here.
    - PSG access happens directly when update_music() advances notes.
*/

int i = 0;
Note *current_note = intro_melody;
UINT32 time_note_started = 0;

/*
    Purpose:
    Initializes music playback state and starts the first note.
*/
void start_music(void)
{
    i = 0;
    current_note = &intro_melody[0];
    time_note_started = 0;

    set_tone(0, current_note->tuning);
    enable_channels(0, 1, 0);
    set_volume(0, 8);
}

/*
    Purpose:
    Advances the melody when the current note duration has elapsed.

    Parameters:
    - time_elapsed: current tick count, expected to come from VBL timing.

    Notes:
    - Call this from do_vbl_isr().
*/
void update_music(UINT32 time_elapsed)
{
    if ((time_elapsed - time_note_started) >= current_note->duration)
    {
        i = (i + 1) % INTRO_MELODY_LENGTH;
        current_note = &intro_melody[i];
        time_note_started = time_elapsed;

        set_tone(0, current_note->tuning);
        set_volume(0, 8);
    }
}