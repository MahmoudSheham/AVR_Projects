/*
 * interrupt.h
 *
 * Created: 11/24/2022 10:15:29 PM
 *  Author: Mahmoud
 */ 

#include "../../Utilities/BIT_MATH.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/std_types.h"

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/**External interrupt 0 vector number**/
#define INT0		__vector_1

/**External interrupt 2 vector number**/
#define INT1		__vector_2

/**External interrupt 2 vector number**/
#define INT2		__vector_3

typedef enum EN_externalInterruptNumber
{
	EXINT0,
	EXINT1,
	EXINT2
	}EN_externalInterruptNumber;

typedef enum EN_externalInterruptLogic
{
	FALINGEDG,
	RISINGEDG,
	LOWLEVEL,
	ANYCHANG	
	}EN_externalInterruptLogic;
	
typedef enum EN_externalInterruptPullUp
{
	PULLUP_ON,
	PULLUP_OFF
}EN_externalInterruptPullUp;
	
void INT_init(EN_externalInterruptNumber interruptNumber, EN_externalInterruptLogic interruptLogic, EN_externalInterruptPullUp pullUp);
void INT_setCallBack(EN_externalInterruptNumber interruptNumber, void(*callBack)(void));
void INT_start(EN_externalInterruptNumber interruptNumber);
void INT_stop(EN_externalInterruptNumber interruptNumber);
#endif /* INTERRUPT_H_ */