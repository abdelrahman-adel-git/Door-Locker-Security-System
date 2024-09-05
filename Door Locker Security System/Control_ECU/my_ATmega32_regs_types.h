/*
 ============================================================================
 Name        : my_ATmega32_regs_types.h
 Author      : Abd-Elrahman Adel
 Date        : 25/9/2023
 ============================================================================
 */

#ifndef MY_ATMEGA32_REGS_TYPES_H
#define MY_ATMEGA32_REGS_TYPES_H

#include "my_std_types.h"

/*******************************GPIO Registers type structure declarations**********************************/

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} Bits;
} GPIO_Reg_Type;

/***********************************************************************************************************/

/*******************************Timers Registers type structure declarations********************************/

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 C :1;
		uint8 Z :1;
		uint8 N :1;
		uint8 V :1;
		uint8 S :1;
		uint8 H :1;
		uint8 T :1;
		uint8 I :1;
	} Bits;

} SREG_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TOIE0 :1;
		uint8 OCIE0 :1;
		uint8 TOIE1 :1;
		uint8 OCIE1B :1;
		uint8 OCIE1A :1;
		uint8 TICIE1 :1;
		uint8 TOIE2 :1;
		uint8 OCIE2 :1;
	} Bits;

} Timers_TIMSK_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TOV0 :1;
		uint8 OCF0 :1;
		uint8 TOV1 :1;
		uint8 OCF1B :1;
		uint8 OCF1A :1;
		uint8 ICF1 :1;
		uint8 TOV2 :1;
		uint8 OCF2 :1;
	} Bits;

} Timers_TIFR_Type;

/***********************************************************************************************************/

/******************************Watchdog Timer Registers type structure declarations*************************/
typedef union
{
	uint8 Byte;
	struct
	{
		uint8 WDP0 :1;
		uint8 WDP1 :1;
		uint8 WDP2 :1;
		uint8 WDE :1;
		uint8 WDTOE :1;
		uint8 :1;
		uint8 :1;
		uint8 :1;
	} Bits;

} Watchdog_WDTCR_Type;

/***********************************************************************************************************/

/*******************************Timer0 Registers type structure declarations********************************/

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 CS00 :1;
		uint8 CS01 :1;
		uint8 CS02 :1;
		uint8 WGM01 :1;
		uint8 COM00 :1;
		uint8 COM01 :1;
		uint8 WGM00 :1;
		uint8 FOC0 :1;
	} Bits;

} Timer0_TCCR0_Type;

typedef union
{
	uint8 Byte;
} Timer0_OCR0_Type;

typedef union
{
	uint8 Byte;
} Timer0_TCNT0_Type;

/***********************************************************************************************************/

/*******************************Timer1 Registers type structure declarations********************************/
typedef union
{
	uint8 Byte;
	struct
	{
		uint8 WGM10 :1;
		uint8 WGM11 :1;
		uint8 FOC1B :1;
		uint8 FOC1A :1;
		uint8 COM1B0 :1;
		uint8 COM1B1 :1;
		uint8 COM1A0 :1;
		uint8 COM1A1 :1;
	} Bits;

} Timer1_TCCR1A_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 CS10 :1;
		uint8 CS11 :1;
		uint8 CS12 :1;
		uint8 WGM12 :1;
		uint8 WGM13 :1;
		uint8 :1;
		uint8 ICES1 :1;
		uint8 ICNC1 :1;
	} Bits;

} Timer1_TCCR1B_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0 :1;
		uint16 Bit1 :1;
		uint16 Bit2 :1;
		uint16 Bit3 :1;
		uint16 Bit4 :1;
		uint16 Bit5 :1;
		uint16 Bit6 :1;
		uint16 Bit7 :1;
		uint16 Bit8 :1;
		uint16 Bit9 :1;
		uint16 Bit10 :1;
		uint16 Bit11 :1;
		uint16 Bit12 :1;
		uint16 Bit13 :1;
		uint16 Bit14 :1;
		uint16 Bit15 :1;
	} Bits;

} Timer1_TCNT1_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0 :1;
		uint16 Bit1 :1;
		uint16 Bit2 :1;
		uint16 Bit3 :1;
		uint16 Bit4 :1;
		uint16 Bit5 :1;
		uint16 Bit6 :1;
		uint16 Bit7 :1;
		uint16 Bit8 :1;
		uint16 Bit9 :1;
		uint16 Bit10 :1;
		uint16 Bit11 :1;
		uint16 Bit12 :1;
		uint16 Bit13 :1;
		uint16 Bit14 :1;
		uint16 Bit15 :1;
	} Bits;

} Timer1_OCR1A_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0 :1;
		uint16 Bit1 :1;
		uint16 Bit2 :1;
		uint16 Bit3 :1;
		uint16 Bit4 :1;
		uint16 Bit5 :1;
		uint16 Bit6 :1;
		uint16 Bit7 :1;
		uint16 Bit8 :1;
		uint16 Bit9 :1;
		uint16 Bit10 :1;
		uint16 Bit11 :1;
		uint16 Bit12 :1;
		uint16 Bit13 :1;
		uint16 Bit14 :1;
		uint16 Bit15 :1;
	} Bits;
} Timer1_OCR1B_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 Bit0 :1;
		uint16 Bit1 :1;
		uint16 Bit2 :1;
		uint16 Bit3 :1;
		uint16 Bit4 :1;
		uint16 Bit5 :1;
		uint16 Bit6 :1;
		uint16 Bit7 :1;
		uint16 Bit8 :1;
		uint16 Bit9 :1;
		uint16 Bit10 :1;
		uint16 Bit11 :1;
		uint16 Bit12 :1;
		uint16 Bit13 :1;
		uint16 Bit14 :1;
		uint16 Bit15 :1;
	} Bits;

} Timer1_ICR1_Type;

