/*
 * timer0.c
 *
 * Created: 11/23/2022 6:11:25 PM
 *  Author: Mahmoud
 */ 
#include "timer0.h"

void static (*TICallBackFunction)(void);

void Timer0_init(EN_timer0Mood timerMood,EN_timer0CompareOutputMood timerCompareOutputMood)
{
	switch (timerMood)
	{
		case NORMAL_MODE:
			CLR_BIT(TCCR0, 6);
			CLR_BIT(TCCR0, 3);
			break;
		case PWMPHASECORRECT:
			SET_BIT(TCCR0, 6);
			CLR_BIT(TCCR0, 3);
			break;
		case CTC:
			CLR_BIT(TCCR0, 6);
			SET_BIT(TCCR0, 3);		
			break;
		case FASTPWM:
			SET_BIT(TCCR0, 6);
			SET_BIT(TCCR0, 3);			
			break;
	}
	
	switch (timerCompareOutputMood)
	{
		case NORMAL:
			CLR_BIT(TCCR0, 4);
			CLR_BIT(TCCR0, 5);			
			break;
		case TOGGEL_OC0:
			SET_BIT(TCCR0, 4);
			CLR_BIT(TCCR0, 5);			
			break;
		case CLEAR_OC0:
			CLR_BIT(TCCR0, 4);
			SET_BIT(TCCR0, 5);			
			break;
		case SET_OC0:
			SET_BIT(TCCR0, 4);
			SET_BIT(TCCR0, 5);			
			break; 
	}
	return;
}
void Timer0_setCallBack(void(*callBack)(void))
{
	TICallBackFunction = callBack;
	return;
}
void Timer0_start(EN_clockSelect clockSelect, uint8_t start, uint8_t OCRValue)
{
	OCR0 = OCRValue;
	TCNT0 = start;
	switch (clockSelect)
	{
		case NO_CLOCK_SOURCE:
			CLR_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
			
		case NO_PRESCALER:
			SET_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
			
		case PRESCALER_8:
			CLR_BIT(TCCR0, 0);
			SET_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
		
		case PRESCALER_64:
			SET_BIT(TCCR0, 0);
			SET_BIT(TCCR0, 1);
			CLR_BIT(TCCR0, 2);
			break;
		
		case PRESCALER_256:
			CLR_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			SET_BIT(TCCR0, 2);
			break;
		
		case PRESCALER_1024:
			SET_BIT(TCCR0, 0);
			CLR_BIT(TCCR0, 1);
			SET_BIT(TCCR0, 2);
			break;
		
		case ECSFE:
			CLR_BIT(TCCR0, 0);
			SET_BIT(TCCR0, 1);
			SET_BIT(TCCR0, 2);		
			break;
		
		case ECSRE:
			SET_BIT(TCCR0, 0);
			SET_BIT(TCCR0, 1);
			SET_BIT(TCCR0, 2);			
			break;
	}
	return;
}
void Timer0_interruptEnable(EN_state overflowInterrupt, EN_state copareMatchInterrupt)
{
	switch (overflowInterrupt)
	{
		case ENABLE:
			sei();
			SET_BIT(TIMSK, 0);
			/**Enable the global enterrupt**/
			//SET_BIT(SREG, 7);
			break;
		case DISABLE:
			CLR_BIT(TIMSK, 0);
			break;
	}
	
	switch (copareMatchInterrupt)
	{
		case ENABLE:
			/**Enable the global enterrupt**/
			//SET_BIT(SREG, 7);
			sei();
			SET_BIT(TIMSK, 1);
			break;
		case DISABLE:
			CLR_BIT(TIMSK, 1);
			break;
	}
	return;
}
void Timer0_stop(void)
{
	CLR_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 2);
	return;
}
void Timer0_reset(uint8_t reset)
{
	TCNT0 = reset;
}

ISR(TIMER0_INT)
{
	TICallBackFunction();
	return;
}