/*
 * Master_code.c
 *
 * Created: 11/8/2023 2:31:15 PM
 *  Author: eman
 */ 


#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "DIO.h"
#include "EEPROM.h"
#include "LCD-CONFIG.h"
#include "LCD.h"
#include "keypad.h"
#include "std_macros.h"
#include "main_conig.h"
#include "LED.h"
#include "TIMER.h"
#include "menu.h"
#include "SPI.h"

volatile short session_counter = 0;
char timeout_flag = FALSE;

int main(void)
{
	/**********************INTLIZATION*****************************************************************/
	char keypad_pressed = NOTPRESSED;
	char block_mode_flag = FALSE;
	char login_mode = NO_MODE;
	char temperature = 0;
	char temp_first_digit = NOT_SELECTED;
	char temp_second_digit = NOT_SELECTED;
	LCD_int('A');
	keypad_int('D');
	led_int (ADMIN_LED_PORT,ADMIN_LED_PIN);
	led_int (GUEST_LED_PORT,GUEST_LED_PIN);
	led_int (BLOCK_LED_PORT,BLOCK_LED_PIN);
	SPI_Master_int();
	/**********************WELCOME*******************************/
	LCD_send_string('A',"Welcome to smart");
	LCD_move_coursor('A',2,1);
	LCD_send_string('A',"home system");
	_delay_ms(1500);
	LCD_send_command('A',0X01);
	/*********************************************************/
	
	/************Check Admin and Guest passwords************************************************************************************************/
	
	if ( (EEPROM_READ(ADMIN_PASS_STATUS_ADDRESS)!=PASS_SET) || (EEPROM_READ(GUEST_PASS_STATUS_ADDRESS)!=PASS_SET) )
	{
		LCD_send_string('A',"Login for");
		LCD_move_coursor('A',2,1);
		LCD_send_string('A',"first time");
		_delay_ms(1500);
		LCD_send_command('A', 0X01);
		
	/************************************************/
	/*******************ADMIN PASSWORD***************/
	LCD_send_string('A', "Set Admin pass:");
	LCD_move_coursor('A',2,1);
	  char pass_counter=0;
      char pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
      while (pass_counter<PASS_SIZE)
      {
       	keypad_pressed= NOTPRESSED ;
	     while (keypad_pressed == NOTPRESSED )
	   {
		keypad_pressed = keypad_press('D');
	    }

	    pass[pass_counter]=keypad_pressed; //save password at array
	    LCD_send_char('A', keypad_pressed); //number appear at LCD
	    _delay_ms(300);
	    LCD_move_coursor('A',2,1+pass_counter);
	    LCD_send_char('A','*');
	    _delay_ms(200);
	    pass_counter++;
        }
		/**save password from array at EEPROM********/
      EEPROM_Write_Block(EEPROM_ADMIN_ADDRESS,pass,PASS_SIZE);
      EEPROM_WRITE(ADMIN_PASS_STATUS_ADDRESS,PASS_SET);
      LCD_send_command('A',0X01);
      LCD_send_string('A',"Password Saved");
      _delay_ms(1000);
      LCD_send_command('A',0X01);
	
		
   /****************************************************/
   /****************************GUEST PASSWORD*********/
   LCD_send_string('A', "Set guest pass:");
   LCD_move_coursor('A',2,1);
   pass_counter=0;
   char guest_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
      while (pass_counter<PASS_SIZE)
      {
       	keypad_pressed= NOTPRESSED ;
	     while (keypad_pressed == NOTPRESSED )
	   {
		keypad_pressed = keypad_press('D');
	    }

	   guest_pass[pass_counter]=keypad_pressed; //save password at array
	    LCD_send_char('A', keypad_pressed); //number appear at LCD
	    _delay_ms(300);
	    LCD_move_coursor('A',2,1+pass_counter);
	    LCD_send_char('A','*');
	    _delay_ms(200);
	    pass_counter++;
        }
		/**save password at EEPROM********/
      EEPROM_Write_Block(EEPROM_GUEST_ADDRESS,guest_pass,PASS_SIZE);
      EEPROM_WRITE(GUEST_PASS_STATUS_ADDRESS,PASS_SET);
      LCD_send_command('A',0X01);
      LCD_send_string('A',"Password Saved");
      _delay_ms(1000);
      LCD_send_command('A',0X01);
	  EEPROM_WRITE(LOGIN_BLOCKED_ADDRESS,FALSE);
	
	}		
	/***********************************************************/
	/***********************if this not first time*************/
     else
    {
	block_mode_flag = EEPROM_READ(LOGIN_BLOCKED_ADDRESS); //read the blocked location from EEPROM
    }
		/**************************************************************************************************************************************/

    while(1)
    {
		char NO_of_tries=0;
		keypad_pressed = NOTPRESSED;
		/*******session****/
		if ( timeout_flag==TRUE )
		{
			timer0_stop();
			session_counter = 0;
			timeout_flag=FALSE;
			login_mode=NO_MODE;
			keypad_pressed = NOTPRESSED;
			led_off(GUEST_LED_PORT,GUEST_LED_PIN);
			led_off(ADMIN_LED_PORT,ADMIN_LED_PIN);
			LCD_send_command('A',0X01);
			LCD_send_string('A',"Session Timeout");
			_delay_ms(1000);
		}
		
		
        while (login_mode==NO_MODE) 
		{
			if(block_mode_flag==TRUE)
			{
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Login blocked");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"wait 20 seconds");
				led_on(BLOCK_LED_PORT,BLOCK_LED_PIN);
				_delay_ms(BLOCK_MODE_TIME);
				NO_of_tries = 0; 
				block_mode_flag = FALSE;
				led_off(BLOCK_LED_PORT,BLOCK_LED_PIN);
				EEPROM_WRITE(LOGIN_BLOCKED_ADDRESS,FALSE);
			}
			LCD_send_command('A',0X01);
			LCD_send_string('A', "Select MODE");
			LCD_move_coursor('A',2,1);
			LCD_send_string('A', "ADMIN:1");
			LCD_move_coursor('A',2,10);
			LCD_send_string('A', "GUEST:2");
			keypad_pressed= NOTPRESSED ;
			while (keypad_pressed == NOTPRESSED )
			{
				keypad_pressed = keypad_press('D');
			}
			
		/******check which mode is select*****/
		if ((keypad_pressed!=SELECT_ADMIN)&& (keypad_pressed!=SELECT_GUEST) )
		{
			LCD_send_command('A',0X01);
			LCD_send_char('A', keypad_pressed);
			LCD_send_string('A', "WRONG MODE");
			LCD_move_coursor('A',2,1);
			LCD_send_string('A', "TRY AGAIN");
			_delay_ms(2000);
			LCD_send_command('A',0X01);
			keypad_pressed=NOTPRESSED;
			continue;
		  }
		  /***********/
		  LCD_send_command('A',0X01);
		char pass_counter=0;
	    char pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
        char stored_pass[PASS_SIZE]={NOT_STORED,NOT_STORED,NOT_STORED,NOT_STORED};
	    /***********/
		switch(keypad_pressed)
		{
			case SELECT_ADMIN:
			while(login_mode!=ADMIN_MODE){
				pass_counter=0;
			LCD_send_string('A', "ADMIN MODE");
			LCD_move_coursor('A',2,1);
			LCD_send_string('A', "PASSWORD:");
			_delay_ms(200);
			/*ADMIN write password*/
			while (pass_counter<PASS_SIZE)
			{
				keypad_pressed= NOTPRESSED ;
				while (keypad_pressed == NOTPRESSED )
				{
					keypad_pressed = keypad_press('D');
				}

				pass[pass_counter]=keypad_pressed; //save password at array
				LCD_send_char('A', keypad_pressed); //number appear at LCD
				_delay_ms(300);
				LCD_move_coursor('A',2,10+pass_counter);
				LCD_send_char('A','*');
				_delay_ms(200);
				pass_counter++;
			}
			EEPROM_Read_Block(EEPROM_ADMIN_ADDRESS,stored_pass,PASS_SIZE);//read the stored pass from the EEPROM

			/*compare passwords*/
			if ((Compare_Password(pass,stored_pass,PASS_SIZE)) == TRUE)
			{
				login_mode = ADMIN_MODE;
				NO_of_tries=0;
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Right pass");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"Admin mode");
				_delay_ms(1000);
				led_on(ADMIN_LED_PORT,ADMIN_LED_PIN);
				TIMER0_int(CTC,1024,78);
				LCD_send_command('A',0X01);
			}
			else
			{
				NO_of_tries++;
				login_mode = NO_MODE;
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong Pass");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"Tries left:");
				LCD_send_char('A', TRIES_ALLOWED-NO_of_tries+'0');
				_delay_ms(1000);
				LCD_send_command('A',0X01);
				if (NO_of_tries>=TRIES_ALLOWED)
				{
					EEPROM_WRITE(LOGIN_BLOCKED_ADDRESS,TRUE);
					block_mode_flag = TRUE;
					break;
				}
			}
		}
			
			break;
			/**********LOGIN GUEST***********/
			case SELECT_GUEST :
			while(login_mode!=GUEST_MODE){
				pass_counter=0;
			LCD_send_string('A', "GUEST MODE");
			LCD_move_coursor('A',2,1);
			LCD_send_string('A', "PASSWORD:");
			_delay_ms(200);
			/*GUEST write password*/
			while (pass_counter<PASS_SIZE)
			{
				keypad_pressed= NOTPRESSED ;
				while (keypad_pressed == NOTPRESSED )
				{
					keypad_pressed = keypad_press('D');
				}

				pass[pass_counter]=keypad_pressed; //save password at array
				LCD_send_char('A', keypad_pressed); //number appear at LCD
				_delay_ms(300);
				LCD_move_coursor('A',2,10+pass_counter);
				LCD_send_char('A','*');
				_delay_ms(200);
				pass_counter++;
			}
			EEPROM_Read_Block(EEPROM_GUEST_ADDRESS,stored_pass,PASS_SIZE);//read the stored pass from the EEPROM

			/*compare passwords*/
			if ((Compare_Password(pass,stored_pass,PASS_SIZE)) == TRUE)
			{
				login_mode = GUEST_MODE;
				NO_of_tries=0;
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Right pass");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"GUEST MODE");
				_delay_ms(2000);
				led_on(GUEST_LED_PORT,GUEST_LED_PIN);
				TIMER0_int(CTC,1024,76);
				LCD_send_command('A',0X01);
			}
			else
			{
				NO_of_tries++;
				login_mode = NO_MODE;
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong Pass");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"Tries left:");
				LCD_send_char('A', TRIES_ALLOWED-NO_of_tries+'0');
				_delay_ms(1000);
				LCD_send_command('A',0X01);
				if (NO_of_tries>=TRIES_ALLOWED)
				{
					EEPROM_WRITE(LOGIN_BLOCKED_ADDRESS,TRUE);
					block_mode_flag = TRUE;
					break;
				}
			}
		}
		
			break;
		}
}
/**********************************************************MENU*******************************************************************************/
        char show_menu = MAIN_MENU;

        while(timeout_flag!=TRUE)
          {
			 keypad_pressed=NOTPRESSED;
        	switch (show_menu)
	          {
/*CASE 1*/	    case MAIN_MENU:
		    do
		   {
			/******* print main Menu*******/
			LCD_send_command('A',0X01);
			LCD_send_string('A',"ROOM1=1  ROOM2=2");
			LCD_move_coursor('A',2,1);
			if(login_mode==ADMIN_MODE)
			{
				LCD_send_string('A',"ROOM3=3  MORE=4");
			}
			else if(login_mode==GUEST_MODE)
			{
				LCD_send_string('A',"ROOM3=3  ROOM4=4");
			}
		
			
			keypad_pressed = Get_Keypad_Pressed(login_mode); //USER (ADMIN OR GUEST) SELECT ONE OPTION FROM MENU
			_delay_ms(100);
			
			/*******CHECK WHICH OPTION IS SELECTED, AND SAVE THE OPTION IN THE VARIABLE (SHOW_MENU)******/
			if (keypad_pressed == SELECT_ROOM1)
			{
				show_menu = ROOM1_MENU;
			}
			else if (keypad_pressed == SELECT_ROOM2)
			{
				show_menu = ROOM2_MENU;
			}
			else if (keypad_pressed == SELECT_ROOM3)
			{
				show_menu = ROOM3_MENU;
			}
			else if (keypad_pressed == SELECT_ROOM4 && login_mode == GUEST_MODE)
			{
				show_menu = ROOM4_MENU;
			}
			else if (keypad_pressed == SELECT_MORE && login_mode == ADMIN_MODE)
			{
				show_menu = MORE_MENU;
			}
			else if(keypad_pressed != NOTPRESSED)
			{
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong input");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"Try again");
				_delay_ms(1500);
			}
			
			
		} while ( ((keypad_pressed < '1') || (keypad_pressed > '4') ) && (timeout_flag == FALSE) );
		
		break;
			/*******************************END OF MENU SELECTED*************************************************/
/*CASE2*/	 case MORE_MENU:
		     do
		   {
			/************* print more Menu *******/
			LCD_send_command('A',0X01);
			LCD_send_string('A',"ROOM4=1    TV=2");
			LCD_move_coursor('A',2,1);
			LCD_send_string('A',"Air.Cond=3 RET=4");
			/***********************************/
			keypad_pressed = Get_Keypad_Pressed(login_mode); //USER (ADMIN) SELECT ONE OPTION FROM MENU
			_delay_ms(100);
			
			if (keypad_pressed == SELECT_ROOM4_ADMIN)
			{
				show_menu = ROOM4_MENU;
			}
			else if (keypad_pressed== SELECT_TV)
			{
				show_menu = TV_MENU;
			}
			else if (keypad_pressed == SELECT_AIR_CONDITIONING)
			{
				show_menu = AIRCONDITIONING_MENU;
			}
			else if (keypad_pressed== ADMIN_RET_OPTION)
			{
				show_menu = MAIN_MENU;
			}
			else if(keypad_pressed != NOTPRESSED)
			{
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong input");
				LCD_move_coursor('A',2,1);
				LCD_send_string('A',"Try again");
				_delay_ms(1500);
			}
		} while (( (keypad_pressed < '1') || (keypad_pressed> '4') ) && (timeout_flag == FALSE));
		
		break;
		/*******************************END OF MORE MENU SELECTED*************************************************/
		case AIRCONDITIONING_MENU:
		do
		{
			/******************** print more Menu ******************/
			LCD_send_command('A',0X01);
			LCD_send_string('A',"1:Set temperature ");
			LCD_move_coursor('A',2,1);
			LCD_send_string('A',"2:Control  0:RET");
			/*******************************************************/
			keypad_pressed = Get_Keypad_Pressed(login_mode);
			_delay_ms(100);
			
			if (keypad_pressed == SELECT_SET_TEMPERATURE)
			{
				show_menu = TEMPERATURE_MENU;
			}
			else if (keypad_pressed == SELECT_AIR_COND_CTRL)
			{
				show_menu = AIRCOND_CTRL_MENU;
			}
			else if (keypad_pressed == SELECT_AIR_COND_RET)
			{
				show_menu = MORE_MENU;
			}
			else if(keypad_pressed != NOTPRESSED)
			{
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong input");
				_delay_ms(500);
			}
		} while (( (keypad_pressed < '0') || (keypad_pressed > '2') ) && (timeout_flag == FALSE));
		break;
		/************ROOM 1&2&3&4 MENU***************/
		case ROOM1_MENU:                                    /*CASE3*/
		Menu_Option(ROOM1_MENU,login_mode);
		show_menu = MAIN_MENU;
		break;
		/**********/
		case ROOM2_MENU:                                    /*CASE4*/
		Menu_Option(ROOM2_MENU,login_mode);
		show_menu = MAIN_MENU;
		break;
		/**********/
		case ROOM3_MENU:                                    /*CASE5*/
		Menu_Option(ROOM3_MENU,login_mode);
		show_menu = MAIN_MENU;
		break;
		/**********/
		case ROOM4_MENU:                                    /*CASE6*/
		Menu_Option(ROOM4_MENU,login_mode);
		if (login_mode == GUEST_MODE)
		{
			show_menu = MAIN_MENU;
		}
		else
		{
			show_menu = MORE_MENU;
		}
		break;
		/********** TV & AIR COND*********/
		case TV_MENU:                                       /*CASE7*/
		Menu_Option(TV_MENU,login_mode);
		show_menu = MORE_MENU;
		break;
		/**********/
		case AIRCOND_CTRL_MENU:                              /*CASE8*/
		Menu_Option(AIRCOND_CTRL_MENU,login_mode);
		show_menu = AIRCONDITIONING_MENU;
		break;
		/************/
		case TEMPERATURE_MENU:                              /*CASE9*/
		temperature = 0;
		while (temperature==0 && timeout_flag == FALSE)
		{
			keypad_pressed = NOTPRESSED;
			LCD_send_command('A',0X01);
			LCD_send_string('A',"Set temp.:__ ");
			LCD_send_char('A',DEGREES_SYMBOL);
			LCD_send_char('A','C'); 
			LCD_move_coursor('A',1,11);
			_delay_ms(200);
			/*******************************************************************************/
			keypad_pressed = Get_Keypad_Pressed(login_mode);
			_delay_ms(250);

			if (timeout_flag == TRUE) 
			{
				break;
			}
			if (keypad_pressed <'0' || keypad_pressed >'9')
			{
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong input");
				_delay_ms(500);
				continue;
			}
			else
			{
				LCD_send_char('A',keypad_pressed);
				temp_second_digit = keypad_pressed-'0';
				keypad_pressed = NOTPRESSED;
			}
			/*******************************************************************************/
			keypad_pressed = Get_Keypad_Pressed(login_mode);
			_delay_ms(250);
			
			if (timeout_flag == TRUE)
			{
				break;
			}
			if ((keypad_pressed <'0' || keypad_pressed >'9'))
			{
				LCD_send_command('A',0X01);
				LCD_send_string('A',"Wrong input");
				_delay_ms(500);
				continue;
			}
			else
			{
				LCD_send_char('A',keypad_pressed);
				temp_first_digit = keypad_pressed-'0';
				keypad_pressed = NOTPRESSED;
			}
			temperature = temp_second_digit*10 + temp_first_digit;
			SPI_Slave_TX_char(SET_TEMPERATURE);
			_delay_ms(200);
			SPI_Slave_TX_char(temperature);
			LCD_send_command('A',0X01);
			LCD_send_string('A',"Temperature Sent");
			_delay_ms(500);
		}
		show_menu = AIRCONDITIONING_MENU;
		break;
		}
		
		}		
	  
		   }}	  
	  
	  
	  
	  ISR(TIMER0_COMP_vect)
	  {
		  session_counter++;
	  }