/*
 ============================================================================
 Name        : Control_ECU.c
 Author      : Abd-Elrahman Adel
 Date        : 30/10/2023
 ============================================================================
 */

#include "my_gpio.h"
#include "util/delay.h"
#include "Timer0.h"
#include "Timer1.h"
#include "my_dcMotor.h"
#include "my_uart.h"
#include "my_twi.h"
#include "external_eeprom.h"
#include "Buzzer.h"
#include <string.h>
#include "Control_ECU.h"

/*********************************************Globale_Variables**********************************************/

/*Here is the address of the password in which it will be saved in the EEPROM
 * I've chosen random addresses instead of storing the password in consecutive addresses*/
uint16 password_address_in_EEPROM[4] =
{ 0x0F1B, 0x0C3A, 0x0D6C, 0x0E92 };

uint32 password_1st_entry;
uint32 password_2nd_entry;
uint8 *password_1st_entry_1st_byte_address = (uint8*) &password_1st_entry;
uint8 *password_2nd_entry_1st_byte_address = (uint8*) &password_2nd_entry;
uint32 Entered_password;
uint8 *Entered_password_1st_byte_address = (uint8*) &Entered_password;

uint8 Passwords_matching_status_message[14];
const char *matched_message = "Pass matched#";
const char *not_matched_message = "Pass not matched#";

Timer0_ConfigType Timer0_Configuartions;

UART_ConfigType Uart_Configurations =
{ UART_8_BITS, DISABLED_PARITY, STOP_BIT_1, bps_9600 };

TWI_ConfigType Twi_Configurations =
{ 0x01, TWI_BIT_RATE_PRESCALER_1 };

Timer1_ConfigType LockingandUnlocking_Door_Configurations =
{ 0, 58593, TIMER1_FCPU_1024, TIMER1_CTC_MODE };

Timer1_ConfigType Holding_Door_Configurations =
{ 0, 23437, TIMER1_FCPU_1024, TIMER1_CTC_MODE };

Timer1_ConfigType Buzzer_Configurations =
{ 0, 58593, TIMER1_FCPU_1024, TIMER1_CTC_MODE };

uint32 Confirmed_password;
uint8 Chosen_option;
volatile uint8 g_Timer1_tick = 0;

/************************************************************************************************************/

/*========================================================================================================================*/
int main(void)
{

	/*Initializations*/
	DcMotor_Init();
	Buzzer_init();
	UART_init(&Uart_Configurations);
	TWI_init(&Twi_Configurations);

	SREG.Bits.I = 1; /*Enable Interrupts*/

	/*here the Control_ECU keeps receiving the two entered passwords from the HMI_ECU and won't save the password in the
	 * EEPROM unless the HMI_ECU sends two matching passwords*/
	Receive_password_two_entries();

	Save_password_to_EEPROM(password_2nd_entry_1st_byte_address); /*saving the password to the EEPROM*/
	Read_password_from_EEPROM((uint8*) &Confirmed_password); /*reading the password from the EEPROM and
	 *                                                          storing it in a variable*/

	/*Informing the HMI_ECU that the two passwords are matching so it can continue to the main options screen*/
	strcpy((char*) Passwords_matching_status_message, matched_message);
	UART_sendString((const uint8*) Passwords_matching_status_message);

	for (;;)
	{
		Chosen_option = Receive_the_chosen_option_from_HMI_ECU(); /*receive the chosen option*/
		switch (Chosen_option)
		{
		case '+':
			start_password_3_trials(); /*receive the password from the HMI_ECU for maximum 3 times*/
			if (Entered_password != Confirmed_password)
			{
				/*turning on the buzzer for 1 minute*/
				Buzzer_on();
				Timer1_setCallBack(Buzzer_Call_Back_Function);
				Timer1_init(&Buzzer_Configurations);
			}
			else
			{
				/*starts the unlocking and locking door operation*/
				DcMotor_Rotate(CW, 100);
				Timer1_setCallBack(Unlocking_Door_Call_Back_Function);
				Timer1_init(&LockingandUnlocking_Door_Configurations);
			}

			break;
		case '-':
			start_password_3_trials(); /*receive the password from the HMI_ECU for maximum 3 times*/
			if (Entered_password != Confirmed_password)
			{
				/*turning on the buzzer for 1 minute*/
				Buzzer_on();
				Timer1_setCallBack(Buzzer_Call_Back_Function);
				Timer1_init(&Buzzer_Configurations);
			}
			else
			{
				/*here the Control_ECU keeps receiving the new password two entries from the HMI_ECU and
				 * won't save the password in the EEPROM unless the HMI_ECU sends two matching passwords*/
				Receive_password_two_entries();

				Save_password_to_EEPROM(password_2nd_entry_1st_byte_address); /*saving the new password to the EEPROM*/
				Read_password_from_EEPROM((uint8*) &Confirmed_password); /*reading the new password from the EEPROM and
				 *                                                         storing in a variable*/

				/*Informing the HMI_ECU that the new password two entries are matching
				 * so it can continue to the main options screen*/
				strcpy((char*) Passwords_matching_status_message, matched_message);
				UART_sendString((const uint8*) Passwords_matching_status_message);
			}
			break;
		}

	}
}
/*========================================================================================================================*/

