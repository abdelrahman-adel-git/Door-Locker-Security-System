/*
 ============================================================================
 Name        : Timer1.c
 Author      : Abd-Elrahman Adel
 Date        : 1/11/2023
 ============================================================================
 */
#include "my_common_macros.h"
#include "my_ATmega32_interrupts.h"
#include "my_ATmega32_regs.h"
#include "Timer1.h"

/*********************************************Globale_Variables**********************************************/

static volatile void (*g_Timer1_Call_Back_Ptr)(void) = NULL_PTR; /* Global variable to hold the address of the call back function in the application */
volatile uint16 g_Timer1_OVF_reset_value = 0; /*Global variable that will be used in the OVF mode to store the initial value and and continously write it in TCNT1 register within the ISR so the timer doesn't start counting from zero when the OVF occurs*/

/***********************************************************************************************************/

/*******************************************Interrupt_Service_Routines***************************************/

ISR(TIMER1_OVF_vect)
{
	if (g_Timer1_Call_Back_Ptr != NULL_PTR)
	{
		(*g_Timer1_Call_Back_Ptr)(); /*Call the Call Back function in the application*/
		TCNT1.TwoBytes = g_Timer1_OVF_reset_value; /*making the timer start counting from the specified initial value and not the zero*/
	}
}

ISR(TIMER1_COMPA_vect)
{
	if (g_Timer1_Call_Back_Ptr != NULL_PTR)
		(*g_Timer1_Call_Back_Ptr)(); /*Call the Call Back function in the application*/
}

/***********************************************************************************************************/

/*****************************************TIMER1_FUNCTIONS_DEFINITIONS**************************************/

void Timer1_init(const Timer1_ConfigType *Config_Ptr)
{
	TCNT1.TwoBytes = Config_Ptr->initial_value; /*setting initial value*/

	if (Config_Ptr->mode == TIMER1_CTC_MODE)
		OCR1A.TwoBytes = Config_Ptr->compare_value; /*setting compare value in case of compare mode*/
	else
		g_Timer1_OVF_reset_value = Config_Ptr->initial_value; /*In case of OVF mode, store the initial value in a global variable to update the TCNT1 register with it in the ISR*/

	TCCR1A.Bits.FOC1A = 1; /*FOC1A bit is set to one in both modes*/

	TCCR1A.Byte = (TCCR1A.Byte & 0xFC) | ((Config_Ptr->mode) & 0x03); /*inserting the first two bits of the mode in bits WGM11 & WGM10*/
	TCCR1B.Byte = (TCCR1B.Byte & 0xE7) | (((Config_Ptr->mode) & 0x0C) << 1); /*inserting the seconds two bits of the mode in bits WGM13 & WGM12*/

	TCCR1B.Byte = (TCCR1B.Byte & 0xF8) | (Config_Ptr->prescaler); /*setting the prescaler*/

	(Config_Ptr->mode == TIMER1_CTC_MODE) ? (TIMSK.Bits.OCIE1A = 1) : (TIMSK.Bits.TOIE1 = 1); /*Enable compare match interrupt or overflow interrupt according to the chosen mode*/
}

void Timer1_deInit(void)
{
	/*Clearing all Timer1 registers*/
	TCCR1A.Byte = 0;
	TCCR1B.Byte = 0; /*here we cleared the bits CS12:0 so there is no clock source and the timer is stopped now*/
	TCNT1.TwoBytes = 0;

	/*Disable both compare match and overflow interrupts*/
	TIMSK.Bits.OCIE1A = 0;
	TIMSK.Bits.TOIE1 = 0;

	g_Timer1_Call_Back_Ptr = NULL_PTR; /*Reset the global pointer value*/
}

void Timer1_setCallBack(void (*a_ptr)(void))
{
	g_Timer1_Call_Back_Ptr = a_ptr; /*Saving the address of the Call back function in a global variable*/
}

/***********************************************************************************************************/
