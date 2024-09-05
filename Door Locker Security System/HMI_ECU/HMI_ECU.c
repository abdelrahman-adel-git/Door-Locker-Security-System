/*
 ============================================================================
 Name        : HMI_ECU.c
 Author      : Abd-Elrahman Adel
 Date        : 30/10/2023
 ============================================================================
 */

#include "my_keypad.h"
#include "my_lcd.h"
#include "my_uart.h"
#include "Timer1.h"
#include "util/delay.h"
#include <string.h>
#include "my_ATmega32_regs.h"
#include "HMI_ECU.h"

/*===========================================================================================================
 *                                          '=' is the Enter key
 *===========================================================================================================*/

/*********************************************Globale_Variables**********************************************/

uint32 password_1st_entry;
uint32 password_2nd_entry;
uint8 *password_1st_entry_1st_byte_address = (uint8*) &password_1st_entry;
uint8 *password_2nd_entry_1st_byte_address = (uint8*) &password_2nd_entry;
uint32 Entered_password;
uint8 *Entered_password_1st_byte_address = (uint8*) &Entered_password;
uint32 New_password;
uint8 *New_password_1st_byte_address = (uint8*) &New_password;
uint8 Entered_password_status = 0xFF;

Timer1_ConfigType LockingandUnlocking_Door_Configurations =
{ 0, 58593, TIMER1_FCPU_1024, TIMER1_CTC_MODE };

Timer1_ConfigType Holding_Door_Configurations =
{ 0, 23437, TIMER1_FCPU_1024, TIMER1_CTC_MODE };

Timer1_ConfigType Buzzer_Configurations =
{ 0, 58593, TIMER1_FCPU_1024, TIMER1_CTC_MODE };

uint8 key = 0;
UART_ConfigType Uart_Configurations =
{ UART_8_BITS, DISABLED_PARITY, STOP_BIT_1, bps_9600 };

uint8 Passwords_matching_status_message[13];
const char *matched_message = "Pass matched";
const char *not_matched_message = "Pass not matched";

volatile uint8 g_Timer1_tick = 0;
volatile uint8 g_Open_Door_task_completed = 0;
volatile uint8 g_Buzzer_task_completed = 0;
uint8 Chosen_option;

/************************************************************************************************************/

/*========================================================================================================================*/
int main(void)
{
	/*Initializations*/
	LCD_init();
	UART_init(&Uart_Configurations);

	SREG.Bits.I = 1; /*Enable Interrupts*/

	/*here is where the user enters the two passwords, the user won't exit this function unless the Control_ECU decides that
	 * two entered passwords are matching*/
	Begin_password_two_entries();

	/*Display for the user that the two entered passwords are matching*/
	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, matched_message);
	_delay_ms(400);

	for (;;)
	{
		Display_main_options(); /*displaying the main options screen*/

		/*the user is only allowed to enter either '+' or '-', otherwise the system will ignore the input and won't proceed
		 * unless he enters either '+' or '-'*/
		Choose_an_option(&Chosen_option);
		Send_the_chosen_option_to_Control_ECU(&Chosen_option); /*send the chosen option the Control_ECU
		 *                                                       so it can act accordingly*/
		switch (Chosen_option)
		{
		case '+':
			start_password_3_trials(); /*here the system starts the 3 password trials and sends the password
			 *                           to the Control_ECU and act according to it's response*/
			if (Entered_password_status == WRONG_PASSWORD)
			{
				g_Buzzer_task_completed = 0;

				LCD_displayStringRowColumn(0, 0, "Wrong Password  ");
				LCD_displayStringRowColumn(1, 0, "Wait for 1 min. ");
				Timer1_setCallBack(Buzzer_Call_Back_Function);
				Timer1_init(&Buzzer_Configurations); /*here the system shows the above message for 1 minute (buzzer time)*/

				/*locking the system until the 1 minute is over*/
				while (!g_Buzzer_task_completed)
					;
			}
			else
			{
				g_Open_Door_task_completed = 0; /*clearing the flag*/

				/*Displaying the unlocking and locking door messages*/
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Door Unlocking");
				Timer1_setCallBack(Unlocking_Door_Call_Back_Function);
				Timer1_init(&LockingandUnlocking_Door_Configurations);
				while (!g_Open_Door_task_completed)
					;
			}
			break;

		case '-':
			start_password_3_trials(); /*here the system starts the 3 password trials and sends the password
			 *                           to the Control_ECU and act according to it's response*/
			if (Entered_password_status == WRONG_PASSWORD)
			{
				g_Buzzer_task_completed = 0; /*clearing this flag so the system can be locked*/
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, "Wrong Password");
				LCD_displayStringRowColumn(1, 0, "Wait for 1 min.");
				Timer1_setCallBack(Buzzer_Call_Back_Function);
				Timer1_init(&Buzzer_Configurations); /*here the system shows the above message for 1 minute (buzzer time)*/

				/*locking the system until the 1 minute is over*/
				while (!g_Buzzer_task_completed)
					;
			}
			else
			{
				/*here the user begins the new password two entries and won't proceed further
				 * unless he enters matching passwords*/
				Begin_password_two_entries();

				/*Display for the user that the two entered passwords are matching*/
				LCD_clearScreen();
				LCD_displayStringRowColumn(0, 0, matched_message);
				_delay_ms(400);
			}
			break;
		}
	}
}
/*========================================================================================================================*/

/**********************************************FUNCTIONS_DEFINITIONS*******************************************************/

