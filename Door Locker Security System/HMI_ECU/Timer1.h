/*
 ============================================================================
 Name        : Timer1.h
 Author      : Abd-Elrahman Adel
 Date        : 1/11/2023
 ============================================================================
 */

#ifndef TIMER1_H_
#define TIMER1_H_

#include "my_std_types.h"

/************************************************TIMER1_ENUMS***********************************************/

typedef enum
{
	TIMER1_NORMAL_MODE, TIMER1_CTC_MODE = 4
} Timer1_Mode;

typedef enum
{
	TIMER1_NO_CLOCK, TIMER1_FCPU_1, TIMER1_FCPU_8, TIMER1_FCPU_64, TIMER1_FCPU_256, TIMER1_FCPU_1024, TIMER1_EXTERNAL_CLOCK_FALLING_EDGE, TIMER1_EXTERNAL_CLOCK_RISING_EDGE
} Timer1_Prescaler;

/***********************************************************************************************************/

/*********************************************TIMER1_STRUCTS************************************************/

typedef struct
{
	uint16 initial_value;
	uint16 compare_value;
	Timer1_Prescaler prescaler;
	Timer1_Mode mode;
} Timer1_ConfigType;

/***********************************************************************************************************/

/*****************************************TIMER1_FUNCTIONS_PROTOTYPES***************************************/

void Timer1_init(const Timer1_ConfigType *Config_Ptr);
void Timer1_deInit(void);
void Timer1_setCallBack(void (*a_ptr)(void));

/***********************************************************************************************************/

#endif /* TIMER1_H_ */
