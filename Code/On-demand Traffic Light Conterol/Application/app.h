/*
 * app.h
 *
 * Created: 11/25/2022 1:59:17 PM
 *  Author: Mahmoud
 */ 


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/LED Driver/LED.h"
#include "../ECUAL/Button Driver/button.h"

typedef enum EN_trafficState
{
	RED,
	GREEN,
	YELLOW_TO_RED,
	YELLOW_TO_GREEN
	}EN_trafficState;

void appStart(void);
void TimerCallBack(void);
void INTCallBack(void);
void appInit();

#endif /* APP_H_ */