#include <stdint.h>
#include <vga.h>
#include <kstdio.h>
#include <common.h>
#include <serial.h>
#include <string.h>
#include <mem/gdt.h>
#include <grub/multiboot.h>

int k_main(multiboot_info_t* multiboot_info, unsigned int magic){
    serial_default_config(SERIAL_COM1_BASE, 1);

    serial_printf(SERIAL_COM1_BASE, "Multiboot info address %x\n", multiboot_info);
    serial_printf(SERIAL_COM1_BASE, "Magic number  %x\n", magic);

    gdt_set_gate(0, 0, 0xfffff, CODE_EXECUTE_READ, ACCESS_BYTE_KERNEL_CODE_SEGMENT, FOUR_KB_32_BIT);

    serial_struct_dump(SERIAL_COM1_BASE, gdt, sizeof(gdt_entry_t));

    vga_clear_screen();

    return 0x0DEADBABA;
}
