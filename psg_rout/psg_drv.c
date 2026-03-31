#include "psg_drv.h"

void test_write_read_psg() {

    UINT8 read_reg = read_psg(0);

    printf("Current register is 0 and value is %d\n", read_reg);

    write_psg(0, 64);
    printf("Wrote the value 64 to register 0\n");

    read_reg = read_psg(0);
    printf("Value in register 0 is now %d\n", read_reg);

    read_reg = read_psg(2);
    
    printf("Current register is 2 and value is %d\n", read_reg);

    write_psg(0, 77);
    printf("Wrote the value 77 to register 2\n");

    read_reg = read_psg(0);
    printf("Value in register 2 is now %d\n", read_reg);

}

void test_boundary_values() {

    /*
    
    With the properties of UINT8, If any values less than 0 and greater than
    255 should just wrap around

    */

    UINT8 read_reg = read_psg(0);

    printf("Current register is 0 and value is %d\n", read_reg);

    write_psg(0, -1);
    printf("Wrote the value -1 to register 0\n");

    read_reg = read_psg(0);
    printf("Value in register 0 is now %d\n", read_reg);

    printf("Current register is 0 and value is %d\n", read_reg);

    write_psg(0, 256);
    printf("Wrote the value 256 to register 0\n");

    read_reg = read_psg(0);
    printf("Value in register 0 is now %d\n", read_reg);
}

void test_invalid_register() {
    printf("Bound checks for write_psg():\n");
    printf("----------------------------\n"); 
    write_psg(-1, 200);
    write_psg(16, 200);
    write_psg(0, 200); /* No message for the following */
    printf("----------------------------\n\n"); 

    printf("Bound checks for read_psg():\n");
    printf("----------------------------\n"); 
    read_psg(-1);
    read_psg(16);
    read_psg(0); /* No message for the following */
    printf("----------------------------\n\n"); 
}

void test_set_tone_fine() {

    /*
    
    Pass in a value that is less than 256, so fine is set to
    a value and coarse is 0

    Addititionally sets tone for all channels
    
    */

    set_tone(0, 255);

    printf("Channel A:\n");
    printf("----------------------------\n"); 
    printf("Value of register 0(fine) is: %d\n", read_psg(0));
    printf("Value of register 1(coarse) is: %d\n", read_psg(1));
    printf("----------------------------\n\n");     

    set_tone(1, 200);

    printf("Channel B:\n");
    printf("----------------------------\n"); 
    printf("Value of register 2(fine) is: %d\n", read_psg(2));
    printf("Value of register 3(coarse) is: %d\n", read_psg(3));
    printf("----------------------------\n\n"); 

    set_tone(2, 170);

    printf("Channel C:\n");
    printf("----------------------------\n"); 
    printf("Value of register 4(fine) is: %d\n", read_psg(4));
    printf("Value of register 5(coarse) is: %d\n", read_psg(5));
    printf("----------------------------\n\n"); 
}

void test_set_coarse_and_fine() {

    /*
    
    Any value greater than 255 will set fine and coarse to
    a value
    
    */

    set_tone(0, 256);

    printf("Channel A:\n");
    printf("----------------------------\n"); 
    printf("Value of register 0(fine) is: %d\n", read_psg(0));
    printf("Value of register 1(coarse) is: %d\n", read_psg(1));
    printf("----------------------------\n\n");     

    set_tone(1, 280);

    printf("Channel B:\n");
    printf("----------------------------\n");     
    printf("Value of register 2(fine) is: %d\n", read_psg(2));
    printf("Value of register 3(coarse) is: %d\n", read_psg(3));
    printf("----------------------------\n\n"); 

    set_tone(2, 300);

    printf("Channel C:\n");
    printf("----------------------------\n"); 
    printf("Value of register 4(fine) is: %d\n", read_psg(4));
    printf("Value of register 5(coarse) is: %d\n", read_psg(5));
    printf("----------------------------\n\n");
}

void test_set_tone_boundary_values() {
    set_tone(3, 250);
    set_tone(-1, 250);
}

