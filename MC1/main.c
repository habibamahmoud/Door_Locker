/*
 * File Name: main.c
 *
 * Author: Habiba Mahmoud
 */

#include "MC1.h"


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


//START OF MAIN FUNCTION

int main(void)
{

	//Variable Declarations

	uint8 i,key
	,new_pass[7],match_pass[7],old_pass[7],match_pass2[7];

	//init lcd
	LCD_init();

	//init uart
	UART_init();

	/* These statements out of main as I got first password for new user just one time
	 * I don't have to to make second MCU check for any stranger in this phase
	 * as my user is new one with no reserved data in E2PROM
	 */

	get_pass("Enter your PW:", new_pass);
	_delay_ms(10);
	get_pass("reEnter your PW:",match_pass);
	F_compare(new_pass,match_pass,"reEnter your PW:",READY1);


    while(1)
    {
    	/*
    	 * once the program started and get new password from new user you will continously
    	 * see the following messages
    	 */

		LCD_displayStringRowColumn(0,0,"- open");
		LCD_displayStringRowColumn(1,0,"+ New password");
		_delay_ms(1000);

		//Get user option to do specific actions on the second MCU

		key = KeyPad_getPressedKey(); /* get the pressed key number */
		_delay_ms(2000); /* Press time  */

		if (key =='+'){
			get_pass("Enter old PW:", old_pass);
			UART_sendByte(READY2);
			for(i=0;i<5;i++){
				while(UART_recieveByte()!=READY2){};
				match_pass2[i]=UART_recieveByte();
				_delay_ms(100);
			}
			//Check_Stranger(match_pass2,old_pass,"reEnter old PW:");
			F_compare(match_pass2,old_pass,"reEnter old PW:",READY3);
			get_pass("Enter new PW:", new_pass);
			_delay_ms(10);
			get_pass("reEnter new PW:",match_pass);
			F_compare(new_pass,match_pass,"reEnter new PW:",READY1);
		}

		else if(key=='-'){
			get_pass("Enter your PW:", new_pass);
			UART_sendByte(READY6);
			for(i=0;i<5;i++){
				while(UART_recieveByte()!=READY6){};
				match_pass2[i]=UART_recieveByte();
				_delay_ms(100);
			}

			F_compare(match_pass2,new_pass,"reEnter your PW:",READY7);
			_delay_ms(100);

			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayStringRowColumn(0,0,"DOOR OPEN");
			timer0_init_normal_mode(T0_F_CPU_1024, 0);
			while (second != 2)
				;
			second = 0;

			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayStringRowColumn(0,0,"DOOR CLOSE");
			while (second != 2)
				;
			second = 0;
		}
		LCD_sendCommand(CLEAR_COMMAND);
    }

}
