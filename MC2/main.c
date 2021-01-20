/*
 * File Name: main.c
 * Description: Source file
 * Author: Habiba Mahmoud
 */
#include "MC2.h"


uint8 g_tick = 0;
uint8 second;

/* Description :
 * For clock = 8Mhz and prescaler F_CPU/1024 every count will take 128 microsecond
 * so put initial timer counter=0  0 --> 255 (32ms per overflow)
 * so we need timer to overflow 31 times to get a 1 second
 * This is the ISR of timer0 overflow mode
 */

ISR(TIMER0_OVF_vect)
{
	g_tick++;
	if (g_tick == NUMBER_OF_OVERFLOWS_PER_SECOND)
	{
		second++;
		g_tick = 0; //clear the tick counter again to count a new 0.5 second
	}
}




/*
 * START OF MAIN FUNCTION
 */

int main (void){

	/*
	 * initialise UART DRIVER
	 */

	UART_init();

	/*
	 * initialise EEPROM DRIVER
	 */

	EEPROM_init();

	/*
	 * Variable Declaration
	 */

	uint8 i,x[7];

	Recive_Write(READY1);

	while(1){

		/*
		 * Variable Declaration
		 */

		uint8 RECIEVE=UART_recieveByte();



		if(RECIEVE==READY2){
			while(RECIEVE!=READY2){};
			for(i=0;i<5;i++){
				UART_sendByte(READY2);
				EEPROM_readByte((0x000|i),&x[i]);
				UART_sendByte(x[i]);
				_delay_ms(100);
			}
			Recive_Write(READY3);
			Recive_Write(READY1);
		}


		else if(RECIEVE==READY6){
			while(RECIEVE!=READY6){};
			for(i=0;i<5;i++){
				UART_sendByte(READY6);
				EEPROM_readByte((0x000|i),&x[i]);
				UART_sendByte(x[i]);
				_delay_ms(100);
			}

			uint8 recieve=UART_recieveByte();

			/*
			 * ALARM SETED FOR FOUR SECONDS
			 */

			if (recieve==READY4){
				_delay_ms(100);
				SET_BIT(DDRA,0);
				SET_BIT(PORTA,0);
				timer0_init_normal_mode(T0_F_CPU_1024, 0);
				while (second != 4)
					;
				second = 0;
				CLEAR_BIT(PORTA,0);

			}

			else if (recieve==READY7){
				for(i=0;i<5;i++){
					UART_sendByte(READY7);
					x[i]=UART_recieveByte();
					EEPROM_writeByte((0x000|i),x[i]);
					_delay_ms(100);
				}
			motor_open();
			timer0_init_normal_mode(T0_F_CPU_1024, 0);
			while (second != 2)
				;
			second=0;

			motor_close();
			while (second != 2)
				;
			second = 0;
			PORTB=0XFC;
			timer0_deinit();
			}

	}
}
}