void test_set_volume_min() {

    /*
    
    Set all volume channels to 0, the lowest volume
    
    */

    set_volume(0, 0);

    printf("Channel A:\n");
    printf("----------------------------\n"); 
    printf("Value of register 8 is: %d\n", read_psg(8));
    printf("----------------------------\n\n");

    set_volume(1, 0);

    printf("Channel B:\n");
    printf("----------------------------\n"); 
    printf("Value of register 9 is: %d\n", read_psg(9));
    printf("----------------------------\n\n");

    set_volume(2, 0);

    printf("Channel C:\n");
    printf("----------------------------\n"); 
    printf("Value of register 10 is: %d\n", read_psg(10));
    printf("----------------------------\n\n");
}

void test_set_volume_max() {

    /*
    
    Set all volume channels to 15, the lowest volume
    
    */

    set_volume(0, 15);

    printf("Channel A:\n");
    printf("----------------------------\n"); 
    printf("Value of register 8 is: %d\n", read_psg(8));
    printf("----------------------------\n\n");

    set_volume(1, 15);

    printf("Channel B:\n");
    printf("----------------------------\n"); 
    printf("Value of register 9 is: %d\n", read_psg(9));
    printf("----------------------------\n\n");

    set_volume(2, 15);

    printf("Channel C:\n");
    printf("----------------------------\n"); 
    printf("Value of register 10 is: %d\n", read_psg(10));
    printf("----------------------------\n\n");
}

void test_set_volume_overflow() {

    /*
    
    If the value for volume exceeds 4 bits, the mask should just clear
    the rest and not ouput garbage
    
    */

    set_volume(0, 16);

    printf("Channel A:\n");
    printf("----------------------------\n"); 
    printf("Value of register 8 is: %d\n", read_psg(8));
    printf("----------------------------\n\n");    

}

void test_stop_sound_all() {

    stop_sound();

    printf("Channel A:\n");
    printf("----------------------------\n"); 
    printf("Value of register 8 is: %d\n", read_psg(8));
    printf("----------------------------\n\n");

    printf("Channel B:\n");
    printf("----------------------------\n"); 
    printf("Value of register 9 is: %d\n", read_psg(9));
    printf("----------------------------\n\n");

    printf("Channel C:\n");
    printf("----------------------------\n"); 
    printf("Value of register 10 is: %d\n", read_psg(10));
    printf("----------------------------\n\n");
}

void test_stop_sound_when_stopped() {

    /*
    
    Stop sound twice to ensure nothing unintended happens
    
    */

    test_stop_sound_all();
    test_stop_sound_all();
}

void test_min_noise() {
    set_noise(10); /* Originally set to 0 */
    printf("Current value in register 6: %d\n", read_psg(6));
    set_noise(0);
    printf("New value in register 6: %d\n", read_psg(6));
}

void test_max_noise() {
    printf("Current value in register 6: %d\n", read_psg(6));
    set_noise(31);
    printf("New value in register 6: %d\n", read_psg(6));
}

void test_noise_overflow() {

    /* 
    
    32 -> 0
    33 -> 1
    34 -> 2
    
    */

    printf("Current value in register 6: %d\n", read_psg(6));
    set_noise(34);
    printf("New value in register 6: %d\n", read_psg(6));
}

void test_min_sustain_value() {
    set_envelope(1, 600);
    printf("Current value in register 11: %d\n", read_psg(11));
    printf("Current value in register 12: %d\n", read_psg(12));

    set_envelope(1, 0);
    printf("Current value in register 11: %d\n", read_psg(11));
    printf("Current value in register 12: %d\n", read_psg(12));
}

void test_max_sustain_value() {
    set_envelope(1, 65535);
    printf("Current value in register 11: %d\n", read_psg(11));
    printf("Current value in register 12: %d\n", read_psg(12));
}

void test_envelope_shape_boundaries() {
    set_envelope(-1, 600);
    set_envelope(16, 600);
}

void test_envelope_sustain_boundaries() {

    /*
    
    Because sustain is unsigned, make sure it wraps around
    
    */

    set_envelope(1, -1);
    printf("Current value in register 11: %d\n", read_psg(11));
    printf("Current value in register 12: %d\n", read_psg(12));

    set_envelope(1, 65536);
    printf("Current value in register 11: %d\n", read_psg(11));
    printf("Current value in register 12: %d\n", read_psg(12));
}

int main() {
	long old_ssp = Super(0);

    test_envelope_shape_boundaries();

	Super(old_ssp);
    return 0;
}