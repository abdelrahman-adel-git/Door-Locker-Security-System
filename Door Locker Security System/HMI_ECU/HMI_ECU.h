/*
 ============================================================================
 Name        : HMI_ECU.h
 Author      : Abd-Elrahman Adel
 Date        : 5/11/2023
 ============================================================================
 */

#ifndef HMI_ECU_H_
#define HMI_ECU_H_

#include "my_std_types.h"

/**********************************************Preprocessor_Macros*******************************************/

#define CORRECT_PASSWORD 1
#define WRONG_PASSWORD 0

/************************************************************************************************************/

/*********************************************FUNCTIONS_PROTOTYPES*******************************************/

void Begin_password_first_entry(uint8 *key_ptr, uint32 *password_1st_entry_ptr);
void Begin_password_second_entry(uint8 *key_ptr, uint32 *password_2nd_entry_ptr);
void Enter_password(uint8 *key_ptr, uint32 *Entered_password_ptr);
void Begin_password_two_entries(void);
void Wait_for_Enter_button(uint8 *key_ptr);

void Send_password_1st_entry_to_Control_ECU(uint8 *password_1st_entry_byte_ptr);
void Send_password_2nd_entry_to_Control_ECU(uint8 *password_2nd_entry_byte_ptr);
void Send_Entered_password_to_Control_ECU(uint8 *Entered_password_byte_ptr);

void Display_main_options(void);
void Choose_an_option(uint8 *Chosen_option_ptr);
void start_password_3_trials(void);
void Send_the_chosen_option_to_Control_ECU(uint8 *key_ptr);
void Unlocking_Door_Call_Back_Function(void);
void Hold_Door_Call_Back_Function(void);
void Locking_Door_Call_Back_Function(void);
void Buzzer_Call_Back_Function(void);

/************************************************************************************************************/

#endif /* HMI_ECU_H_ */
