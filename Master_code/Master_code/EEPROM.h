/*
 * EEPROM.h
 *
 * Created: 10/23/2023 6:47:09 PM
 *  Author: eman
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include <avr/io.h>
#include "std_macros.h"
void EEPROM_WRITE (short address , char data);
char EEPROM_READ (short address);
void EEPROM_Read_Block(const short Address, char* data,const short size);
void EEPROM_Write_Block (const short Address, const char* Data,const short size);

#endif /* EEPROM_H_ */