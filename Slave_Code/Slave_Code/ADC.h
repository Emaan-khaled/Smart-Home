/*
 * ADC.h
 *
 * Created: 10/24/2023 10:00:39 PM
 *  Author: eman
 */ 


#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
#include "std_macros.h"
void ADC_int (char pin);
char ADC_READ (void);




#endif /* ADC_H_ */