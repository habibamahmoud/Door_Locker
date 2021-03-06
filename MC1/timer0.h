/*
 * File Name: Timer0.h
 * Module: Timer
 * Description: Header file for timer
 * Author: Habiba Mahmoud
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include "common_macros.h"
#include "std_types.h"
#include "micro_config.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define MODE NORMAL
typedef enum{
	T0_NO_CLOCK, T0_F_CPU_, T0_F_CPU_8, T0_F_CPU_64, T0_F_CPU_256, T0_F_CPU_1024
}TIMER0_Prescaler;

typedef enum{
	T0_FALLING = 6, T0_RISING = 7
}TIMER0_Edge;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void timer0_init_normal_mode(uint8 , uint8 );
void timer0_init_compare_mode(uint8 , uint8 , uint8 );
void timer0_deinit(void);


#endif /* TIMER0_H_ */
