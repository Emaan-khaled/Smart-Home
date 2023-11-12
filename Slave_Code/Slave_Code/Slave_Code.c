/*
 * Slave_Code.c
 *
 * Created: 11/10/2023 10:39:22 AM
 *  Author: eman
 */ 


#include <avr/io.h>
#include "SPI.h"
#include "SLAVE_MACROS.h"
#include "DIO.h"
#include "LED.h"
#include "ADC.h"
#include "TIMER.h"
#include "std_macros.h"

volatile short required_temperature=24; // the required temperature which sent from Master with initial value 24
volatile short temp_sensor_reading=0; // the temperature of the room
volatile char counter=0; // the counter which determine the periodic time of implementing ISR
volatile char last_air_conditioning_value=AIR_CONDTIONING_OFF; // last air conditioning value which will help in hysteresis

int main(void)
{
	/**************** INTLIZATION *************/
	SPI_Slave_int();
	TIMER0_int(CTC,1024,78);
	led_int(ROOM1_PORT,ROOM1_PIN);
	led_int(ROOM2_PORT,ROOM2_PIN);
	led_int(ROOM3_PORT,ROOM3_PIN);
	led_int(ROOM4_PORT,ROOM4_PIN);
	led_int(TV_PORT,TV_PIN);
	led_int(AIR_COND_PORT,AIR_COND_PIN);
	ADC_int(0);
	char request = DEFAULT_ACK;//the value that is received from the master
	char response = DEFAULT_ACK;//the values that is sent back to the master
	
	
	
	
    while(1)
    {
		request = SPI_Slave_TX_char(DEFAULT_ACK);
		
		switch (request)
		{
        /*********************************   STATUS COMMANDS ********************************/
        case ROOM1_STATUS:
        if (LED_Read_Status(ROOM1_PORT,ROOM1_PIN)==0)
        {
	        response = OFF_STATUS;
        }
        else if (LED_Read_Status(ROOM1_PORT,ROOM1_PIN)==1)
        {
	        response = ON_STATUS;
        }
        else
        {
        }
        SPI_Slave_TX_char(response);//response to the transmitter with the status
        break;
		/**************/
        case ROOM2_STATUS:
        if (LED_Read_Status(ROOM2_PORT,ROOM2_PIN)==0)
        {
	        response = OFF_STATUS;
        }
        else if (LED_Read_Status(ROOM2_PORT,ROOM2_PIN)==1)
        {
	        response = ON_STATUS;
        }
        else
        {
        }
        SPI_Slave_TX_char(response);
        break;
		/**************/
        case ROOM3_STATUS:
        if (LED_Read_Status(ROOM3_PORT,ROOM3_PIN)==0)
        {
	        response = OFF_STATUS;
        }
        else if (LED_Read_Status(ROOM3_PORT,ROOM3_PIN)==1)
        {
	        response = ON_STATUS;
        }
        else
        {
        }
        SPI_Slave_TX_char(response);
        break;
		/**************/
        case ROOM4_STATUS:
        if (LED_Read_Status(ROOM4_PORT,ROOM4_PIN)==0)
        {
	        response = OFF_STATUS;
        }
        else if (LED_Read_Status(ROOM4_PORT,ROOM4_PIN)==1)
        {
	        response = ON_STATUS;
        }
        else
        {
        }
       SPI_Slave_TX_char(response);
        break;
		/**************/
        case AIR_COND_STATUS:
        if (LED_Read_Status(AIR_COND_PORT,AIR_COND_PIN)==0)
        {
	        response = OFF_STATUS;
        }
        else if (LED_Read_Status(AIR_COND_PORT,AIR_COND_PIN)==1)
        {
	        response = ON_STATUS;
        }
        else
        {
        }
        SPI_Slave_TX_char(response);
        break;
		/**************/
        case TV_STATUS:
        if (LED_Read_Status(TV_PORT,TV_PIN)==0)
        {
	        response = OFF_STATUS;
        }
        else if (LED_Read_Status(TV_PORT,TV_PIN)==1)
        {
	        response = ON_STATUS;
        }
        else
        {
        }
        SPI_Slave_TX_char(response);
        break;
		/*********************************   TURN ON COMMANDS ********************************/
		case ROOM1_TURN_ON:
		led_on(ROOM1_PORT,ROOM1_PIN);
		break;
		
		case ROOM2_TURN_ON:
		led_on(ROOM1_PORT,ROOM2_PIN);
		break;
		
		case ROOM3_TURN_ON:
		led_on(ROOM3_PORT,ROOM3_PIN);
		break;
		
		case ROOM4_TURN_ON:
		led_on(ROOM4_PORT,ROOM4_PIN);
		break;
		
		case AIR_COND_TURN_ON:
		TIMER0_int(CTC,1024,78);
		led_on(AIR_COND_PORT,AIR_COND_PIN);
		break;
		
		case TV_TURN_ON:
		led_on(TV_PORT,TV_PIN);
		break;
		
		/*********************************   TURN OFF COMMANDS ********************************/
		case ROOM1_TURN_OFF:
		led_off(ROOM1_PORT,ROOM1_PIN);
		break;
		
		case ROOM2_TURN_OFF:
		led_off(ROOM2_PORT,ROOM2_PIN);
		break;
		
		case ROOM3_TURN_OFF:
		led_off(ROOM3_PORT,ROOM3_PIN);
		break;
		
		case ROOM4_TURN_OFF:
		led_off(ROOM4_PORT,ROOM4_PIN);
		break;
		
		case AIR_COND_TURN_OFF:
		timer0_stop();
		led_off(AIR_COND_PORT,AIR_COND_PIN);
		break;
		case TV_TURN_OFF:
		led_off(TV_PORT,TV_PIN);
		break;
		
		/*********************************   Set temperature   ********************************/
		case SET_TEMPERATURE:
		required_temperature = SPI_Slave_TX_char(DEFAULT_ACK);
		break;//break the switch case
	}
}
}

     ISR(TIMER0_COMP_vect)
      {
	    counter++;
	    if(counter>=10) 
     	{
		counter=0;
		temp_sensor_reading=(0.25*ADC_READ());
		if (temp_sensor_reading>=(required_temperature+1))
		{
			led_on(AIR_COND_PORT,AIR_COND_PIN);
			last_air_conditioning_value=AIR_CONDTIONING_ON;
		}
		else if (temp_sensor_reading<=(required_temperature-1))
		{
			led_off(AIR_COND_PORT,AIR_COND_PIN);
			last_air_conditioning_value=AIR_CONDTIONING_OFF;
		}
		else if (required_temperature==temp_sensor_reading)
		{
			if (last_air_conditioning_value==AIR_CONDTIONING_ON)
			{
				led_on(AIR_COND_PORT,AIR_COND_PIN);
			}
			else if (last_air_conditioning_value==AIR_CONDTIONING_OFF) 
			{
				led_off(AIR_COND_PORT,AIR_COND_PIN);
			}
		}
        
    }
}	
	

