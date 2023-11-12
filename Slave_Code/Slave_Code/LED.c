/*
 * LED.c
 *
 * Created: 10/5/2023 5:48:21 PM
 *  Author: eman
 */ 
#include "DIO.h"
void led_int(char port,char pin)
{
	DIO_set_pin_direction (port,pin,1);
}

void led_on(char port, char pin)
{
	DIO_write_pin (port,pin,1);
}

void led_off(char port, char pin)
{
	DIO_write_pin (port,pin,0);
}

void led_tog(char port, char pin)
{
	DIO_toggle_pin (port,pin);
}

char LED_Read_Status(char port_name,char pin_number)
{
	return DIO_read_pin(port_name,pin_number);
}