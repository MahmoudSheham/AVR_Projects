/*
 * LED.c
 *
 * Created: 11/22/2022 5:45:03 PM
 *  Author: Mahmoud
 */ 
#include "LED.h"

void LED_init(EN_portName ledPort, EN_pinNumber ledPin)
{
	DIO_pinInt(ledPin, ledPort, OUTPUT);
	return;
}
void LED_off(EN_portName ledPort, EN_pinNumber ledPin)
{
	DIO_pinWrite(ledPin, ledPort, LOW);
	return;
}
void LED_on(EN_portName ledPort, EN_pinNumber ledPin)
{
	DIO_pinWrite(ledPin, ledPort, HIGH);
	return;
}
void LED_toggel(EN_portName ledPort, EN_pinNumber ledPin)
{
	DIO_pinToggle(ledPin, ledPort);
	return;
}