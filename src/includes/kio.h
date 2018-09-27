//
// Created by ratulrafsan on 9/23/18.
//

#ifndef SNACKBAR_KIO_H
#define SNACKBAR_KIO_H

#endif //SNACKBAR_KIO_H

#include "clib/ministdint.h"

// Color definitions
#define VGA_COLOR_BLACK 0
#define VGA_COLORBLUE 1
#define VGA_COLOR_GREEN 2
#define VGA_COLOR_CYAN 3
#define VGA_COLOR_RED 4
#define VGA_COLORMAGENTA 5
#define VGA_COLORBROWN 6
#define VGA_COLORLIGHT_GRAY 7
#define VGA_COLORDARK_GREY 8
#define VGA_COLOR_LIGHT_BLUE 9
#define VGA_COLORLIGHT_GREEN 10
#define VGA_COLORLIGHT_CYAN 11
#define VGA_COLORLIGHT_RED 12
#define VGA_COLORLIGHT MAGENTA 13
#define VGA_COLOR_LIGHT_BROWN 14
#define VGA_COLOR_WHITE 15


void        outb(uint16_t port, uint8_t data);
uint8_t     inb(uint16_t port);
uint16_t    inw(uint16_t port);
void        k_write_cell(char, uint8_t fg_color, uint8_t bg_color);
void        k_clear_screen();
void        k_putchar(char c);
void        k_putserr(char* c);
void        k_puts(char* str);
void        k_puts_color(char* c, uint8_t fg_color, uint8_t bg_color);
void        move_cursor();