/**********************************************FUNCTIONS_DEFINITIONS*******************************************************/

void Receive_password_1st_entry_from_HMI_ECU(uint8 *password_1st_entry_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, password_1st_entry_byte_ptr++)
	{
		(*password_1st_entry_byte_ptr) = UART_recieveByte();
	}
}
void Receive_password_2nd_entry_from_HMI_ECU(uint8 *password_2nd_entry_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, password_2nd_entry_byte_ptr++)
	{
		(*password_2nd_entry_byte_ptr) = UART_recieveByte();
	}
}

void Receive_Entered_password_from_HMI_ECU(uint8 *Entered_password_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, Entered_password_byte_ptr++)
	{
		(*Entered_password_byte_ptr) = UART_recieveByte();
	}
}

void Receive_password_two_entries(void)
{
	do
	{
		Receive_password_1st_entry_from_HMI_ECU(password_1st_entry_1st_byte_address);
		Receive_password_2nd_entry_from_HMI_ECU(password_2nd_entry_1st_byte_address);
		if (password_1st_entry != password_2nd_entry)
		{
			strcpy((char*) Passwords_matching_status_message, not_matched_message);
			UART_sendString((const uint8*) Passwords_matching_status_message);
		}
	} while (password_1st_entry != password_2nd_entry);
}

void Save_password_to_EEPROM(uint8 *password_2nd_entry_byte_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, password_2nd_entry_byte_ptr++)
	{
		EEPROM_writeByte(password_address_in_EEPROM[i], *password_2nd_entry_byte_ptr);
		_delay_ms(10);
	}
}
void Read_password_from_EEPROM(uint8 *confirmed_password_ptr)
{
	uint8 i;
	for (i = 0; i < 4; i++, confirmed_password_ptr++)
	{
		EEPROM_readByte(password_address_in_EEPROM[i], confirmed_password_ptr);
		_delay_ms(10);
	}
}

void start_password_3_trials(void)
{
	uint8 i;
	for (i = 0; i < 3; i++)
	{
		Receive_Entered_password_from_HMI_ECU(Entered_password_1st_byte_address);
		if (Entered_password != Confirmed_password)
			UART_sendByte(WRONG_PASSWORD);
		else
		{
			UART_sendByte(CORRECT_PASSWORD);
			return;
		}
	}
}

uint8 Receive_the_chosen_option_from_HMI_ECU(void)
{
	return UART_recieveByte();
}

void Unlocking_Door_Call_Back_Function(void)
{
	g_Timer1_tick++;
	if (g_Timer1_tick == 2)
	{
		DcMotor_Rotate(STOP, 0);
		g_Timer1_tick = 0;
		Timer1_deInit();
		Timer1_setCallBack(Hold_Door_Call_Back_Function);
		Timer1_init(&Holding_Door_Configurations);
	}

}

void Hold_Door_Call_Back_Function(void)
{
	DcMotor_Rotate(ACW, 100);
	Timer1_deInit();
	Timer1_setCallBack(Locking_Door_Call_Back_Function);
	Timer1_init(&LockingandUnlocking_Door_Configurations);
}

void Locking_Door_Call_Back_Function(void)
{
	g_Timer1_tick++;
	if (g_Timer1_tick == 2)
	{
		DcMotor_Rotate(STOP, 0);
		g_Timer1_tick = 0;
		Timer1_deInit();
	}
}

void Buzzer_Call_Back_Function(void)
{
	g_Timer1_tick++;
	if (g_Timer1_tick == 8)
	{
		Buzzer_off();
		g_Timer1_tick = 0;
		Timer1_deInit();
	}
}

/************************************************************************************************************/

