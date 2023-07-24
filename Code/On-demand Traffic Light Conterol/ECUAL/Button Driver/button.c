/*
 * button.c
 *
 * Created: 1/22/2023 9:50:11 PM
 *  Author: Mahmoud
 */ 

#include "button.h"

void button_init(EN_portName bottonPort, EN_pinNumber buttonPin)
{
	
	DIO_pinInt(buttonPin, bottonPort, INPUT);	
}

EN_buttonState buttonRead(EN_portName bottonPort, EN_pinNumber buttonPin)
{
	uint8_t value = 1;
	DIO_pinRead(buttonPin, bottonPort, &value);
	
	if(value == 0)
		return LOW_STATE;
	
	return HIGH_STATE;	
}