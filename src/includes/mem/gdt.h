//
// Created by ratulrafsan on 10/11/18.
//

#ifndef SNACKBAR_GDT_H
#define SNACKBAR_GDT_H

#include <stdint.h>

// Segment type definition
#define DATA_READ_ONLY              0b0000
#define DATA_READ_WRITE             0b0010
#define STACK_READ_ONLY             0b0010
#define STACK_READ_WRITE            0b1100
#define CODE_EXECUTE_ONLY           0b0010
#define CODE_EXECUTE_READ           0b1010
#define CODE_CONFORM_EXECUTE_ONLY   0b0110
#define CODE_CONFORM_EXECUTE_READ   0b1110

// Privilege level; Layout: Present bit(1) | DPL bits(2)
#define DPL_KERNEL                  0b1000 // Ring zero
#define DPL_DRIVER                  0b1010 // Drivers only
#define DPL_USER                    0b1110 // Ring three, user mode

// Descriptor type
#define DESCRIPTOR_SYSTEM           0b0000 // What is this used for?
#define DESCRIPTOR_CDS              0b0001 // CDS = Code Data Stack

// Segment flags
#define ONE_BYTE_16_BIT             0b0000 // 16 bit mode with 1 byte granularity
#define ONE_BYTE_32_BIT             0b0100 // 32 bit mode with 1 byte granularity
#define FOUR_KB_16_BIT              0b1000 // 16 bit mode with 4KB granularity
#define FOUR_KB_32_BIT              0b1100 // 32 bit mode with 4KB granularity

// Common access nibble definitions
#define ACCESS_BYTE_KERNEL_CODE_SEGMENT     ((DESCRIPTOR_CDS | DPL_KERNEL) << 4) | CODE_EXECUTE_READ
#define ACCESS_BYTE_KERNEL_DATA_SEGMENT     ((DESCRIPTOR_CDS | DPL_KERNEL) << 4) | DATA_READ_WRITE
#define ACCESS_BYTE_USER_CODE_SEGMENT       ((DESCRIPTOR_CDS | DPL_USER)   << 4) | CODE_EXECUTE_READ
#define ACCESS_BYTE_USER_DATA_SEGMENT       ((DESCRIPTOR_CDS | DPL_USER)   << 4) | DATA_READ_WRITE

struct gdt_ptr_struct{
    uint16_t limit; // upper 16 bits of all sector limits
    uint32_t base; // address of first gdt entry
}__attribute__((packed));

// lim_low + base_low + base_mid + type + s + priv + present
struct gdt_entry_struct{
    unsigned int lim_low       : 16; // Low 16 bits of segment limit

    unsigned int base_low      : 16; // Low 16 bits of segment base address
    unsigned int base_mid     :  8; // Middle 8 bits of segment base address

    //Access byte
    unsigned int type           :  4; // Segment type
    unsigned int s              :  1; // Descriptor type, 0 = system, 1 = Code, data, segment
    unsigned int previlege      :  2; // Descriptor privilege level
    unsigned int present        :  1; // Present bit. Must be 1 for all valid sectors

    //Flag/granularity byte
    unsigned int lim_high      :  4; // High 4 bits of segment limit

    unsigned int available      :  1; // Unused bit. Available for software use
    unsigned int reserved       :  1; // Reserved bit. Set it to 0
    unsigned int segment_size   :  1; // 0 = 16 bit segment, 1 = 32 bit segment
    unsigned int granularity    :  1; // Limit scaled by 4K when set.

    unsigned int base_high     :  8; // High 8 bits of segment base address

}__attribute__((packed));

typedef struct gdt_entry_struct gdt_entry_t;
typedef struct gdt_ptr_struct gdt_ptr_t;

gdt_entry_t gdt[3];
gdt_ptr_t gdt_ptr;

void gdt_set_gate(int num, uint32_t base, uint32_t limit, unsigned int type,
        unsigned int access, unsigned int flags);





#endif //SNACKBAR_GDT_H
