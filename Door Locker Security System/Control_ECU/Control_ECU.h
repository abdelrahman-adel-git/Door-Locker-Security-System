/*
 ============================================================================
 Name        : Control_ECU.h
 Author      : Abd-Elrahman Adel
 Date        : 5/11/2023
 ============================================================================
 */

#ifndef CONTROL_ECU_H_
#define CONTROL_ECU_H_

#include "my_std_types.h"

/**********************************************Preprocessor_Macros*******************************************/

#define CORRECT_PASSWORD 1
#define WRONG_PASSWORD 0

/************************************************************************************************************/

/*********************************************FUNCTIONS_PROTOTYPES*******************************************/

void Receive_password_1st_entry_from_HMI_ECU(uint8 *password_1st_entry_byte_ptr);
void Receive_password_2nd_entry_from_HMI_ECU(uint8 *password_2nd_entry_byte_ptr);
void Receive_Entered_password_from_HMI_ECU(uint8 *Entered_password_byte_ptr);
void Receive_password_two_entries(void);

void Save_password_to_EEPROM(uint8 *password_2nd_entry_byte_ptr);
void Read_password_from_EEPROM(uint8 *confirmed_password_ptr);
void start_password_3_trials(void);
uint8 Receive_the_chosen_option_from_HMI_ECU(void);
void Unlocking_Door_Call_Back_Function(void);
void Hold_Door_Call_Back_Function(void);
void Locking_Door_Call_Back_Function(void);
void Buzzer_Call_Back_Function(void);

/************************************************************************************************************/

#endif /* CONTROL_ECU_H_ */
