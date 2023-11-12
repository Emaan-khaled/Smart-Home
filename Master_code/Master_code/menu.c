/*
 * menu.c
 *
 * Created: 11/9/2023 12:24:16 PM
 *  Author: eman
 */ 
#include "menu.h"
#define NOTPRESSED 0Xff
extern volatile short session_counter;
extern char timeout_flag;

char Compare_Password(const char* pass1,const char* pass2,const char size)
{
	char counter=0;
	char return_value = TRUE;
	while (counter<size)
	{
		if (*(pass1+counter)!=*(pass2+counter))
		{
			return_value= FALSE;
			break;
		}
		counter++;
	}
	return return_value;
}

char Get_Keypad_Pressed(const char Login_Mode)
{
	char keypad_pressed = NOTPRESSED;
	while (keypad_pressed == NOTPRESSED)
	{
		if ( (session_counter >= ADMIN_TIMEOUT && Login_Mode == ADMIN_MODE) || ( session_counter >= GUEST_TIMEOUT && Login_Mode == GUEST_MODE ))
		{
			timeout_flag = TRUE;
			break;
		}
		
		keypad_pressed = keypad_press('D');
	}
	return keypad_pressed;
}

void Menu_Option(const char Selected_Room,const char Login_Mode)
{
	char Status_Code  = 0;
	char TurnOn_Code  = 0;
	char TurnOff_Code = 0;
	char response      = DEFAULT_ACK;
	char keypad_pressed   = NOTPRESSED;
	
	do
	{
		LCD_send_command('A',0X01);
		
		switch(Selected_Room) //in each case we save addresses of status & turn on & turn off
		{
			case ROOM1_MENU:
			Status_Code = ROOM1_STATUS; 
			TurnOn_Code = ROOM1_TURN_ON;
			TurnOff_Code = ROOM1_TURN_OFF;
			LCD_send_string('A',"Room1 S:");
			break;
			/******************/
			case ROOM2_MENU:
			Status_Code = ROOM2_STATUS;
			TurnOn_Code = ROOM2_TURN_ON;
			TurnOff_Code = ROOM2_TURN_OFF;
			LCD_send_string('A',"Room2 S:");
			break;
			/******************/
			case ROOM3_MENU:
			Status_Code = ROOM3_STATUS;
			TurnOn_Code = ROOM3_TURN_ON;
			TurnOff_Code = ROOM3_TURN_OFF;
			LCD_send_string('A',"Room3 S:");
			break;
			/******************/
			case ROOM4_MENU:
			Status_Code = ROOM4_STATUS;
			TurnOn_Code = ROOM4_TURN_ON;
			TurnOff_Code = ROOM4_TURN_OFF;
			LCD_send_string('A',"Room4 S:");
			break;
			/******************/
			case TV_MENU:
			Status_Code = TV_STATUS;
			TurnOn_Code = TV_TURN_ON;
			TurnOff_Code = TV_TURN_OFF;
			LCD_send_string('A',"TV S:");
			break;
			/******************/
			case AIRCOND_CTRL_MENU:
			Status_Code = AIR_COND_STATUS;
			TurnOn_Code = AIR_COND_TURN_ON;
			TurnOff_Code = AIR_COND_TURN_OFF;
			LCD_send_string('A',"Air Cond. S:");
			break;
		}
		/*************************************************************************/
		
		SPI_Slave_TX_char(Status_Code);
		_delay_ms(100);
		response = SPI_Slave_TX_char(DEMAND_RESPONSE);
		if(response == ON_STATUS)
		{
			LCD_send_string('A',"ON");
		}
		else
		{
			LCD_send_string('A',"OFF");
		}

		LCD_move_coursor('A',2,1);
		LCD_send_string('A',"1-On 2-Off 0-RET");
		/********************/
		keypad_pressed = Get_Keypad_Pressed(Login_Mode); //select from on & off & ret
		_delay_ms(100);
		
		
		if (keypad_pressed == ON)
		{
			SPI_Slave_TX_char(TurnOn_Code);
		}
		else if (keypad_pressed == OFF)
		{
			SPI_Slave_TX_char(TurnOff_Code);
		}
		else if( (keypad_pressed != NOTPRESSED) && (keypad_pressed != '0') )
		{
			LCD_send_command('A',0X01);
			LCD_send_string('A',"Wrong input");
			_delay_ms(500);
		}
		else 
		{
			
		}
	} while ( ( (keypad_pressed < '0') || (keypad_pressed >'2') ) && (timeout_flag == FALSE)); 
}