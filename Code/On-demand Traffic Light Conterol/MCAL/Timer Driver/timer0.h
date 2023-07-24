/*
 * timer0.h
 *
 * Created: 11/23/2022 6:11:44 PM
 *  Author: Mahmoud
 */ 


#ifndef TIMER0_H_
#define TIMER0_H_



#include "../../Utilities/BIT_MATH.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/std_types.h"

#define TIMER0_INT		__vector_11

typedef enum EN_timer0Mood
{
	NORMAL_MODE,
	PWMPHASECORRECT,
	CTC,
	FASTPWM
	}EN_timer0Mood; 
	
typedef enum EN_timer0CompareOutputMood
{
	NORMAL,
	TOGGEL_OC0,
	CLEAR_OC0,
	SET_OC0
	}EN_timer0CompareOutputMood;

typedef enum EN_clockSelect
{
	NO_CLOCK_SOURCE,
	NO_PRESCALER,
	PRESCALER_8,
	PRESCALER_64,
	PRESCALER_256,
	PRESCALER_1024,
	/**External clock source on T0 pin. Clock on falling edge.**/
	ECSFE,
	/**External clock source on T0 pin. Clock on rising edge.**/
	ECSRE
	}EN_clockSelect;
	
typedef enum EN_state
{
	ENABLE,
	DISABLE
}EN_state;
	
void Timer0_init(EN_timer0Mood timerMood,EN_timer0CompareOutputMood timerCompareOutputMood);
void Timer0_setCallBack(void(*callBack)(void));
void Timer0_start(EN_clockSelect clockSelect, uint8_t start, uint8_t OCRValue);
void Timer0_stop(void);
void Timer0_interruptEnable(EN_state overflowInterrupt, EN_state copareMatchInterrupt);
void Timer0_reset(uint8_t reset);
  
#endif /* TIMER0_H_ */