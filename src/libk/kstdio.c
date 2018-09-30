//
// Created by ratulrafsan on 9/30/18.
//

/*
 * This file contains function definition for common input/output methods to be used in kernel mode
 */

#include <vga.h>

/*
 * Given a character, k_putchar function prints the character in white with black background.
 */
void k_putch(char c){
    vga_write_cell(c, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

/*
 *  Given a pointer to string, this function will print the string upto '\0' & add a '\n' at the end
 */
void k_puts(char* ptr_str){
    while(*ptr_str != '\0'){
        k_putch(*ptr_str++);
    }
    k_putch('\n');
}

/*
 * Given a string and foreground & background color this function prints the string upto '\0' using the given
 * color and adds a '\n' at the end
 */
void k_puts_color(char* ptr_str, uint8_t foreground_color, uint8_t background_color){
    while(*ptr_str != '\0'){
        vga_write_cell(*ptr_str++, foreground_color, background_color);
    }
}

/*
 *  Given a string, k_puts_err will print the string in white with red background
 */
void k_puts_err(char* ptr_str){
    k_puts_color(ptr_str, VGA_COLOR_WHITE, VGA_COLOR_RED);
}


