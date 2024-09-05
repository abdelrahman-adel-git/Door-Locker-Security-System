/*
 ============================================================================
 Name        : my_ATmega32_regs.h
 Author      : Abd-Elrahman Adel
 Date        : 25/9/2023
 ============================================================================
 */

#ifndef MY_ATMEGA32_REGS_H
#define MY_ATMEGA32_REGS_H

#include "my_ATmega32_regs_types.h"

/****************************************GPIO_REGISTERS_DEFINITIONS****************************************/

#define PORTA (*(volatile GPIO_Reg_Type *const)0x3B)
#define DDRA (*(volatile GPIO_Reg_Type *const)0x3A)
#define PINA (*(volatile GPIO_Reg_Type const *const)0x39)

#define PORTB (*(volatile GPIO_Reg_Type *const)0x38)
#define DDRB (*(volatile GPIO_Reg_Type *const)0x37)
#define PINB (*(volatile GPIO_Reg_Type const *const)0x36)

#define PORTC (*(volatile GPIO_Reg_Type *const)0x35)
#define DDRC (*(volatile GPIO_Reg_Type *const)0x34)
#define PINC (*(volatile GPIO_Reg_Type const *const)0x33)

#define PORTD (*(volatile GPIO_Reg_Type *const)0x32)
#define DDRD (*(volatile GPIO_Reg_Type *const)0x31)
#define PIND (*(volatile GPIO_Reg_Type const *const)0x30)

/***********************************************************************************************************/

/****************************************TIMERS_REGISTERS_DEFINITIONS***************************************/

#define SREG (*(volatile SREG_Type *const)0x5F)
#define TIMSK (*(volatile Timers_TIMSK_Type *const)0x59)
#define TIFR (*(volatile Timers_TIFR_Type *const)0x58)
/***********************************************************************************************************/

/****************************************WATCHDOG_REGISTERS_DEFINITIONS***************************************/
#define WDTCR (*(volatile Watchdog_WDTCR_Type *const)0x41)
/***********************************************************************************************************/

/****************************************TIMER0_REGISTERS_DEFINITIONS***************************************/

#define OCR0 (*(volatile Timer0_OCR0_Type *const)0x5C)
#define TCCR0 (*(volatile Timer0_TCCR0_Type *const)0x53)
#define TCNT0 (*(volatile Timer0_TCNT0_Type *const)0x52)

/***********************************************************************************************************/

/****************************************TIMER1_REGISTERS_DEFINITIONS***************************************/

#define TCCR1A (*(volatile Timer1_TCCR1A_Type *const)0x4F)
#define TCCR1B (*(volatile Timer1_TCCR1B_Type *const)0x4E)
#define TCNT1 (*(volatile Timer1_TCNT1_Type *const)0x4C)
#define OCR1A (*(volatile Timer1_OCR1A_Type *const)0x4A)
#define OCR1B (*(volatile Timer1_OCR1B_Type *const)0x48)
#define ICR1 (*(volatile Timer1_ICR1_Type *const)0x46)

/***********************************************************************************************************/

/*******************************************ADC_REGISTERS_DEFINITIONS***************************************/

#define ADMUX (*(volatile ADC_ADMUX_Type *const)0x27)
#define ADCSRA (*(volatile ADC_ADCSRA_Type *const)0x26)
#define ADC (*(volatile ADC_ADC_Type *const)0x24)
#define SFIOR (*(volatile ADC_SFIOR_TYPE *const)0x50)

/***********************************************************************************************************/

/*******************************************UART_REGISTERS_DEFINITIONS***************************************/

#define UDR (*(volatile UART_UDR_Type *const)0x2C)
#define UCSRA (*(volatile UART_UCSRA_Type *const)0x2B)
#define UCSRB (*(volatile UART_UCSRB_Type *const)0x2A)
#define UCSRC (*(volatile UART_UCSRC_Type *const)0x40)
#define UBRRH (*(volatile UART_UBRRH_Type *const)0x40)
#define UBRRL (*(volatile UART_UBRRL_Type *const)0x29)

/***********************************************************************************************************/

/*******************************************TWI(I2C)_REGISTERS_DEFINITIONS***************************************/

#define TWBR (*(volatile TWI_TWBR_Type *const)0x20)
#define TWCR (*(volatile TWI_TWCR_Type *const)0x56)
#define TWSR (*(volatile TWI_TWSR_Type *const)0x21)
#define TWDR (*(volatile TWI_TWDR_Type *const)0x23)
#define TWAR (*(volatile TWI_TWAR_Type *const)0x22)

/***********************************************************************************************************/

#endif /*MY_ATMEGA32_REGS_H*/
