/*
 * button.h
 *
 * Created: 1/22/2023 9:50:23 PM
 *  Author: Mahmoud
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "../../MCAL/DIO Driver/DIO.h"
#include "../../MCAL/Interrupt Driver/interrupt.h"
#include "../../MCAL/Timer Driver/timer0.h"

typedef enum EN_buttonState
{
	HIGH_STATE,
	LOW_STATE
	}EN_buttonState;

void button_init(EN_portName bottonPort, EN_pinNumber buttonPin);

EN_buttonState buttonRead(EN_portName bottonPort, EN_pinNumber buttonPin);


#endif /* BUTTON_H_ */