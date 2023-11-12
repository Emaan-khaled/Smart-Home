/*
 * menu.h
 *
 * Created: 11/9/2023 12:24:30 PM
 *  Author: eman
 */ 


#ifndef MENU_H_
#define MENU_H_
#include "main_conig.h"
#define F_CPU 8000000UL
#include <util/delay.h>
char Compare_Password(const char* pass1,const char* pass2,const char size);
char Get_Keypad_Pressed(const char Login_Mode);
void Menu_Option(const char Selected_Room,const char Login_Mode);

#endif /* MENU_H_ */