//
// Created by ratulrafsan on 10/2/18.
//

/**
 * Implements most common serial communication methods.
 * Primarily intended to be used with bochs for debug outputs.
 *
 * See serial.h for com port & register port definitions
 * See https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming for more details
 */

#include <serial.h>
#include <common.h>
#include <stdarg.h>
#include <string.h>

/**
 * Sets the baud rate of a @param com_port to @param divisor.
 * @param com_port : Address of com port.
 * @param divisor  : 16 bit clock divisor which is used to control baud rate.
 */
void serial_set_baud_rate(uint16_t com_port, uint16_t divisor){
    //uint8_t divisor_high_byte = (divisor >> 8) & 0x00ff;
    //uint8_t divisor_low_byte = divisor & 0x00ff;

    //Disable interrupts
    outb(SERIAL_INT_ENABLE_REGISTER(com_port), 0x00);
    //Enable DLAB
    outb(SERIAL_LINE_CONTROL_REGISTER(com_port), SERIAL_SET_DLAB_BIT);
    //Send divisor high byte
    outb(SERIAL_DATA_REGISTER_PORT(com_port), divisor & 0x00ff);
    //Send divisor low byte
    outb(SERIAL_INT_ENABLE_REGISTER(com_port), (divisor >> 8) & 0x00ff);
    //Disable DLAB
    outb(SERIAL_LINE_CONTROL_REGISTER(com_port), 0x00);

}

/**
 * Sets the line control register of @param com_port according to @param line_control_data.
 * The layout of the line control register is as follows:
 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b |parity | s | dl  |
 *  d       = DLAB bit
 *  b       = break control
 *  parity  = number of parity bit
 *  s       = number of stop bits to use. Set to 0 for 1, set to 1 for 1.5 or 2
 *  dl      = Describes the length of data. 00 = 5 bits, 01 = 6 bits, 10 = 7 bits, 11 = 8 bits.
 *
 * @param com_port          : Com port address.
 * @param line_control_data : Data that will be written into line control register. Most commonly used: 0x03
 */
void serial_configure_line(uint16_t com_port, uint8_t line_control_data){
    outb(SERIAL_LINE_CONTROL_REGISTER(com_port), line_control_data);
}

/**
 * Sets the FIFO control register of @param com_port according to @param fifo_control_data
 * The layout of this register is as follows:
 * Bit:     | 7 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * Content: | trg |e64| r |DMA|clt|clr| e|
 * trg = Trigger thresh-hold. See https://en.wikibooks.org/wiki/Serial_Programming/8250_UART_Programming#FIFO_Control_Register
 * e64 = Enable 64 byte FIFO
 * r   = Reserved
 * DMA = How the serial port data should be accessed
 * clt = Clear transmit FIFO buffer
 * clr = Clear recieve FIFO buffer
 * e   = Enable/Disable FIFO buffer
 *
 * @param com_port          : Com port address.
 * @param fifo_control_data : Data that will be written to FIFO control register.
 */
void serial_configure_fifo(uint16_t com_port, uint8_t fifo_control_data){
    outb(SERIAL_INT_FIFO_CONTROL_REGISTER(com_port), fifo_control_data);
}


/**
 * Sets modem control register of @param com_port according to @param modem_control_data
 * The layout of this register is as follows:
 * Bits:     | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 * Contents: | r | r |afc|lb |ao2|ao1|rts|dtr|
 * r    = reserved
 * afc  = Autoflow control enable
 * lb   = Loopback mode
 * a02  = Auxiliary output 2
 * a01  = Auxiliary output 1
 * rts  = Ready to transmit
 * dtr  = Data terminal ready
 *
 * @param com_port            : Com port address.
 * @param modem_control_data  : Data that will be written to Modem control register
 */
void serial_configure_modem(uint16_t com_port, uint8_t modem_control_data){
    outb(SERIAL_MODEM_CONTROL_REGISTER(com_port), modem_control_data);
}

/**
 * Prints a single character @param c to @param com_port
 * @param com_port : Com port address.
 * @param c        : Character to write.
 */
void serial_putchar(uint16_t com_port, char c){
    // Wait until UART is ready to recieve next byte
    while( (inb(SERIAL_LINE_STATUS_REGISTER(com_port)) & (1 << 5)) == 0); // NOTICE THE SEMICOLON
    // Write the character to Data register
    outb(com_port, (uint8_t )c);
}
/**
 * Prints a string pointed by @param buff to @param com_port. Adds a '\n' at the end
 * @param com_port  : Com port address
 * @param buff      : Pointer to buffer to read from
 */
void serial_puts(uint16_t com_port, char* buff){
    while(*buff != '\0'){
        serial_putchar(com_port, *buff++);
    }
    outb(com_port, (uint8_t )'\n');
}

/**
 * Configures @param com_port with some default configs for quick setup
 * SERIAL_LINE_CONTROL_REGISTER is set to 0x03 : Break control disabled, no parity, 1 stop bit, 8 bit data length
 * SERIAL_INT_FIFO_CONTROL_REGISTER is set to 0xC7 : Enable FIFO, Clear TX & RX FIFO queue, use 14 bytes as size of queue
 *
 * @param com_port  : Com port address
 * @param divisor   : 16 bit clock divisor for baud rate.
 */
void serial_default_config(uint16_t com_port, uint16_t divisor){
    serial_set_baud_rate(com_port, divisor);
    serial_configure_line(com_port, 0x03);
    serial_configure_fifo(com_port, 0xC7);
    //TODO: configure modem and enable interrupts
}

/**
 * Helper function for serial_printf. Prototye is NOT declared in serial.h
 * @param com_port : Com port address
 * @param buffer   : Pointer to buffer to read from.
 */
void serial_print(uint16_t com_port, char* buffer){
    for(int i = 0; buffer[i]; i++){
        serial_putchar(com_port, buffer[i]);
    }
}

/**
 * Minimal implementation of printf for serial outputs
 * Currently supported formatters:
 * d,i : int/decimal numbers
 * b,B : binary numbers
 * x,X : hexadecimal numbers
 * s   : strings
 *
 * @param com_port : Serial port to write to
 * @param fmt      : Formatted string
 * @param ...      : Parameters to place in the formatter
 */

void serial_printf(uint16_t com_port, char* fmt, ...){
    //TODO: add support for string width formatting
    va_list ap;
    char buffer[11];
    //TODO: add support for doubles?

    va_start(ap, fmt);
    for(char* p = fmt; *p; p++){
        if(*p != '%'){
            serial_putchar(com_port, *p);
            continue;
        }
        switch (*++p){
            case 'd':
            case 'i':
                itoa(buffer, va_arg(ap, int), 10);
                serial_print(com_port, buffer);
                break;
            case 'x':
            case 'X':
                itoa(buffer, va_arg(ap, int), 16);
                serial_print(com_port, buffer);
                break;
            case 'b':
            case 'B':
                itoa(buffer, va_arg(ap, int), 2);
                serial_print(com_port, buffer);
                break;
            case 's':
                serial_print(com_port, va_arg(ap, char*));
                break;
            default:
                serial_putchar(com_port, *p);
                break;
        }
    }
    va_end(ap);

}

