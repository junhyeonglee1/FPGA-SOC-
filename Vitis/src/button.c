#include "button.h"


void initButtonState(button_t *button, uint32_t *gpi, int pin)
{
	button->gpi = gpi;
	button->pin = pin;
	button->prevState = RELEASED;
}


btnState getButtonState(button_t *button)
{

	int currState = (*button->gpi & (1<<button->pin));

	if((currState != RELEASED) && (*button->prevState == RELEASED))
	{
		*button->prevState = PUSHED;
		usleep(10000); // 10ms
		return ACT_PUSHED;
	}
	else if((currState == RELEASED) && (*button->prevState != RELEASED))
	{
		*button->prevState = RELEASED;
		usleep(10000); // 10ms
		return ACT_RELEASED;
	}
	return ACT_NO;
}
