//
// Created by ratulrafsan on 9/23/18.
//

#include <stdint.h>
#include <vga.h>
#include <common.h>

uint16_t *fb = (uint16_t *) VGA_TUI_FRAME_BUFFER_START;
uint8_t cur_x = 0;
uint8_t cur_y = 0;

void vga_write_cell(char c, uint8_t fg_color, uint8_t bg_color){
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
        uint8_t attribByte = (uint8_t) ((bg_color << 4) | (fg_color & 0x0F));
        uint16_t colorData = attribByte << 8;

        writePos = fb + (cur_y * 80 + cur_x);
        *writePos = c | colorData;
        cur_x++;
    }
    if(cur_x >= 80){
        cur_x = 0;
        cur_y++;
    }

    vga_move_cursor();
}

void vga_set_blink_mode(bool blink){
    (void)blink;
}

void vga_clear_screen(){
    uint8_t colorData = (VGA_COLOR_BLACK << 4) | (VGA_COLOR_WHITE & 0x0F);
    uint16_t blank = (uint8_t)0x20 | (colorData << 8); // 0x20 is 'Space' in ASCII
    for(uint16_t i = 0; i < 80*25; i++){
        fb[i] = blank;
    }

    cur_x = 0;
    cur_y = 0;
    vga_move_cursor();
}

void vga_move_cursor(){
    //Index = [(y * width) + x]
    uint16_t cursorLocation = cur_y * (uint8_t )80 + cur_x;

    outb(VGA_CURSOR_ATTRIB_PORT, VGA_CURSOR_HIGH_BYTE); // Tell the VGA that we will write attribute data on high 8 bytes
    outb(VGA_CURSOR_DATA_PORT, cursorLocation >> 8);    // Send the actual data
    outb(VGA_CURSOR_ATTRIB_PORT, VGA_CURSOR_LOW_BYTE);  // Likewise, we set to receive low 8 bytes
    outb(VGA_CURSOR_DATA_PORT, cursorLocation);
}