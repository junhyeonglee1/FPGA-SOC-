/*
 * timer.h
 *
 *  Created on: 2024. 9. 20.
 *      Author: HARMAN-12
 */

#ifndef SRC_TIMER_H_
#define SRC_TIMER_H_


#include <stdio.h>
#include "xparameters.h"
#include <stdint.h>


typedef struct{
	volatile uint32_t TCNT;
	volatile uint32_t PSR;
	volatile uint32_t TTR;
	volatile uint32_t TIE; //4�� �� 16����Ʈ
}tim_t;

#define TIM0 (tim_t *)(XPAR_TIMER2_0_S00_AXI_BASEADDR)





void Timer_SetPrescale(tim_t *tim, uint32_t prescale);
void Timer_SetTimerTop(tim_t *tim, uint32_t topcnt);
uint32_t Timer_GetPrescaler(tim_t *tim);
uint32_t Timer_GetTimerTop(tim_t *tim);
void Timer_StartIEnable(tim_t *tim);
void Timer_StopIEnable(tim_t *tim);
uint32_t Timer_GetTimerCounter(tim_t *tim);



#endif /* SRC_TIMER_H_ */
