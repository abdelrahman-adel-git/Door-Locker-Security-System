/*
 ============================================================================
 Name        : my_twi.h
 Author      : Abd-Elrahman Adel
 Date        : 30/10/2023
 ============================================================================
 */

#ifndef MY_TWI_H_
#define MY_TWI_H_

#include "my_std_types.h"

#define TWI_START         0x08
#define TWI_REP_START     0x10
#define TWI_MT_SLA_W_ACK  0x18
#define TWI_MT_SLA_R_ACK  0x40
#define TWI_MT_DATA_ACK   0x28
#define TWI_MR_DATA_ACK   0x50
#define TWI_MR_DATA_NACK  0x58

typedef uint8 TWI_Address;

typedef enum
{
	TWI_BIT_RATE_PRESCALER_1, TWI_BIT_RATE_PRESCALER_4, TWI_BIT_RATE_PRESCALER_16, TWI_BIT_RATE_PRESCALER_64
} TWI_BaudRate;

typedef struct
{
	TWI_Address address;
	TWI_BaudRate bit_rate;
} TWI_ConfigType;

void TWI_init(const TWI_ConfigType *Config_Ptr);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(uint8 data);
uint8 TWI_readByteWithACK(void);
uint8 TWI_readByteWithNACK(void);
uint8 TWI_getStatus(void);

#endif /* MY_TWI_H_ */
