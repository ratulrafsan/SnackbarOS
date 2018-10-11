#include <stdint.h>
#include <vga.h>
#include <kstdio.h>
#include <common.h>
#include <serial.h>
#include <string.h>

int k_main(){
    vga_clear_screen();
    //vga_write_cell('t', VGA_COLOR_CYAN, VGA_COLOR_WHITE);
    serial_default_config(SERIAL_COM1_BASE, 1);
    serial_puts(SERIAL_COM1_BASE, "[DEBUG | INFO] configured serial communication port 1");
    serial_printf(SERIAL_COM1_BASE, "%d + %d = %i; %s %b + %B = %b; %s %x + %X = %x\n ", 10, 20, 10+20, "or in binary we can say",
            10, 20, 10+20, "and finally in hex..", 10, 20, 10+20);
    vga_set_blink_mode(false);// DOESN'T WORK
    k_puts_color("BLK TXT\n", VGA_COLOR_RED, VGA_COLOR_WHITE);


    return 0x0DEADBABA;
}
