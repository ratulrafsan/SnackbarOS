//
// Created by ratulrafsan on 9/23/18.
//

#include "includes/clib/ministdint.h"
#include "includes/magicaddr.h"
#include "includes/kio.h"

uint16_t *fb = (uint16_t *) VGA_3_FRAME_BUFFER_START;
uint8_t cur_x = 0;
uint8_t cur_y = 0;

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

void k_write_cell(char c, uint8_t fg_color, uint8_t bg_color){
    uint16_t *writePos;

    if(c == '\n'){
        cur_x = 0;
        cur_y++;
    }else if(c == '\t'){
        if ((cur_x + 4) < 80){
            cur_x += 4;
        }
    }
    else {
        //else its just a usual character
        uint8_t attribByte = (bg_color << 4) | (fg_color & 0x0F);
        uint16_t colorData = attribByte << 8;

        writePos = fb + (cur_y * 80 + cur_x);
        *writePos = c | colorData;
        cur_x++;
    }
    if(cur_x >= 80){
        cur_x = 0;
        cur_y++;
    }

    move_cursor();
}

void k_putchar(char c){
    k_write_cell(c, VGA_COLOR_WHITE, VGA_COLOR_BLACK);
}

void k_putserr(char* c){
    k_puts_color(c, VGA_COLOR_RED, VGA_COLOR_BLACK);
}

void k_puts_color(char* str, uint8_t fg_color, uint8_t bg_color){
    while (*str != '\0'){
        k_write_cell(*str++, fg_color, bg_color);
    }
    k_putchar('\n');
}

void k_puts(char* str){
    while(*str != '\0') k_putchar(*str++);
    k_putchar('\n');
}

void k_clear_screen(){
    uint8_t colorData = (VGA_COLOR_BLACK << 4) | (VGA_COLOR_WHITE & 0x0F);
    uint16_t blank = 0x20 | (colorData << 8); // 0x20 is 'Space' in ASCII
    for(uint16_t i = 0; i < 80*25; i++){
        fb[i] = blank;
    }

    cur_x = 0;
    cur_y = 0;
    move_cursor();
}

void move_cursor(){
    //Index = [(y * width) + x]
    uint16_t cursorLocation = cur_y * 80 + cur_x;

    outb(VGA_CURSOR_ATTRIB_PORT, VGA_CURSOR_HIGH_BYTE); // Tell the VGA that we will write attribute data on high 8 bytes
    outb(VGA_CURSOR_DATA_PORT, cursorLocation >> 8);    // Send the actual data
    outb(VGA_CURSOR_ATTRIB_PORT, VGA_CURSOR_LOW_BYTE);  // Likewise, we set to receive low 8 bytes
    outb(VGA_CURSOR_DATA_PORT, cursorLocation);

}