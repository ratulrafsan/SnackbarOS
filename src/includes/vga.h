//
// Created by ratulrafsan on 9/23/18.
//

#ifndef SNACKBAR_VGA_H
#define SNACKBAR_VGA_H

#include <stdint.h>
#include <stdbool.h>

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

#define VGA_TUI_FRAME_BUFFER_START  0x000B8000
#define VGA_CURSOR_HIGH_BYTE        14
#define VGA_CURSOR_LOW_BYTE         15
#define VGA_CURSOR_ATTRIB_PORT      0x3D4
#define VGA_CURSOR_DATA_PORT        0x3D5
#define VGA_ISR_PORT                0x3DA
#define VGA_ATTRIB_DATA_REG_PORT    0x3C0
#define VGA_ATTRIB_DATA_READ_PORT   0x3C1

void        vga_write_cell(char, uint8_t fg_color, uint8_t bg_color);
void        vga_clear_screen();
void        vga_set_blink_mode(bool blink); //TODO: IMPLEMENT vga blinking control function

#endif //SNACKBAR_VGA_H