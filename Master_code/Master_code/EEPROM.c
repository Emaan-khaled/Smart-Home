/*
 * EEPROM.c
 *
 * Created: 10/23/2023 6:46:52 PM
 *  Author: eman
 */ 

#include "EEPROM.h"


void EEPROM_WRITE (short address , char data)
{
	while ( ( (EECR & (1 << EEWE) ) >>EEWE ) == 1);
	EEARL=(char)address;
	EEARH=(char)(address>>8);
	
	EECR |= (1 << EERE);
	EEDR = data;
	
	SET_BIT (EECR,EEMWE);
	SET_BIT (EECR,EEWE);
	
}

char EEPROM_READ (short address)
{
	while (((EECR & (1 << EEWE))>>EEWE)==1);
	EEARL=(char)address;
	EEARH=(char)(address>>8);
	
	SET_BIT (EECR,EERE);
	
	return EEDR;
	
}

void EEPROM_Write_Block (const short Address, const char* Data,const short size)
{
	short counter = 0;
	while (counter < size)
	{
		
		while (( (EECR & (1 << EEWE) ) >>EEWE ) == 1);
		
		EEAR = Address + counter;

		
		EECR |= (1 << EERE);
		if (EEDR != (*(Data + counter)))
		{
			EEDR = *(Data + counter);

			
			EECR |= (1 << EEMWE);
			EECR |= (1 << EEWE);
		}
		else
		{

		}
		counter++;
	}
}

void EEPROM_Read_Block(const short Address, char* data,const short size)
{
	
	while (((EECR & (1 << EEWE))>>EEWE)==1);

	short counter = 0;

	while (counter < size) 
	{
		
		EEAR = Address + counter;
		EECR |= (1 << EERE);
		
		*(data + counter) = EEDR;

		counter++;
	}
}