void Begin_password_first_entry(uint8 *key_ptr, uint32 *password_1st_entry_ptr)
{
	uint8 i;
	(*password_1st_entry_ptr) = 0;

	LCD_clearScreen();
	if (Chosen_option == '-')
		LCD_displayStringRowColumn(0, 0, "Enter new pass:");
	else
		LCD_displayStringRowColumn(0, 0, "Plz enter pass:");

	LCD_moveCursor(1, 0);
	for (i = 0; i < 5; i++)
	{
		do
		{
			*key_ptr = KEYPAD_getPressedKey();
			_delay_ms(400); /* Press time */
		} while (*key_ptr > 9);
		LCD_displayCharacter('*');
		(*password_1st_entry_ptr) = ((*password_1st_entry_ptr) * 10) + (*key_ptr);
	}
}

void Begin_password_second_entry(uint8 *key_ptr, uint32 *password_2nd_entry_ptr)
{
	uint8 i;
	(*password_2nd_entry_ptr) = 0;

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Plz re-enter the:");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass: ");
	for (i = 0; i < 5; i++)
	{
		do
		{
			*key_ptr = KEYPAD_getPressedKey();
			_delay_ms(400); /* Press time */
		} while (*key_ptr > 9);
		LCD_displayCharacter('*');
		(*password_2nd_entry_ptr) = ((*password_2nd_entry_ptr) * 10) + (*key_ptr);
	}
}

void Enter_password(uint8 *key_ptr, uint32 *Entered_password_ptr)
{
	uint8 i;
	(*Entered_password_ptr) = 0;

	LCD_clearScreen();
	LCD_displayStringRowColumn(0, 0, "Plz enter pass:");
	LCD_moveCursor(1, 0);
	for (i = 0; i < 5; i++)
	{
		do
		{
			*key_ptr = KEYPAD_getPressedKey();
			_delay_ms(400); /* Press time */
		} while (*key_ptr > 9);
		LCD_displayCharacter('*');
		(*Entered_password_ptr) = ((*Entered_password_ptr) * 10) + (*key_ptr);
	}
}

void Begin_password_two_entries(void)
{
	do
	{
		Begin_password_first_entry(&key, &password_1st_entry);
		Wait_for_Enter_button(&key);
		Begin_password_second_entry(&key, &password_2nd_entry);
		Wait_for_Enter_button(&key);

		Send_password_1st_entry_to_Control_ECU(password_1st_entry_1st_byte_address);
		Send_password_2nd_entry_to_Control_ECU(password_2nd_entry_1st_byte_address);

		UART_receiveString(Passwords_matching_status_message);
		if (strcmp((const char*) Passwords_matching_status_message, matched_message) != 0)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0, 0, not_matched_message);
			_delay_ms(400);
		}
	} while (strcmp((const char*) Passwords_matching_status_message, matched_message) != 0);

}

void Wait_for_Enter_button(uint8 *key_ptr)
{
	do
	{
		*key_ptr = KEYPAD_getPressedKey();
		_delay_ms(400); /* Press time */
	} while (*key_ptr != '=');
}

void Send_password_1st_entry_to_Control_ECU(uint8 *password_1st_entry_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, password_1st_entry_byte_ptr++)
	{
		UART_sendByte(*password_1st_entry_byte_ptr);
	}
}
void Send_password_2nd_entry_to_Control_ECU(uint8 *password_2nd_entry_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, password_2nd_entry_byte_ptr++)
	{
		UART_sendByte(*password_2nd_entry_byte_ptr);
	}
}

void Send_Entered_password_to_Control_ECU(uint8 *Entered_password_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, Entered_password_byte_ptr++)
	{
		UART_sendByte(*Entered_password_byte_ptr);
	}
}

void Display_main_options(void)
{
	LCD_displayStringRowColumn(0, 0, "+ : Open Door    ");
	LCD_displayStringRowColumn(1, 0, "- : Change Pass  ");
}

void Choose_an_option(uint8 *Chosen_option_ptr)
{
	do
	{
		*Chosen_option_ptr = KEYPAD_getPressedKey();
		_delay_ms(400);
	} while (*Chosen_option_ptr != '+' && *Chosen_option_ptr != '-');
}

void start_password_3_trials(void)
{
	uint8 i;
	for (i = 0; i < 3; i++)
	{
		Enter_password(&key, &Entered_password);
		Wait_for_Enter_button(&key);
		Send_Entered_password_to_Control_ECU(Entered_password_1st_byte_address);
		Entered_password_status = UART_recieveByte();
		if (Entered_password_status == CORRECT_PASSWORD)
			return;
	}
}

void Send_the_chosen_option_to_Control_ECU(uint8 *key_ptr)
{
	UART_sendByte(*key_ptr);
}

void Unlocking_Door_Call_Back_Function(void)
{
	g_Timer1_tick++;
	if (g_Timer1_tick == 2)
	{
		LCD_displayStringRowColumn(0, 0, "Door unlocked   ");
		Timer1_deInit();
		Timer1_setCallBack(Hold_Door_Call_Back_Function);
		Timer1_init(&Holding_Door_Configurations);
		g_Timer1_tick = 0;
	}

}

void Hold_Door_Call_Back_Function(void)
{
	LCD_displayStringRowColumn(0, 0, "Door Locking  ");
	Timer1_deInit();
	Timer1_setCallBack(Locking_Door_Call_Back_Function);
	Timer1_init(&LockingandUnlocking_Door_Configurations);
}

void Locking_Door_Call_Back_Function(void)
{
	g_Timer1_tick++;
	if (g_Timer1_tick == 2)
	{
		Timer1_deInit();
		g_Timer1_tick = 0;
		g_Open_Door_task_completed = 1;
	}
}

void Buzzer_Call_Back_Function(void)
{
	g_Timer1_tick++;
	if (g_Timer1_tick == 8)
	{
		g_Timer1_tick = 0;
		Timer1_deInit();
		g_Buzzer_task_completed = 1;
	}
}

/************************************************************************************************************/
