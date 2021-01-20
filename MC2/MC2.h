/**************************************************
 * File Name: MC2.h
 * Description: header file for MC2
 * Author: Habiba Mahmoud
 *
 ***************************************************/

#include "external_eeprom.h"
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
	READY6=60, READY7=70
};

/*
 * Number of overflows per second as the used mode is the normal mode
 * */

#define NUMBER_OF_OVERFLOWS_PER_SECOND 32
/*******************************************************************************
 * FUNCTIONS PROTYPE
 *******************************************************************************/
void motor_open(void);
void motor_close(void);
void Recive_Write(enum READY R);
