/*
 ============================================================================
 Name        : my_dcMotor.h
 Author      : Abd-Elrahman Adel
 Description : Fan controller System Project
 Date        : 11/10/2023
 ============================================================================
 */

#ifndef MY_DCMOTOR_H_
#define MY_DCMOTOR_H_

#include "my_gpio.h"

#define DCMOTOR_IN1_PORT_ID PORTB_ID
#define DCMOTOR_IN1_PIN_ID PIN0_ID

#define DCMOTOR_IN2_PORT_ID PORTB_ID
#define DCMOTOR_IN2_PIN_ID PIN1_ID

#define DCMOTOR_E1_PORT_ID PORTB_ID
#define DCMOTOR_E1_PIN_ID PIN3_ID

typedef enum
{
	STOP, CW, ACW

} DcMotor_State;

typedef enum
{
	FAN_OFF, FAN_ON

} Fan_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* MY_DCMOTOR_H_ */
