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
    UINT8 read_reg = read_psg(0);

    printf("Current register is 0 and value is %d\n", read_reg);

    write_psg(0, -1);
    printf("Wrote the value -1 to register 0\n");

    read_reg = read_psg(0);
    printf("Value in register 0 is now %d\n", read_reg);
}

void test_invalid_register() {
    UINT8 read_reg = read_psg(-1);

    printf("Current register is -1 and value is %d\n", read_reg);


}

int main() {

    long old_ssp = Super(0);

    test_invalid_register();

    Super(old_ssp);

    return 0;
}