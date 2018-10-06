//
// Created by ratulrafsan on 9/23/18.
//

#include <stdint.h>
#include <vga.h>
#include <common.h>
#include <string.h>

uint16_t *fb = (uint16_t *) VGA_TUI_FRAME_BUFFER_START;
uint8_t cur_x = 0;
uint8_t cur_y = 0;

/**
 *  Internal function. Must not be called by external functions by any means
 */
void vga_move_cursor(){
    //Index = [(y * width) + x]
    uint16_t cursorLocation = cur_y * (uint8_t )80 + cur_x;

    outb(VGA_CURSOR_ATTRIB_PORT, VGA_CURSOR_HIGH_BYTE); // Tell the VGA that we will write attribute data on high 8 bytes
    outb(VGA_CURSOR_DATA_PORT, cursorLocation >> 8);    // Send the actual data
    outb(VGA_CURSOR_ATTRIB_PORT, VGA_CURSOR_LOW_BYTE);  // Likewise, we set to receive low 8 bytes
    outb(VGA_CURSOR_DATA_PORT, cursorLocation);
}

/**
 * Prints c with fg_color as foreground color & bg_color as background color
 *
 * @param c         : ASCII character to write
 * @param fg_color  : VGA foreground color code, check vga.h
 * @param bg_color  : VGA background color code, check vga.h
 */

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

/**
 * Enables or disables VGA text blinking
 * @param blink
 */
void vga_set_blink_mode(bool blink){
    //outb(0xe9, 'I');
    /* Read I/O address 0x03DA to reset index/data flip-flop
     * mov dx, 0x03DA
     * in al,dx
     * Write index 0x30 to 0x03C0 to set register index to 0x30s
     * mov dx, 0x03C0
     * mov al, 0x030
     * out dx, al
     * Read from 0x3C1 to get register contests
     * inc dx
     * in al, dx
     * Unset bit 3 to enable/disable blink
     * Enable: 0x08, Disable: 0xF7
     * and al, _____
     * dec dx
     * out dx, al
     */

    inb(VGA_ISR_PORT); //Read from 0x03DA to reset index/data flip-flop
    outb(VGA_ATTRIB_DATA_REG_PORT, 0x30); // Write 0x30 to 0x03C0 to set register index to 0x30
    uint8_t attrib_data = inb(VGA_ATTRIB_DATA_READ_PORT); //Read from 0x3C1 to get attrib register contents

    if(blink == true){
        attrib_data |= 0x08;
    }else{
        attrib_data |= 0xF7;
    }

    outb(VGA_ATTRIB_DATA_REG_PORT, attrib_data); //write new data back to attribute data register
}

/**
 * Clears the entier screen. Uses ASCII space character (0x20) with white black ground and white foreground color
 */
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

