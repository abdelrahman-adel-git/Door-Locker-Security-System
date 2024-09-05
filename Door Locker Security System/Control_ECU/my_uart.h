/*
 ============================================================================
 Name        : my_uart.h
 Author      : Abd-Elrahman Adel
 Date        : 30/10/2023
 ============================================================================
 */

#ifndef MY_UART_H_
#define MY_UART_H_

#include "my_std_types.h"

typedef enum
{
	UART_5_BITS, UART_6_BITS, UART_7_BITS, UART_8_BITS, UART_9_BITS = 7
} UART_BitData;

typedef enum
{
	DISABLED_PARITY, RESERVED_PARITY, EVEN_PARITY, ODD_PARITY

} UART_Parity;

typedef enum
{
	STOP_BIT_1, STOP_BIT_2

} UART_StopBit;

typedef enum
{
	bps_2400 = 2400, bps_4800 = 4800, bps_9600 = 9600

} UART_BaudRate;

typedef struct
{
	UART_BitData bit_data;
	UART_Parity parity;
	UART_StopBit stop_bit;
	UART_BaudRate baud_rate;
} UART_ConfigType;

void UART_init(const UART_ConfigType *Config_Ptr);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte(void);

void UART_sendString(const uint8 *Str);

void UART_receiveString(uint8 *Str);

#endif /* MY_UART_H_ */