/***********************************************************************************************************/

/**********************************ADC Registers type structure declarations********************************/

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 MUX0 :1;
		uint8 MUX1 :1;
		uint8 MUX2 :1;
		uint8 MUX3 :1;
		uint8 MUX4 :1;
		uint8 ADLAR :1;
		uint8 REFS0 :1;
		uint8 REFS1 :1;
	} Bits;

} ADC_ADMUX_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 ADPS0 :1;
		uint8 ADPS1 :1;
		uint8 ADPS2 :1;
		uint8 ADIE :1;
		uint8 ADIF :1;
		uint8 ADATE :1;
		uint8 ADSC :1;
		uint8 ADEN :1;
	} Bits;

} ADC_ADCSRA_Type;

typedef union
{
	uint16 TwoBytes;
	struct
	{
		uint16 ADC0 :1;
		uint16 ADC1 :1;
		uint16 ADC2 :1;
		uint16 ADC3 :1;
		uint16 ADC4 :1;
		uint16 ADC5 :1;
		uint16 ADC6 :1;
		uint16 ADC7 :1;
		uint16 ADC8 :1;
		uint16 ADC9 :1;
		uint16 :1;
		uint16 :1;
		uint16 :1;
		uint16 :1;
		uint16 :1;
		uint16 :1;
	} Bits;

} ADC_ADC_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 PSR10 :1;
		uint8 PSR2 :1;
		uint8 PUD :1;
		uint8 ACME :1;
		uint8 :1;
		uint8 ADTS0 :1;
		uint8 ADTS1 :1;
		uint8 ADTS2 :1;
	} Bits;

} ADC_SFIOR_TYPE;

/***********************************************************************************************************/

/**********************************UART Registers type structure declarations********************************/

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} Bits;

} UART_UDR_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 MPCM :1;
		uint8 U2X :1;
		uint8 PE :1;
		uint8 DOR :1;
		uint8 FE :1;
		uint8 UDRE :1;
		uint8 TXC :1;
		uint8 RXC :1;
	} Bits;

} UART_UCSRA_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TXB8 :1;
		uint8 RXB8 :1;
		uint8 UCSZ2 :1;
		uint8 TXEN :1;
		uint8 RXEN :1;
		uint8 UDRIE :1;
		uint8 TXCIE :1;
		uint8 RXCIE :1;
	} Bits;

} UART_UCSRB_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 UCPOL :1;
		uint8 UCSZ0 :1;
		uint8 UCSZ1 :1;
		uint8 USBS :1;
		uint8 UPM0 :1;
		uint8 UPM1 :1;
		uint8 UMSEL :1;
		uint8 URSEL :1;
	} Bits;

} UART_UCSRC_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 Bit8 :1;
		uint8 Bit9 :1;
		uint8 Bit10 :1;
		uint8 Bit11 :1;
		uint8 :1;
		uint8 :1;
		uint8 :1;
		uint8 URSEL :1;
	} Bits;

} UART_UBRRH_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 Bit0 :1;
		uint8 Bit1 :1;
		uint8 Bit2 :1;
		uint8 Bit3 :1;
		uint8 Bit4 :1;
		uint8 Bit5 :1;
		uint8 Bit6 :1;
		uint8 Bit7 :1;
	} Bits;

} UART_UBRRL_Type;

/***********************************************************************************************************/

/**********************************TWI(I2C) Registers type structure declarations********************************/

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TWBR0 :1;
		uint8 TWBR1 :1;
		uint8 TWBR2 :1;
		uint8 TWBR3 :1;
		uint8 TWBR4 :1;
		uint8 TWBR5 :1;
		uint8 TWBR6 :1;
		uint8 TWBR7 :1;
	} Bits;

} TWI_TWBR_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TWIE :1;
		uint8 :1;
		uint8 TWEN :1;
		uint8 TWWC :1;
		uint8 TWSTO :1;
		uint8 TWSTA :1;
		uint8 TWEA :1;
		uint8 TWINT :1;
	} Bits;

} TWI_TWCR_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TWPS0 :1;
		uint8 TWPS1 :1;
		uint8 :1;
		uint8 TWS3 :1;
		uint8 TWS4 :1;
		uint8 TWS5 :1;
		uint8 TWS6 :1;
		uint8 TWS7 :1;
	} Bits;

} TWI_TWSR_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TWD0 :1;
		uint8 TWD1 :1;
		uint8 TWD2 :1;
		uint8 TWD3 :1;
		uint8 TWD4 :1;
		uint8 TWD5 :1;
		uint8 TWD6 :1;
		uint8 TWD7 :1;
	} Bits;

} TWI_TWDR_Type;

typedef union
{
	uint8 Byte;
	struct
	{
		uint8 TWGCE :1;
		uint8 TWA0 :1;
		uint8 TWA1 :1;
		uint8 TWA2 :1;
		uint8 TWA3 :1;
		uint8 TWA4 :1;
		uint8 TWA5 :1;
		uint8 TWA6 :1;
	} Bits;

} TWI_TWAR_Type;

/***********************************************************************************************************/
#endif /*MY_ATMEGA32_REGS_TYPES_H*/
