/*
 ============================================================================
 Name        : my_uart.c
 Author      : Abd-Elrahman Adel
 Date        : 30/10/2023
 ============================================================================
 */
#include "my_uart.h"
#include "my_gpio.h"
#include "my_common_macros.h"

void UART_init(const UART_ConfigType *Config_Ptr)
{
	uint16 ubrr_value = 0;

	UCSRA.Bits.U2X = 1;

	UCSRB.Bits.RXEN = 1;
	UCSRB.Bits.TXEN = 1;
	UCSRB.Bits.UCSZ2 = ((Config_Ptr->bit_data) & 0x04); /*inserting bit2 of bit_data in UCSZ2 bit*/

	UCSRC.Bits.URSEL = 1;
	UCSRC.Bits.USBS = Config_Ptr->stop_bit; /*inserting the stop bit in USBS bit*/
	UCSRC.Byte = (UCSRC.Byte & 0xCF) | (((Config_Ptr->parity) & 0x03) << 4); /*inserting parity in UPM1 & UPM0 bits*/
	UCSRC.Byte = (UCSRC.Byte & 0xF9) | (((Config_Ptr->bit_data) & 0x03) << 1); /*inserting bit1 & bit0 of bit_data in UCSZ1 & UCSZ0 bits*/

	ubrr_value = (uint16) (((F_CPU / ((Config_Ptr->baud_rate) * 8UL))) - 1);

	UBRRH.Byte = ubrr_value >> 8;
	UBRRL.Byte = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while (UCSRA.Bits.UDRE == 0)
		;

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR.Byte = data;

	/************************* Another Method *************************
	 UDR = data;
	 while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	 SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while (UCSRA.Bits.RXC == 0)
		;

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR.Byte;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{

	while (*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}

}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while (Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}
