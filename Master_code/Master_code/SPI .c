/*
 * SPI_.c
 *
 * Created: 11/3/2023 10:22:02 AM
 *  Author: eman
 */ 
#include "SPI.h"
#include <avr/io.h>
#include "std_macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"

void SPI_Master_int (void)
{
	//set pin SS, MISO, SCK as output
	DIO_set_pin_direction ('B',4,1);
	DIO_set_pin_direction ('B',5,1);
	DIO_set_pin_direction ('B',7,1);
	
	//master enable, SPI enable
	SET_BIT(SPCR,MSTR);
	//set clock
	SET_BIT(SPCR,SPR0);
	
	SET_BIT(SPCR,SPE);
	//start to genrate clk
	DIO_write_pin('B',4,1);
}

void SPI_Slave_int (void)
{
	//SPI enable
	SET_BIT(SPCR,SPE);
	DIO_set_pin_direction ('B',6,1);
	
	
}

char SPI_Master_TX_char (char Data)
{
	DIO_write_pin('B',4,0);
	SPDR=Data;
	while (READ_BIT(SPSR,SPIF)==0);
	return SPDR;
}

char SPI_Slave_TX_char (char Data)
{
	SPDR=Data;
	while (READ_BIT(SPSR,SPIF)==0);
	return SPDR;
}

char SPI_Master_TX_string (char *ptr)
{
	while ((*ptr)!=0)
	{
		SPI_Slave_TX_char(*ptr);
		_delay_ms(300);
		ptr++;
	}
}

