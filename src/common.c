//
// Created by ratulrafsan on 9/27/18.
//

#include <stdint.h>
/*
 * Writes data to port specified by
 */
void outb(uint16_t port, uint8_t data){
    asm volatile ("outb %1, %0" :: "dN" (port), "a" (data));
}

uint8_t inb(uint16_t port){
    uint8_t data;
    asm volatile ("inb %1, %0" : "=r"(data) : "dN"(port));
    return data;
}

uint16_t inw(uint16_t port){
    uint16_t data;
    asm volatile ("inw %1, %0" : "=r"(data) : "dN"(port));
    return data;
}