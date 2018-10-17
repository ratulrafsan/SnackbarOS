//
// Created by ratulrafsan on 10/11/18.
//

#include <mem/gdt.h>
#include <serial.h>


void print_gdt_entry(gdt_entry_t gdt_entry){
    #define print(X, Y) serial_printf(SERIAL_COM1_BASE, X, Y);

    print("Limit low: %b\n", gdt_entry.lim_low);
    print("base low: %b\n", gdt_entry.base_low);
    print("base mid: %b\n", gdt_entry.base_mid);
    print("type: %b\n", gdt_entry.type);
    print("s: %b\n", gdt_entry.s);
    print("Priv: %b\n", gdt_entry.previlege);
    print("Present: %b\n", gdt_entry.present);
    print("Limit high: %b\n", gdt_entry.lim_high);
    print("Available: %b\n", gdt_entry.available);
    print("Reserved: %b\n", gdt_entry.reserved);
    print("Segment size: %b\n", gdt_entry.segment_size);
    print("Granularity: %b\n", gdt_entry.granularity);
    print("Base high: %b\n", gdt_entry.base_high);
}

/**
 * Set a GDT descriptor
 *
 * @param num The number for the descriptor to set
 * @param base Segment base address
 * @param limit Segment limit
 * @param type Type of segment (See segment type definition in gdt.h)
 * @param access Access nibble (See common access nibble definitions in gdt.h)
 * @param flags Flags for the granularity nibble (
 */

void gdt_set_gate(
        int num,
        uint32_t base,
        uint32_t limit,
        unsigned int access,
        unsigned int flags
        ){

    // Lets say base is 0x12345678
    gdt[num].base_high = base >> 16; // is 0x1234
    gdt[num].base_mid = (base & 0xffff) >> 8; // is 0x56
    gdt[num].base_low = base & 0xff; // is 0x78

    gdt[num].lim_high = (limit >> 16) & 0x0f;
    gdt[num].lim_low = limit & 0xffff;

    gdt[num].type = access & 0b1111;

    // Access nibble
    // Bits:     | 3 | 2 | 1 | 0 |
    // Contents: | p | priv  | s |
    // s = Descriptor type
    // priv = Privilege level
    // p = present bit
    access = access >> 4; // Strip segment type info from access byte
    gdt[num].s = access & 0b1;
    gdt[num].previlege = (access >> 1) & 0b11;
    gdt[num].present = access >> 3;

    // Flag nibble
    // Bits:     | 3 | 2 | 1 | 0 |
    // Contents: | g | s | r | a |
    // g = granularity bit
    // s = segment size
    // r = reserved by intel
    // a = available for software use
    gdt[num].available = 0; // by default lol
    gdt[num].reserved = 0; // Its reserved, meh
    gdt[num].segment_size = (flags >> 2) & 0b1;
    gdt[num].granularity = flags >> 3;

    //serial_printf(SERIAL_COM1_BASE, "%x %b\n", flags, flags);
    //serial_printf(SERIAL_COM1_BASE, "%x %b\n", access, access);
    //print_gdt_entry(gdt[num]);
}

/**
 *  Sets up a new GDT with some default values, flushes the old GDT setup by GRUB and loads this one.
 *  Most values are hard coded for now. Segmentation will later be dumped for
 *  paging, so I won't spend much time making it dynamic.
 */
void gdt_install(){

    gdt_ptr.limit = (sizeof(gdt_entry_t)*5) - 1; //5 because there will be 5 gdt entries (see below)
    gdt_ptr.base = (uint32_t)gdt;

    // Null descriptor
    gdt_set_gate(0, 0, 0, 0, 0);
    // Kernel Code segment
    gdt_set_gate(1, 0, 0xffffffff, ACCESS_BYTE_KERNEL_CODE_SEGMENT, FLAG_FOUR_KB_32_BIT);
    // Kernel data segment
    gdt_set_gate(2, 0, 0xffffffff, ACCESS_BYTE_KERNEL_DATA_SEGMENT, FLAG_FOUR_KB_32_BIT);
    // User code segment
    gdt_set_gate(3, 0, 0xffffffff, ACCESS_BYTE_USER_CODE_SEGMENT, FLAG_FOUR_KB_32_BIT);
    // User data segment
    gdt_set_gate(4, 0, 0xffffffff, ACCESS_BYTE_USER_DATA_SEGMENT, FLAG_FOUR_KB_32_BIT);

    // Flush the old gdt and load this new gdt
    gdt_flush((uint32_t)&gdt_ptr);
}

