//
// Created by ratulrafsan on 9/27/18.
//

#ifndef SNACKBAR_COMMON_H
#define SNACKBAR_COMMON_H

#include <stdint.h>

void        outb(uint16_t port, uint8_t data);
uint8_t     inb(uint16_t port);
uint16_t    inw(uint16_t port);

#endif //SNACKBAR_COMMON_H
