/*
 ============================================================================
 Name        : Buzzer.h
 Author      : Abd-Elrahman Adel
 Date        : 2/11/2023
 ============================================================================
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "my_gpio.h"

#define BUZZER_PORT_ID PORTD_ID
#define BUZZER_PIN_ID PIN7_ID

void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);

#endif /* BUZZER_H_ */
