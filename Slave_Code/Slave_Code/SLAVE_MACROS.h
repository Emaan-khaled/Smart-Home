/*
 * SLAVE_MACROS.h
 *
 * Created: 11/10/2023 11:02:09 AM
 *  Author: eman
 */ 


#ifndef SLAVE_MACROS_H_
#define SLAVE_MACROS_H_

#define AIR_CONDTIONING_ON          (char)0x01
#define AIR_CONDTIONING_OFF			(char)0x00

/****************** PIN ******************/
#define ROOM1_PIN					(char)7
#define ROOM2_PIN					(char)6
#define ROOM3_PIN					(char)5
#define ROOM4_PIN					(char)4
#define TV_PIN						(char)3
#define AIR_COND_PIN				(char)2
/****************** PORT ******************/
#define AIR_COND_PORT 				(char)'D'
#define TV_PORT       				(char)'D'
#define ROOM1_PORT    				(char)'D'
#define ROOM2_PORT   				(char)'D'
#define ROOM3_PORT   				(char)'D'
#define ROOM4_PORT    				(char)'D'

/****************** LED PORT ******************/
#define ROOM1_LED_PORT			  'D'
#define ROOM2_LED_PORT			  'D'
#define ROOM3_LED_PORT			  'D'
#define ROOM4_LED_PORT			  'D'
#define TV_LED_PORT				  'D'
#define AIR_CONDITIONING_LED_PORT 'D'

/****************** LED PIN ******************/
#define ROOM1_LED_PIN			   0
#define ROOM2_LED_PIN			   1
#define ROOM3_LED_PIN			   2
#define ROOM4_LED_PIN			   3
#define TV_LED_PIN				   4
#define AIR_CONDITIONING_LED_PIN   5

/****************** STATUS ADDRESSES ******************/
#define ROOM1_STATUS    0x11
#define ROOM2_STATUS    0x12
#define ROOM3_STATUS    0x13
#define ROOM4_STATUS    0x14
#define TV_STATUS 		0x15
#define AIR_COND_STATUS 0x16

/****************** TURN ON ADDRESSES ******************/
#define ROOM1_TURN_ON    0x21
#define ROOM2_TURN_ON    0x22
#define ROOM3_TURN_ON    0x23
#define ROOM4_TURN_ON    0x24
#define TV_TURN_ON 		 0x25
#define AIR_COND_TURN_ON 0x26

/****************** TURN OFF ADDRESSES ******************/
#define ROOM1_TURN_OFF    0x31
#define ROOM2_TURN_OFF    0x32
#define ROOM3_TURN_OFF    0x33
#define ROOM4_TURN_OFF    0x34
#define TV_TURN_OFF 	  0x35
#define AIR_COND_TURN_OFF 0x36

/*********************************************/
#define SET_TEMPERATURE 0x40

#define DEFAULT_ACK    0xFF
#define DEMAND_RESPONSE 0xFF

#define ON_STATUS   0x01
#define OFF_STATUS  0x00

#endif /* SLAVE_MACROS_H_ */