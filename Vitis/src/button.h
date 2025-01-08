/*
 * button.h
 *
 *  Created on: 2024. 9. 9.
 *      Author: HARMAN-18
 */

#ifndef SRC_DRIVER_BUTTON_BUTTON_H_
#define SRC_DRIVER_BUTTON_BUTTON_H_

#include "sleep.h"

typedef enum { RELEASED = 0, PUSHED, ACT_NO, ACT_RELEASED, ACT_PUSHED,} btnState;

typedef struct{
	uint32_t *gpi;
	int pin;
	int *prevState;
}button_t;

void initButtonState(button_t *button, uint32_t *gpi, int pin);
btnState getButtonState(button_t *button);

#endif /* SRC_DRIVER_BUTTON_BUTTON_H_ */
