//
// Created by ratulrafsan on 9/30/18.
//

/*
 * This file contains function definition for common input/output methods to be used in kernel mode
 */

#include <vga.h>

/**
 * Print character @param c to screen.
 * @param c  : Character to print
 */
void k_putch(char c){
    vga_write_cell(c, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

/**
 * Prints string pointed by @param ptr_str to screen.
 * @param ptr_str   : Pointer to string buffer to read from.
 */
void k_puts(char* ptr_str){
    while(*ptr_str != '\0'){
        k_putch(*ptr_str++);
    }
    k_putch('\n');
}


/**
 * Prints @param ptr_str with foreground color as @param foreground_color & background color as @param background_color
 * It also prints a new line character ('\n') at the end.
 * @param ptr_str           : Pointer to string buffer to read from
 * @param foreground_color
 * @param background_color
 */
void k_puts_color(char* ptr_str, uint8_t foreground_color, uint8_t background_color){
    while(*ptr_str != '\0'){
        vga_write_cell(*ptr_str++, foreground_color, background_color);
    }
}

/**
 * Prints @param ptr_str with white foreground and red background color
 * @param ptr_str : Pointer to string buffer to read from.
 */
void k_puts_err(char* ptr_str){
    k_puts_color(ptr_str, VGA_COLOR_WHITE, VGA_COLOR_RED);
}


