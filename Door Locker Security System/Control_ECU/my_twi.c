/*
 ============================================================================
 Name        : my_twi.c
 Author      : Abd-Elrahman Adel
 Date        : 30/10/2023
 ============================================================================
 */
#include "my_twi.h"
#include "my_common_macros.h"
#include "my_ATmega32_regs.h"

void TWI_init(const TWI_ConfigType *Config_Ptr)
{
	/* Bit Rate: 400.000 kbps using zero pre-scaler TWPS=00 and F_CPU=8Mhz */
	TWBR.Byte = Config_Ptr->bit_rate;
	TWSR.Byte = 0x00;

	/* Two Wire Bus address my address if any master device want to call me: 0x1 (used in case this MC is a slave device)
	 General Call Recognition: Off */
	TWAR.Byte = Config_Ptr->address; // my address = 0x01 :)

	TWCR.Bits.TWEN = 1; /* enable TWI */
}

void TWI_start(void)
{
	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR.Byte = 0b10100100;

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (TWCR.Bits.TWINT == 0)
		;
}

void TWI_stop(void)
{
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1
	 */

	TWCR.Byte = 0b10010100;
}

void TWI_writeByte(uint8 data)
{
	/* Put data On TWI data Register */
	TWDR.Byte = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR.Byte = 0b10000100;
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (TWCR.Bits.TWINT == 0)
		;
}

uint8 TWI_readByteWithACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1
	 */

	TWCR.Byte = 0b11000100;
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (TWCR.Bits.TWINT == 0)
		;
	/* Read Data */
	return TWDR.Byte;
}

uint8 TWI_readByteWithNACK(void)
{
	/*
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
	TWCR.Byte = 0b10000100;
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (TWCR.Bits.TWINT == 0)
		;
	/* Read Data */
	return TWDR.Byte;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR.Byte & 0xF8;
	return status;
}

