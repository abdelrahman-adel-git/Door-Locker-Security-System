/*
 * File: Keypad7Seg.c
 * Created on: Sep 25, 2023
 * Author: Abd-Elrahman Adel
 */

#include "my_keypad.h"
#include "my_gpio.h"
#ifndef STANDARD_KEYPAD
#include <util/delay.h>
#endif

#ifndef STANDARD_KEYPAD
#if (KEYPAD_NUM_OF_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_OF_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif
#endif

uint8 KEYPAD_getPressedKey(void)
{
	uint8 row, col;

	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID + 1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID + 2, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID + 3, PIN_INPUT);

	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_FIRST_PIN_ID, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_FIRST_PIN_ID + 1, PIN_INPUT);
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_FIRST_PIN_ID + 2, PIN_INPUT);
#if (KEYPAD_NUM_OF_COLS == 4)
	GPIO_setupPinDirection(KEYPAD_COL_PORT_ID, KEYPAD_COL_FIRST_PIN_ID + 3, PIN_INPUT);
#endif

	while (1)
	{
		for (row = 0; row < KEYPAD_NUM_OF_ROWS; row++)
		{
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID + row, PIN_OUTPUT);
			GPIO_writePin(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID + row, KEYPAD_BUTTON_PRESSED);

			for (col = 0; col < KEYPAD_NUM_OF_COLS; col++)
			{
				if (GPIO_readPin(KEYPAD_COL_PORT_ID, KEYPAD_COL_FIRST_PIN_ID + col) == KEYPAD_BUTTON_PRESSED)
				{
#if (KEYPAD_NUM_OF_COLS == 3)
#ifdef STANDARD_KEYPAD
                    return ((row * KEYPAD_NUM_OF_COLS) + col + 1);
#else
                    return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_OF_COLS) + col + 1);
#endif
#elif (KEYPAD_NUM_OF_COLS == 4)
#ifdef STANDARD_KEYPAD
					return ((row * KEYPAD_NUM_OF_COLS) + col + 1);
#else
#ifdef ETA32_MINI
                    return KEYPAD_4x4_adjustKeyNumber_ETA32MINI((row * KEYPAD_NUM_OF_COLS) + col + 1)
#else
					return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_OF_COLS) + col + 1);
#endif
#endif
#endif
				}
			}
			GPIO_setupPinDirection(KEYPAD_ROW_PORT_ID, KEYPAD_ROW_FIRST_PIN_ID + row, PIN_INPUT);
#ifndef STANDARD_KEYPAD /*no need worry about the CPU load if I'm working on the Eta32mini*/
			_delay_ms(10);
#endif
		}
	}
}
#ifndef STANDARD_KEYPAD
#if (KEYPAD_NUM_OF_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
    switch (button_number)
    {
        /*from 1 to 9 is included in the default case*/
    default:
        return button_number;
        break;
    case 10:
        return '*';
        break;
    case 11:
        return 0;
        break;
    case 12:
        return '#';
        break;
    }
}
#elif (KEYPAD_NUM_OF_COLS == 4)

static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	switch (button_number)
	{
	case 1:
		return 7;
		break;
	case 2:
		return 8;
		break;
	case 3:
		return 9;
		break;
	case 4:
		return '/';
		break;
	case 5:
		return 4;
		break;
	case 6:
		return 5;
		break;
	case 7:
		return 6;
		break;
	case 8:
		return '*';
		break;
	case 9:
		return 1;
		break;
	case 10:
		return 2;
		break;
	case 11:
		return 3;
		break;
	case 12:
		return '-';
		break;
	case 13:
		return 13;
		break;
	case 14:
		return 0;
		break;
	case 15:
		return '=';
		break;
	case 16:
		return '+';
		break;
	default:
		return button_number;
		break;
	}
}
#endif
#endif
