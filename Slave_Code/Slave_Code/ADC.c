/*
 * ADC.c
 *
 * Created: 10/24/2023 10:00:25 PM
 *  Author: eman
 */ 
#include "ADC.h"
void ADC_int (char pin)
{
	SET_BIT (ADMUX,REFS0);
	SET_BIT (ADMUX,REFS1);
	SET_BIT (ADCSRA,ADEN);
	switch (pin)
	{
		case 0:
		CLR_BIT (ADMUX,MUX0);
		break;
		
		case 1:
		SET_BIT (ADMUX,MUX0);
		break;
		
		case 2:
		SET_BIT (ADMUX,MUX1);
		break;
		
		case 3:
		SET_BIT (ADMUX,MUX0);
		SET_BIT (ADMUX,MUX1);
		break;
		
		case 4:
		SET_BIT (ADMUX,MUX2);
		break;
		
		case 5:
		SET_BIT (ADMUX,MUX0);
		SET_BIT (ADMUX,MUX2);
		break;
		
		case 6:
		SET_BIT (ADMUX,MUX1);
		SET_BIT (ADMUX,MUX2);
		break;
		
		case 7:
		SET_BIT (ADMUX,MUX0);
		SET_BIT (ADMUX,MUX1);
		SET_BIT (ADMUX,MUX2);
		break;
	}	
	
	SET_BIT (ADCSRA,ADPS1);
	SET_BIT (ADCSRA,ADPS2);
}

char ADC_READ (void)
{
	short return_val;
	SET_BIT (ADCSRA,ADSC);
	while(READ_BIT(ADCSRA,ADSC)==1);
	SET_BIT (ADCSRA,ADSC);
	
	return_val=ADCL;
	return_val=return_val|(ADCH<<8);
	
	return return_val;
}

