/*
 ============================================================================
 Name        : Timer0.h
 Author      : Abd-Elrahman Adel
 Date        : 2/11/2023
 ============================================================================
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "my_std_types.h"

typedef uint8 Timer0_duty_cycle;

/************************************************TIMER0_ENUMS***********************************************/

typedef enum
{
	TIMER0_NORMAL_MODE, TIMER0_CTC_MODE = 2, TIMER0_FAST_PWM_MODE
} Timer0_Mode;

typedef enum
{
	PWM_NORMAL_MODE, PWN_NON_INVERTING_MODE = 2, PWM_INVERTING_MODE
} Timer0_FastPwmModeType;

typedef enum
{
	COMPARE_NORMAL, COMPARE_TOGGLE, COMPARE_CLEAR, COMPARE_SET
} Timer0_CompareType;

typedef enum
{
	TIMER0_NO_CLOCK, TIMER0_FCPU_1, TIMER0_FCPU_8, TIMER0_FCPU_64, TIMER0_FCPU_256, TIMER0_FCPU_1024, TIMER0_EXTERNAL_CLOCK_FALLING_EDGE, TIMER0_EXTERNAL_CLOCK_RISING_EDGE
} Timer0_Prescaler;

/***********************************************************************************************************/

/*********************************************TIMER0_STRUCTS************************************************/

typedef struct
{
	uint8 initial_value;
	Timer0_Prescaler prescaler;
	Timer0_Mode mode;
	Timer0_duty_cycle duty_cycle;
	uint8 compare_value;
} Timer0_ConfigType;

/***********************************************************************************************************/

/*****************************************TIMER0_FUNCTIONS_PROTOTYPES***************************************/

void Timer0_init(const Timer0_ConfigType *Config_Ptr);
void Timer0_deInit(void);
void Timer0_setCallBack(void (*a_ptr)(void));

/***********************************************************************************************************/

#endif /* TIMER0_H_ */
