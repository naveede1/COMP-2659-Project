#ifndef PSG_DRV_H
#define PSG_DRV_H

#include "psg.c"

void test_write_read_psg();
void test_boundary_values();
void test_invalid_register();

void test_set_tone_fine();
void test_set_coarse_and_fine();
void test_set_tone_boundary_values();

void test_set_volume_min();
void test_set_volume_max();
void test_set_volume_overflow();

void test_stop_sound_all();
void test_stop_sound_when_stopped();

#endif