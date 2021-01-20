/************************************************************************
 * File Name: MC2.c
 * Description: a source file for MC2
 * Author: Habiba Mahmoud
 *
 */

#include "MC2.h"

uint8 second;
/*
 * Motor Rotates clockwise
 */

void motor_open(void){
	/* configure pin PC0 and PC1 as output pins */
	DDRB |= 0x03;
	_delay_ms(1000);
	// Rotate the motor --> clock wise
	PORTB |= (1<<PB1);
	PORTB &= (~(1<<PB0));
}

/*
 * Motor rotates anti-clockwise
 */

void motor_close(void){
	/* configure pin PC0 and PC1 as output pins */
	DDRB |= 0x03;
	_delay_ms(1000);
	// Rotate the motor --> anti-clock wise
	PORTB |= (1<<PB0);
	PORTB &= (~(1<<PB1));
}

/*
 * This Function recieve specific flag to store the sent array in E2PROM memory
 */

void Recive_Write(enum READY R){
	uint8 i,x[7];
	uint8 recieve=UART_recieveByte();
	while(recieve!=R){};
	for(i=0;i<5;i++){
		UART_sendByte(R);
		x[i]=UART_recieveByte();
		EEPROM_writeByte((0x000|i),x[i]);
		_delay_ms(100);
	}
}
