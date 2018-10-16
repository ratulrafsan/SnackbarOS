//
// Created by ratulrafsan on 10/11/18.
//

#include <mem/gdt.h>
#include <serial.h>

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
        unsigned int type,
        unsigned int access,
        unsigned int flags
        ){

    // Lets say base is 0x12345678
    gdt[num].base_high = base >> 16; // is 0x1234
    gdt[num].base_mid = (base & 0xffff) >> 8; // is 0x56
    gdt[num].base_low = base & 0xff; // is 0x78

    gdt[num].lim_high = limit & 0xffff;
    gdt[num].lim_low = (limit >> 16) & 0x0f;

    gdt[num].type = type;

    // Access nibble
    // Bits:     | 3 | 2 | 1 | 0 |
    // Contents: | p | priv  | s |
    // s = Descriptor type
    // priv = Privilege level
    // p = present bit
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
    gdt[num].available = 1; // by default lol
    gdt[num].reserved = 1; // Its reserved, meh
    gdt[num].segment_size = (flags >> 2) & 0b1;
    gdt[num].granularity = flags >> 3;

    //serial_printf(SERIAL_COM1_BASE, "%x %b\n", flags, flags);
    //serial_printf(SERIAL_COM1_BASE, "%x %b\n", access, access);

}
