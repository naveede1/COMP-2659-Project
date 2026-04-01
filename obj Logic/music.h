#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"

typedef struct {
    int tuning;
    int duration;
} Note;
 
#define INTRO_MELODY_LENGTH 79

Note intro_melody[] = {
    {477, 8},   /* C4 (261.63 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {715, 8},   /* F3 (174.61 Hz) */
    {715, 7},   /* F3 (174.61 Hz) */
    {568, 7},   /* A3 (220.0 Hz) */
    {715, 7},   /* F3 (174.61 Hz) */
    {284, 20},  /* A4 (440.0 Hz) */
    {568, 7},   /* A3 (220.0 Hz) */
    {357, 7},   /* F4 (349.23 Hz) */
    {318, 8},   /* G4 (392.0 Hz) */
    {357, 7},   /* F4 (349.23 Hz) */
    {851, 7},   /* D3 (146.83 Hz) */
    {715, 7},   /* F3 (174.61 Hz) */
    {637, 7},   /* G3 (196.0 Hz) */
    {715, 7},   /* F3 (174.61 Hz) */
    {637, 7},   /* G3 (196.0 Hz) */
    {715, 7},   /* F3 (174.61 Hz) */
    {425, 25},  /* D4 (293.66 Hz) */
    {637, 8},   /* G3 (196.0 Hz) */
    {425, 8},   /* D4 (293.66 Hz) */
    {425, 8},   /* D4 (293.66 Hz) */
    {536, 7},   /* A#3 (233.08 Hz) */
    {637, 7},   /* G3 (196.0 Hz) */
    {536, 7},   /* A#3 (233.08 Hz) */
    {637, 7},   /* G3 (196.0 Hz) */
    {268, 20},  /* A#4 (466.16 Hz) */
    {536, 7},   /* A#3 (233.08 Hz) */
    {318, 7},   /* G4 (392.0 Hz) */
    {284, 8},   /* A4 (440.0 Hz) */
    {318, 7},   /* G4 (392.0 Hz) */
    {758, 8},   /* E3 (164.81 Hz) */
    {637, 8},   /* G3 (196.0 Hz) */
    {568, 8},   /* A3 (220.0 Hz) */
    {637, 8},   /* G3 (196.0 Hz) */
    {568, 8},   /* A3 (220.0 Hz) */
    {379, 25},  /* E4 (329.63 Hz) */
    {637, 8},   /* G3 (196.0 Hz) */
    {379, 8},   /* E4 (329.63 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {379, 1},   /* E4 (329.63 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {238, 16},  /* C5 (523.25 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {568, 8},   /* A3 (220.0 Hz) */
    {284, 16},  /* A4 (440.0 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {357, 7},   /* F4 (349.23 Hz) */
    {379, 8},   /* E4 (329.63 Hz) */
    {284, 7},   /* A4 (440.0 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {268, 8},   /* A#4 (466.16 Hz) */
    {568, 9},   /* A3 (220.0 Hz) */
    {238, 7},   /* C5 (523.25 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {357, 8},   /* F4 (349.23 Hz) */
    {212, 16},  /* D5 (587.33 Hz) */
    {425, 8},   /* D4 (293.66 Hz) */
    {536, 8},   /* A#3 (233.08 Hz) */
    {268, 16},  /* A#4 (466.16 Hz) */
    {425, 8},   /* D4 (293.66 Hz) */
    {357, 8},   /* F4 (349.23 Hz) */
    {318, 16},  /* G4 (392.0 Hz) */
    {425, 8},   /* D4 (293.66 Hz) */
    {357, 8},   /* F4 (349.23 Hz) */
    {536, 9},   /* A#3 (233.08 Hz) */
    {318, 7},   /* G4 (392.0 Hz) */
    {425, 8},   /* D4 (293.66 Hz) */
    {477, 8},   /* C4 (261.63 Hz) */
    {568, 8},   /* A3 (220.0 Hz) */
    {477, 4},   /* C4 (261.63 Hz) */
    {568, 3},   /* A3 (220.0 Hz) */
    {715, 3},   /* F3 (174.61 Hz) */
    {568, 3},   /* A3 (220.0 Hz) */
    {284, 20},  /* A4 (440.0 Hz) */
    {477, 15},  /* C4 (261.63 Hz) */
    {379, 7},   /* E4 (329.63 Hz) */
    {357, 8},   /* F4 (349.23 Hz) */
    {318, 7},   /* G4 (392.0 Hz) */
    {568, 17},  /* A3 (220.0 Hz) */
};


/*----- Function: start_music -----

Begins the playing of the song by loading the data for the first note into the PSG

*/
void start_music();

/*----- Function: update_music -----

Advances to the next note of the song if necessary, as determined by the amount of
time elapsed since the previous call. The time elapsed is determined by the caller. It is
intended that this value is equal to the current value of the vertical blank clock, minus
its value when the function was last called

*/
void update_music(UINT32 time_elapsed);

#endif