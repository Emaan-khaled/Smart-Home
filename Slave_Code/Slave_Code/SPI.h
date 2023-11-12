/*
 * SPI.h
 *
 * Created: 11/3/2023 10:22:16 AM
 *  Author: eman
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "std_macros.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
void SPI_Master_int (void);
void SPI_Slave_int (void);
char SPI_Master_TX_char (char Data);
char SPI_Slave_TX_char (char Data);
char SPI_Master_TX_string (char *ptr);


#endif /* SPI_H_ */