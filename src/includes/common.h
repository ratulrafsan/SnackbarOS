//
// Created by ratulrafsan on 9/27/18.
//

#ifndef SNACKBAR_COMMON_H
#define SNACKBAR_COMMON_H

#include <stdint.h>

void        outb(uint16_t port, uint8_t data);
uint8_t     inb(uint16_t port);
uint16_t    inw(uint16_t port);
void        serial_struct_dump(uint16_t com_port, void* ptr_struct, unsigned long size);

#endif //SNACKBAR_COMMON_H
