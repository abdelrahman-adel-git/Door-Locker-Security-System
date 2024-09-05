/*
 ============================================================================
 Name        : Timer0.c
 Author      : Abd-Elrahman Adel
 Date        : 2/11/2023
 ============================================================================
 */
#include "my_ATmega32_regs.h"
#include "my_ATmega32_interrupts.h"
#include "my_common_macros.h"
#include "Timer0.h"

/*********************************************Globale_Variables**********************************************/

static volatile void (*g_Timer0_Call_Back_Ptr)(void) = NULL_PTR; /* Global variable to hold the address of the call back function in the application */
volatile uint8 g_Timer0_OVF_reset_value = 0; /*Global variable that will be used in the OVF mode to store the initial value and and continously write it in TCNT0 register within the ISR so the timer doesn't start counting from zero when the OVF occurs*/

/************************************************************************************************************/

/*******************************************Interrupt_Service_Routines***************************************/

ISR(TIMER0_OVF_vect)
{
	if (g_Timer0_Call_Back_Ptr != NULL_PTR)
	{
		(*g_Timer0_Call_Back_Ptr)(); /*Call the Call Back function in the application*/
		TCNT0.Byte = g_Timer0_OVF_reset_value; /*making the timer start counting from the specified initial value and not the zero*/
	}
}

ISR(TIMER0_COMP_vect)
{
	if (g_Timer0_Call_Back_Ptr != NULL_PTR)
		(*g_Timer0_Call_Back_Ptr)(); /*Call the Call Back function in the application*/
}

/************************************************************************************************************/

/*****************************************TIMER0_FUNCTIONS_DEFINITIONS**************************************/

void Timer0_init(const Timer0_ConfigType *Config_Ptr)
{
	TCNT0.Byte = Config_Ptr->initial_value; /*setting initial value*/

	/*setting the specified mode*/
	TCCR0.Bits.WGM00 = ((Config_Ptr->mode) & 0x01);
	TCCR0.Bits.WGM01 = ((Config_Ptr->mode) & 0x02);

	TCCR0.Byte = (TCCR0.Byte & 0xF8) | (Config_Ptr->prescaler); /*setting the prescaler*/

	switch (Config_Ptr->mode)
	{
	case TIMER0_NORMAL_MODE:
		TCCR0.Bits.FOC0 = 1;
		g_Timer0_OVF_reset_value = Config_Ptr->initial_value;
		TIMSK.Bits.TOIE0 = 1;
		break;
	case TIMER0_CTC_MODE:
		TCCR0.Bits.FOC0 = 1;
		OCR0.Byte = Config_Ptr->compare_value;
		TCCR0.Bits.COM01 = 1;
		TIMSK.Bits.OCIE0 = 1;
		break;
	case TIMER0_FAST_PWM_MODE: /*that is the mode used in the DC motor driver*/
		OCR0.Byte = (Config_Ptr->duty_cycle) * 2.55;
		TCCR0.Bits.COM01 = 1;
		break;
	}
}
void Timer0_deInit(void)
{
	/*Clearing all Timer1 registers*/
	TCNT0.Byte = 0;
	TCCR0.Byte = 0; /*here we cleared the bits CS02:0 so there is no clock source and the timer is stopped now*/

	/*Disable both compare match and overflow interrupts*/
	TIMSK.Bits.OCIE0 = 0;
	TIMSK.Bits.TOIE0 = 0;

	g_Timer0_Call_Back_Ptr = NULL_PTR; /*Reset the global pointer value*/
}

void Timer0_setCallBack(void (*a_ptr)(void))
{
	g_Timer0_Call_Back_Ptr = a_ptr; /*Saving the address of the Call back function in a global variable*/
}

/***********************************************************************************************************/
