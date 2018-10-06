//
// Created by ratulrafsan on 10/2/18.
//

#ifndef SNACKBAR_SERIAL_H
#define SNACKBAR_SERIAL_H

#include <stdint.h>

#define SERIAL_COM1_BASE    0x3F8
#define SERIAL_COM2_BASE    0x2F8
#define SERIAL_COM3_BASE    0x3E8
#define SERIAL_COM4_BASE    0x2E8

/*
 * All I/O ports are calculated relative to data ports
 */

/**
 * SERIAL_DATA_REGISTER_PORT
 * Data register. Reading this register performs read operation on the Receive buffer.
 * Writing to this register performs write operation to the Transmit buffer.
 * When DLAB is set to 1, this acts as the least significant byte of 16 bit divisor
 */
#define SERIAL_DATA_REGISTER_PORT(base)  (base)

/**
 * SERIAL_INT_ENABLE_REGISTER
 * When DLAB is set to 0, this acts as the interrupt enable register
 * When DLAB is set to 1, this acts as the most significant byte of 16 bit divisior
 */
#define SERIAL_INT_ENABLE_REGISTER(base) (base + 1)
#define SERIAL_INT_FIFO_CONTROL_REGISTER(base) (base + 2)
#define SERIAL_LINE_CONTROL_REGISTER(base) (base + 3)
#define SERIAL_MODEM_CONTROL_REGISTER(base) (base + 4)
#define SERIAL_LINE_STATUS_REGISTER(base) (base + 5)
#define SERIAL_MODEM_STATUS_REGISTER(base) (base + 6)
#define SERIAL_SCRATCH_REGISTER(base) (base + 7)

/**
 * SERIAL_SET_DLAB_BIT
 * The most significant bit of SERIAL_LINE_CONTROL_REGISTER needs to be set to 1
 * to enable DLAB. The value 0x80 is 0b10000000, so, setting this value to
 * SERIAL_LINE_CONTROL_REGISTER will effectively enable DLAB
 */
#define SERIAL_SET_DLAB_BIT 0x80

void serial_set_baud_rate(uint16_t com_port, uint16_t divisor);
void serial_configure_line(uint16_t com_port, uint8_t line_control_data);
void serial_configure_fifo(uint16_t com_port, uint8_t fifo_control_data);
void serial_configure_modem(uint16_t com_port, uint8_t modem_control_data);
void serial_putchar(uint16_t com_port, char c);
void serial_puts(uint16_t com_port, char* buff);
void serial_printf(uint16_t com_port, char* fmt, ...);
void serial_default_config(uint16_t com_port, uint16_t divisor);


#endif //SNACKBAR_SERIAL_H
