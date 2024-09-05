/*
 ============================================================================
 Name        : my_gpio.h
 Author      : Abd-Elrahman Adel
 Date        : 25/9/2023
 ============================================================================
 */
#ifndef MY_GPIO_H
#define MY_GPIO_H

#include "my_ATmega32_regs.h"
#include "my_std_types.h"

/***********************************************GPIO_ENUMS**************************************************/
typedef enum
{
	PIN_INPUT, PIN_OUTPUT
} GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT, PORT_OUTPUT = 0xFF
} GPIO_PortDirectionType;
/***********************************************************************************************************/

/***********************************************GPIO_STATES*************************************************/
#define LOGIC_LOW 0u
#define LOGIC_HIGH 1u
/***********************************************************************************************************/

/*******************************************GPIO_IDENTIFICATIONS********************************************/
#define PORTA_ID 0
#define PORTB_ID 1
#define PORTC_ID 2
#define PORTD_ID 3

#define PIN0_ID 0
#define PIN1_ID 1
#define PIN2_ID 2
#define PIN3_ID 3
#define PIN4_ID 4
#define PIN5_ID 5
#define PIN6_ID 6
#define PIN7_ID 7
/***********************************************************************************************************/

/********************************************GPIO_REGISTERS_SIZE********************************************/
#define GPIO_NUM_OF_PORTS 4
#define GPIO_NUM_OF_PINS 8
/***********************************************************************************************************/

/*************************************GPIO_REGISTERS_BEGINNING_ADDRESSES************************************/
#define PORTA_ADDRESS (0x3B)
#define DDRA_ADDRESS (0x3A)
#define PINA_ADDRESS (0x39)

#define GPIO_OFFSET (0x03)
/***********************************************************************************************************/

/*****************************************GPIO_FUNCTIONS_PROTOTYPES*****************************************/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);
void GPIO_writePort(uint8 port_num, uint8 value);
uint8 GPIO_readPort(uint8 port_num);
/***********************************************************************************************************/

/***********************************************GPIO_MACROS*************************************************/
/*MACROS_FOR_PINS*/
#define GPIO_PORT_SET_BIT(PORT_NUM, BIT_NUM) ((*(volatile GPIO_Reg_Type *const)(PORTA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte |= (1 << BIT_NUM))
#define GPIO_PORT_CLEAR_BIT(PORT_NUM, BIT_NUM) ((*(volatile GPIO_Reg_Type *const)(PORTA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte &= ~(1 << BIT_NUM))
#define GPIO_PORT_WRITE_PIN_VALUE(PORT_NUM, BIT_NUM, VALUE) ((VALUE == LOGIC_HIGH) ? GPIO_PORT_SET_BIT(PORT_NUM, BIT_NUM) : GPIO_PORT_CLEAR_BIT(PORT_NUM, BIT_NUM))

#define GPIO_DDR_SET_BIT(PORT_NUM, BIT_NUM) ((*(volatile GPIO_Reg_Type *const)(DDRA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte |= (1 << BIT_NUM))
#define GPIO_DDR_CLEAR_BIT(PORT_NUM, BIT_NUM) ((*(volatile GPIO_Reg_Type *const)(DDRA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte &= ~(1 << BIT_NUM))
#define GPIO_DDR_SETUP_PIN_DIRECTION(PORT_NUM, BIT_NUM, DIRECTION) ((DIRECTION == PIN_OUTPUT) ? GPIO_DDR_SET_BIT(PORT_NUM, BIT_NUM) : GPIO_DDR_CLEAR_BIT(PORT_NUM, BIT_NUM))

#define GPIO_PIN_READ_PIN_VALUE(PORT_NUM, BIT_NUM) (((*(volatile GPIO_Reg_Type const *const)(PINA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte) & (1 << BIT_NUM) ? LOGIC_HIGH : LOGIC_LOW)

/*MACROS_FOR_PORTS*/
#define GPIO_PORT_WRITE_PORT_VALUE(PORT_NUM, VALUE) ((*(volatile GPIO_Reg_Type *const)(PORTA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte = value)
#define GPIO_DDR_SETUP_PORT_DIRECTION(PORT_NUM, DIRECTION) ((*(volatile GPIO_Reg_Type *const)(DDRA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte = DIRECTION)
#define GPIO_PIN_READ_PORT_VALUE(PORT_NUM) ((*(volatile GPIO_Reg_Type const *const)(PINA_ADDRESS - GPIO_OFFSET * PORT_NUM)).Byte)
/***********************************************************************************************************/
#endif /*MY_GPIO_H*/
