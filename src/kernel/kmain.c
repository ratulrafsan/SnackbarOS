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

    vga_clear_screen();

    gdt_install();
    /* Good heavens, it finally works :') At times like this, you realize that writing a good enough OS takes a lot of time.
     * Global Descriptor Table (base=0x0000000000103000, limit=39):
      GDT[0x00]=??? descriptor hi=0x00000000, lo=0x00000000
      GDT[0x01]=Code segment, base=0x00000000, limit=0xffffffff, Execute/Read, Non-Conforming, Accessed, 32-bit
      GDT[0x02]=Data segment, base=0x00000000, limit=0xffffffff, Read/Write, Accessed
      GDT[0x03]=Code segment, base=0x00000000, limit=0xffffffff, Execute/Read, Non-Conforming, 32-bit
      GDT[0x04]=Data segment, base=0x00000000, limit=0xffffffff, Read/Write
     */

    //asm("xchg %bx, %bx"); // bochs magic breakpoint

    return 0x0DEADBABA;
}
