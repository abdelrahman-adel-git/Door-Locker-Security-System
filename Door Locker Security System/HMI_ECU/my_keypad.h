/*
 * File: Keypad7Seg.c
 * Created on: Sep 25, 2023
 * Author: Abd-Elrahman Adel
 */

#ifndef MY_KEYPAD_H
#define MY_KEYPAD_H

#include "my_std_types.h"
/*#define STANDARD_KEYPAD*/
/*****************************************KEYPAD_NUM_OF_ROWS & COLUMNS**************************************/
#define KEYPAD_NUM_OF_ROWS 4
#define KEYPAD_NUM_OF_COLS 4
/***********************************************************************************************************/

/******************************************KEYPAD_PORT_CONFIGURATIONS***************************************/
#define KEYPAD_ROW_PORT_ID PORTB_ID
#define KEYPAD_ROW_FIRST_PIN_ID PIN4_ID

#define KEYPAD_COL_PORT_ID PORTD_ID
#define KEYPAD_COL_FIRST_PIN_ID PIN2_ID
/***********************************************************************************************************/

/********************************************KEYPAD_BUTTON_STATE********************************************/
#define KEYPAD_BUTTON_PRESSED LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED LOGIC_HIGH
/***********************************************************************************************************/

/***************************************KEYPAD_FUNCTIONS_PROTOTYPES*****************************************/
uint8 KEYPAD_getPressedKey(void);
/***********************************************************************************************************/
#endif /*MY_KEYPAD_H*/
