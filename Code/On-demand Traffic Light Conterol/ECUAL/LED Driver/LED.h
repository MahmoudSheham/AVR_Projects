/*
 * LED.h
 *
 * Created: 11/22/2022 5:44:51 PM
 *  Author: Mahmoud
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO Driver/DIO.h"
#include "../../MCAL/Interrupt Driver/interrupt.h"
#include "../../MCAL/Timer Driver/timer0.h"

void LED_init(EN_portName ledPort, EN_pinNumber ledPin);
void LED_off(EN_portName ledPort, EN_pinNumber ledPin);
void LED_on(EN_portName ledPort, EN_pinNumber ledPin);
void LED_toggel(EN_portName ledPort, EN_pinNumber ledPin);

#endif /* LED_H_ */