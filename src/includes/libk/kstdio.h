//
// Created by ratulrafsan on 9/30/18.
//

#ifndef SNACKBAR_KSTDIO_H
#define SNACKBAR_KSTDIO_H

#include <stdint.h>

void        k_putch(char c);
void        k_puts_err(char* ptr_str);
void        k_puts(char* ptr_str);
void        k_puts_color(char* c, uint8_t fg_color, uint8_t bg_color);

#endif //SNACKBAR_KSTDIO_H
