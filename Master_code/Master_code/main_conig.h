/*
 * main_conig.h
 *
 * Created: 11/8/2023 2:52:43 PM
 *  Author: eman
 */ 


#ifndef MAIN_CONIG_H_
#define MAIN_CONIG_H_

#define TRUE    (char) 1
#define FALSE (char) 0
#define NOT_STORED       0xFF
#define PASS_SIZE       (char) 4
#define TRIES_ALLOWED   (char) 3
#define PASS_SET  (char)0x01
#define PASS_NOT_SET (char)0xFF                 
#define ADMIN_PASS_STATUS_ADDRESS (short)0X100
#define GUEST_PASS_STATUS_ADDRESS (short)0X101
#define EEPROM_ADMIN_ADDRESS      (short)0X102
#define EEPROM_GUEST_ADDRESS      (short)0X106
#define LOGIN_BLOCKED_ADDRESS     (short)0X10A
/***********************************************/

#define NO_MODE        (char) 0
#define ADMIN_MODE     (char) 1
#define GUEST_MODE     (char) 2
#define SELECT_ADMIN   '1'
#define SELECT_GUEST   '2'
#define ADMIN_TIMEOUT (short)3000
#define GUEST_TIMEOUT (short)2000
/********************************************/
#define ADMIN_LED_PORT 'C'
#define ADMIN_LED_PIN   0
#define GUEST_LED_PORT 'C'
#define GUEST_LED_PIN   1
#define BLOCK_LED_PORT 'C'
#define BLOCK_LED_PIN   2
#define BLOCK_MODE_TIME (int)20000
/****************************************/
#define MAIN_MENU            (char)1
#define MORE_MENU            (char)2
#define ROOM1_MENU           (char)3
#define ROOM2_MENU           (char)4
#define ROOM3_MENU           (char)5
#define ROOM4_MENU           (char)6
#define TV_MENU              (char)7
#define AIRCONDITIONING_MENU (char)8
#define AIRCOND_CTRL_MENU    (char)9
#define TEMPERATURE_MENU     (char)10
/****************************************************/

#define CHECK_ADMIN_MODE        (char)'0'
#define CHECK_GUEST_MODE        (char)'1'

#define SELECT_ROOM1            (char)'1'
#define SELECT_ROOM2            (char)'2'
#define SELECT_ROOM3            (char)'3'
#define SELECT_ROOM4            (char)'4'
#define SELECT_MORE             (char)'4'

#define SELECT_ROOM4_ADMIN      (char)'1'
#define SELECT_TV               (char)'2'
#define SELECT_AIR_CONDITIONING (char)'3'
#define ADMIN_RET_OPTION        (char)'4'

#define SELECT_SET_TEMPERATURE  (char)'1'
#define SELECT_AIR_COND_CTRL    (char)'2'
#define SELECT_AIR_COND_RET     (char)'0'

/********************************************************************************************/
/***ADDRESS OF ROOMS,TV,AIR****/
#define ROOM1_STATUS    0x11
#define ROOM2_STATUS    0x12
#define ROOM3_STATUS    0x13
#define ROOM4_STATUS    0x14
#define TV_STATUS 		0x15
#define AIR_COND_STATUS 0x16

#define ROOM1_TURN_ON    0x21
#define ROOM2_TURN_ON    0x22
#define ROOM3_TURN_ON    0x23
#define ROOM4_TURN_ON    0x24
#define TV_TURN_ON 		 0x25
#define AIR_COND_TURN_ON 0x26

#define ROOM1_TURN_OFF    0x31
#define ROOM2_TURN_OFF    0x32
#define ROOM3_TURN_OFF    0x33
#define ROOM4_TURN_OFF    0x34
#define TV_TURN_OFF 	  0x35
#define AIR_COND_TURN_OFF 0x36

#define SET_TEMPERATURE 0x40

#define DEFAULT_ACK    0xFF
#define DEMAND_RESPONSE 0xFF

#define ON_STATUS   0x01
#define OFF_STATUS  0x00
/*******************************************/
#define NOT_STORED   0xFF
#define NOT_SELECTED 0xFF
#define BLOCK_MODE_TIME		   (int)20000
#define CHARACTER_PREVIEW_TIME (short)300
#define DEGREES_SYMBOL		   (char)0xDF

#define RET                     (char)'0'
#define OFF                     (char)'2'
#define ON                      (char)'1'
#endif /* MAIN_CONIG_H_ */