//
// Created by ratulrafsan on 9/27/18.
//

#include <stdint.h>

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