/*
 ============================================================================
 Name        : my_gpio.c
 Author      : Abd-Elrahman Adel
 Date        : 25/9/2023
 ============================================================================
 */
#include "my_gpio.h"

/*********************************************PINS_FUNCTIONS************************************************/
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{
	(port_num >= GPIO_NUM_OF_PORTS || pin_num >= GPIO_NUM_OF_PINS) ? /*DO NOTHING*/: GPIO_DDR_SETUP_PIN_DIRECTION(port_num, pin_num, direction);
}

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{
	(port_num >= GPIO_NUM_OF_PORTS || pin_num >= GPIO_NUM_OF_PINS) ? /*DO NOTHING*/: GPIO_PORT_WRITE_PIN_VALUE(port_num, pin_num, value);
}

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{
	return (port_num >= GPIO_NUM_OF_PORTS || pin_num >= GPIO_NUM_OF_PINS) ? LOGIC_LOW : GPIO_PIN_READ_PIN_VALUE(port_num, pin_num);
}
/***********************************************************************************************************/

/********************************************PORTS_FUNCTIONS************************************************/
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{
	(port_num >= GPIO_NUM_OF_PORTS) ? /*DO NOTHING*/: GPIO_DDR_SETUP_PORT_DIRECTION(port_num, direction);
}
void GPIO_writePort(uint8 port_num, uint8 value)
{
	(port_num >= GPIO_NUM_OF_PORTS) ? /*DO NOTHING*/: GPIO_PORT_WRITE_PORT_VALUE(port_num, value);
}
uint8 GPIO_readPort(uint8 port_num)
{
	return (port_num >= GPIO_NUM_OF_PORTS) ? LOGIC_LOW : GPIO_PIN_READ_PORT_VALUE(port_num);
}
/***********************************************************************************************************/
