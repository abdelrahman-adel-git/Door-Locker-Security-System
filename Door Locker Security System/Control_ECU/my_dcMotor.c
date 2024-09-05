/*
 ============================================================================
 Name        : my_dcMotor.c
 Author      : Abd-Elrahman Adel
 Description : Fan controller System Project
 Date        : 11/10/2023
 ============================================================================
 */
#include "my_dcMotor.h"
#include "Timer0.h"

Fan_State currentFanState;
extern Timer0_ConfigType Timer0_Configuartions =
{ 0, TIMER0_FCPU_8, TIMER0_FAST_PWM_MODE };

void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DCMOTOR_E1_PORT_ID, DCMOTOR_E1_PIN_ID, PIN_OUTPUT);

	GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_LOW);

	currentFanState = FAN_OFF;

}
void DcMotor_Rotate(DcMotor_State state, uint8 speed)
{
	switch (state)
	{
	case STOP:
		GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_LOW);
		Timer0_deInit();
		currentFanState = FAN_OFF;
		break;
	case CW:
		GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_LOW);
		GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_HIGH);
		Timer0_Configuartions.duty_cycle = speed;
		Timer0_Configuartions.prescaler = TIMER0_FCPU_8;
		Timer0_init(&Timer0_Configuartions);
		currentFanState = FAN_ON;
		break;
	case ACW:
		GPIO_writePin(DCMOTOR_IN1_PORT_ID, DCMOTOR_IN1_PIN_ID, LOGIC_HIGH);
		GPIO_writePin(DCMOTOR_IN2_PORT_ID, DCMOTOR_IN2_PIN_ID, LOGIC_LOW);
		Timer0_Configuartions.duty_cycle = speed;
		Timer0_Configuartions.prescaler = TIMER0_FCPU_8;
		Timer0_init(&Timer0_Configuartions);
		currentFanState = FAN_ON;
		break;
	}
}

