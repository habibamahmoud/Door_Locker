/*********************************************
 * File name: MC1.h
 * Description: Header file for MC1
 * Author: Habiba Mahmoud
 ********************************************/

#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer0.h"

/*
 *this enum have the orders that will be sent to the other Micro-controller
 */

enum READY{
	READY1=10,
	READY2=20,
	READY3=30,
	READY4=40,
	READY5=50,
	READY6=60,READY7=70
};

/*
 * Number of overflows per second as the used mode is the normal mode
 * */

#define NUMBER_OF_OVERFLOWS_PER_SECOND 32

/***********************************************************
 *   FUNCTIONS PROTOTYPE
 *********************************************************/

void get_pass(char arr[],uint8 sent_pass[]);
uint8 compare(uint8 new_pass[], uint8 match_pass[] );
void F_compare(uint8 new_pass[], uint8 match_pass[],char arr[],enum READY R);
