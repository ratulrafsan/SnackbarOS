#include <stdint.h>
#include <vga.h>
#include <kstdio.h>
#include <common.h>
#include <serial.h>
#include <string.h>
#include <grub/multiboot.h>

int k_main(multiboot_info_t* multiboot_info, unsigned int magic){
    serial_default_config(SERIAL_COM1_BASE, 1);

    serial_printf(SERIAL_COM1_BASE, "Multiboot info address %x\n", multiboot_info);
    serial_printf(SERIAL_COM1_BASE, "Magic number  %x\n", magic);

    vga_clear_screen();
    //vga_write_cell('t', VGA_COLOR_CYAN, VGA_COLOR_WHITE);
    serial_puts(SERIAL_COM1_BASE, "[DEBUG | INFO] configured serial communication port 1");
    serial_printf(SERIAL_COM1_BASE, "%d + %d = %i; %s %b + %B = %b; %s %x + %X = %x\n ", 10, 20, 10+20, "or in binary we can say",
            10, 20, 10+20, "and finally in hex..", 10, 20, 10+20);
    vga_set_blink_mode(false);// DOESN'T WORK
    k_puts_color("BLK TXT\n", VGA_COLOR_RED, VGA_COLOR_WHITE);


    return 0x0DEADBABA;
}
