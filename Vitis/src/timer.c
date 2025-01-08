/*
 * timer.c
 *
 *  Created on: 2024. 9. 20.
 *      Author: HARMAN-12
 */

#include "timer.h"




void Timer_SetPrescale(tim_t *tim, uint32_t prescale)
{
	tim->PSR = prescale;
}

void Timer_SetTimerTop(tim_t *tim, uint32_t topcnt)
{
	tim->TTR = topcnt;
}

uint32_t Timer_GetPrescaler(tim_t *tim)
{
	return tim->PSR;
}

uint32_t Timer_GetTimerTop(tim_t *tim)
{
	return tim->TTR;
}

void Timer_StartIEnable(tim_t *tim)
{
	tim->TIE = 0x01;
}

void Timer_StopIEnable(tim_t *tim)
{
	tim->TIE = 0x00;
}

uint32_t Timer_GetTimerCounter(tim_t *tim)
{
	return tim->TCNT;
}

