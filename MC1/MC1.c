/*****************************************************************
 * File Name: MC1.c
 * Description: a source file for MC1
 * Author: Habiba Mahmoud
 *
 *****************************************************************/

#include "MC1.h"


uint8 second;
/*Description
 * This function take the password from user, Save it in array,
 * Take the required message from user as we get password from user in different Cases,
 * Handle that if the user after enter the password must press on/c in our case,
 * else error message will appear
 * */
 void get_pass(char arr[50],uint8 sent_pass[7]){
	uint8 key, i,j;
	LCD_sendCommand(CLEAR_COMMAND);
	LCD_displayStringRowColumn(0,0,arr);
	LCD_goToRowColumn(1,0);
	/* if any switch pressed for more than 500 ms it counts more than one press */
	for (i=0;i<5;i++){
		key = KeyPad_getPressedKey(); /* get the pressed key number */
		_delay_ms(2000); /* Press time  */
		LCD_displayCharacter('*'); /* display the pressed keypad switch */
		sent_pass[i]=key;
	}
	key = KeyPad_getPressedKey(); /* get the pressed key number */
	_delay_ms(2000); /* Press time  */
	while (key!=13){
		LCD_sendCommand(CLEAR_COMMAND);
    	LCD_displayStringRowColumn(0,0,"Err, press on/c");
    	key = KeyPad_getPressedKey(); /* get the pressed key number */
    	_delay_ms(2000); /* Press time  */
    	j++;

	}
	if (key==13){
		LCD_sendCommand(CLEAR_COMMAND);
	}
}
/*Description
 * This function took two arrays and return if they are matched or not
 * */

uint8 compare(uint8 new_pass[7], uint8 match_pass[7] ){
	uint8 i,j=0;
	for (i=0;i<5;i++){

		if (match_pass[i]==new_pass[i]){
			j++;
		}

	}

	if(j==5){
		LCD_displayStringRowColumn(0,0,"matched!");
	}
	else{
		LCD_displayStringRowColumn(0,0,"Not matched!");
	}

	return j;
}
/*Description
 *This function takes the return value of previous one , check on it
 *if j!=5 then stuck in this while loop till getting the right matched password
 *accepted number of times is 3 &
 *if user violate this condition, ALARM WILL BE SET FOR 3 SECONDS
 *[not applicable in real world but for simulation means]
 *else if j=5 store the password in E2PROM in second micro-controller
 *by sending specific key to start the operation whatever it is
 * */

 void F_compare(uint8 new_pass[7], uint8 match_pass[7],char arr[50],enum READY R){
	uint8 i,j=0,z=1;
	//get j
	j=compare(new_pass,match_pass);

	while(j!=5){
    	get_pass(arr,match_pass);
    	j=compare(new_pass,match_pass);
    	z++;
    	/*Case of Stranger the system will power off and in this case you have to start the program
    	from the beginning
    	*/

		if(z==3){
			UART_sendByte(READY4);
			_delay_ms(100);
			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayStringRowColumn(0,0,"Stranger!");
			timer0_init_normal_mode(T0_F_CPU_1024, 0);
			while (second != 4)
				;
			second = 0;
			LCD_sendCommand(CLEAR_COMMAND);
			LCD_displayStringRowColumn(0,0,"Please ReOpen SYS.");
			_delay_ms(10000);
			LCD_sendCommand(CLEAR_COMMAND);
			_delay_ms(100000);
		}

	}
	//sending password to the second MCU TO be stored at E2PROM
	if (j==5) {

    	UART_sendByte(R);
    	for(i=0;i<5;i++){
    		while(UART_recieveByte()!=R){};
    		UART_sendByte(new_pass[i]);

    	}
	}

}
