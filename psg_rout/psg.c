#include "psg.h"

/* 

TO DO:

    **Each function must validate its input parameters. If an input value is out-of-range, 
    the function must ignore the request.

    **Change typings to UINT8 where needed

    **According to Parker using write_psg is slower then just:
        
        *PSG_reg_select = reg;
	    *PSG_reg_write  = val;

*/

volatile unsigned char *PSG_reg_select = 0xFF8800; 
volatile unsigned char *PSG_reg_write = 0xFF8802;

void write_psg(int reg, UINT8 val) {

    /* 
    
    Add arguement check:

    Only 16 registers and only byte values between 0-255
    
    */

    *PSG_reg_select = reg;
	*PSG_reg_write  = val;
}

UINT8 read_psg(int reg) {

    /* 
    
    Add arguement check:

    Limited amount of registers, between 0-F which is 1-16 
    
    */

    *PSG_reg_select = reg;
    return *PSG_reg_select;
}

void set_tone(int channel, int tuning) {

    /*
    
    Add arguement checks
    
    */

    int fine_tone;
    int rough_tone;

    fine_tone = tuning & 0xFF;
    rough_tone = tuning >> 8;
    
    if (channel == 0) {
        write_psg(0, fine_tone);
        write_psg(1, rough_tone);
    } else if (channel == 1) {
        write_psg(2, fine_tone);
        write_psg(3, rough_tone);
    } else {
        write_psg(4, fine_tone);
        write_psg(5, rough_tone);
    }

}

void set_volume(int channel, int volume) {

    /*
    
    Add arguement checks

    */

    volume = volume & 0x0F;

    if (channel == 0) {
        write_psg(8, volume);
    } else if (channel == 1) {
        write_psg(9, volume);
    } else {
        write_psg(10, volume);
    }
}

void enable_channels(int channel, int tone_on, int noise_on) {

    UINT8 reg_7_value;
    UINT8 tone;
    UINT8 noise;

    reg_7_value = read_psg(7);

    tone &= ~(1 << channel); /* Tone bit position depending on the channel */
    noise &= ~(1 << (channel + 3)); /* Noise bit position depending on the channel */

    /* Set tone bit */
    if (tone_on == 0) {
        reg_7_value |= (1 << channel);
    }

    /* Set tone bit */
    if (noise_on == 0) {
        reg_7_value |= (1 << (channel + 3));
    }

    write_psg(7, reg_7_value);
}

void stop_sound() {
    write_psg(8, 0);
    write_psg(9, 0);
    write_psg(10, 0);  
}