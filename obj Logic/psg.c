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
#define CONSOLE_PTR    ((volatile char *)0x000484)

volatile unsigned char *PSG_reg_select = 0xFF8800; 
volatile unsigned char *PSG_reg_write = 0xFF8802;


void write_psg(int reg, UINT8 val) {
    if ((0 <= reg) && (reg <= 15)) {
        *PSG_reg_select = reg;
	    *PSG_reg_write  = val;
    } else {
       printf("%d is a invalid register\n", reg);
    }
}

UINT8 read_psg(int reg) {
    if ((0 <= reg) && (reg <= 15)) {
        *PSG_reg_select = reg;
        return *PSG_reg_select;
    }

    printf("%d is a invalid register\n", reg);
}

void set_tone(int channel, int tuning) {
    if ((0 <= channel) && (channel <= 2)) {
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
    } else {
        printf("%d is not a valid channel.\n", channel);
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

    /*
    
    Add arguement checks

    */

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

void toggle_keyboard_sound() {
    long old_ssp = Super(0);
    UINT8 console_byte = *CONSOLE_PTR ^ 0x01; /* Invert bit 0 to flip keyboard sound */
    *CONSOLE_PTR = console_byte;
    Super(old_ssp);
}