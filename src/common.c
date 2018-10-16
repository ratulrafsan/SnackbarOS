//
// Created by ratulrafsan on 9/27/18.
//

#include <stdint.h>
#include <serial.h>

/**
 * Writes 8 bit @param data to port speicifed by @param port
 * @param port : 16 bit port address.
 * @param data : 8 bit data to write.
 */
void outb(uint16_t port, uint8_t data){
    asm volatile ("outb %1, %0" :: "dN" (port), "a" (data));
}

/**
 * Reads 8 bit data form @param port
 * @param port  : 16 bit port address
 * @return data : 8 bit data read from @param port
 */
uint8_t inb(uint16_t port){
    uint8_t data;
    asm volatile ("inb %1, %0" : "=r"(data) : "dN"(port));
    return data;
}

/**
 * Reads 16 bit data from @param port
 * @param port : 16 bit port address
 * @return dat : 8 bit data read from @param port
 */
uint16_t inw(uint16_t port){
    uint16_t data;
    asm volatile ("inw %1, %0" : "=r"(data) : "dN"(port));
    return data;
}

/**
 * Simple function to dump a struct to serial output
 * See http://stackoverflow.com/questions/6687500/how-do-i-dump-and-arbitary-struct-in-c
 * @param com_port Port to write to
 * @param ptr_struct Pointer to the struct you want to dump
 * @param size Size of the struct
 */
void serial_struct_dump(uint16_t com_port, void* ptr_struct, unsigned long size){
    const unsigned char* const px = (unsigned char*)ptr_struct;
    for(unsigned int i = 0; i < size; i++){
        if( i % (sizeof(int) * 8) == 0){
            serial_printf(com_port, "\n %b ", i);
        }else if( i % 4 == 0){
            serial_printf(com_port, " ");
        }
        serial_printf(com_port, "%b", px[i]);
    }
}