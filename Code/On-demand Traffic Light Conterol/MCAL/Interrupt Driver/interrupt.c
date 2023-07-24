/*
 * interrupt.c
 *
 * Created: 11/24/2022 10:15:15 PM
 *  Author: Mahmoud
 */ 

#include "interrupt.h"

void static (*INT0CallBackFunction)(void);
void static (*INT1CallBackFunction)(void);
void static (*INT2CallBackFunction)(void);

void INT_init(EN_externalInterruptNumber interruptNumber, EN_externalInterruptLogic interruptLogic ,EN_externalInterruptPullUp pullUp)
{
	switch (interruptNumber)
	{
		
		case EXINT0:
			switch(interruptLogic)
			{
				case FALINGEDG:
					CLR_BIT(MCUCR, 0);
					SET_BIT(MCUCR, 1);				
					break;
				
				case RISINGEDG:
					SET_BIT(MCUCR, 0);
					SET_BIT(MCUCR, 1);				
					break;
				
				case LOWLEVEL:
					CLR_BIT(MCUCR, 0);
					CLR_BIT(MCUCR, 1);				
					break;
				
				case ANYCHANG:
					SET_BIT(MCUCR, 0);
					CLR_BIT(MCUCR, 1);				
					break;
			}
			if (pullUp == PULLUP_ON)
				SET_BIT(PORTD ,2);
			else  
			break;
		
		case EXINT1:
			switch(interruptLogic)
			{
				case FALINGEDG:
					CLR_BIT(MCUCR, 0);
					SET_BIT(MCUCR, 1);
					break;
				
				case RISINGEDG:
					SET_BIT(MCUCR, 0);
					SET_BIT(MCUCR, 1);
					break;
				
				case LOWLEVEL:
					CLR_BIT(MCUCR, 0);
					CLR_BIT(MCUCR, 1);
					break;
				
				case ANYCHANG:
					SET_BIT(MCUCR, 0);
					CLR_BIT(MCUCR, 1);
					break;
				if (pullUp == PULLUP_ON)
					SET_BIT(PORTD ,3);
			}
			break;
		
		case EXINT2:
			switch(interruptLogic)
			{
				case FALINGEDG:
					CLR_BIT(MCUCSR, 6);
					break;
					
				case RISINGEDG:
					SET_BIT(MCUCSR, 6);
					break;
				if (pullUp == PULLUP_ON)
					SET_BIT(PORTB ,2);				
				default:
					break;
			}
			break;
	}	
}
void INT_setCallBack(EN_externalInterruptNumber interruptNumber, void(*callBack)(void))
{
	switch (interruptNumber)
	{
		
		/**Set external interrupt 0 call back function**/
		case EXINT0:
			INT0CallBackFunction = callBack;
			break;
		
		/**Set external interrupt 1 call back function**/
		case EXINT1:
			INT1CallBackFunction = callBack;
			break;
		
		/**Set external interrupt 2 call back function**/
		case EXINT2:
			INT2CallBackFunction = callBack;
			break;
	}
}
void INT_start(EN_externalInterruptNumber interruptNumber)
{
	switch (interruptNumber)
	{
		
		case EXINT0:
			sei();
			SET_BIT(GICR, 6);
			break;

		case EXINT1:
			sei();
			SET_BIT(GICR, 7);
			break;

		case EXINT2:
			sei();
			SET_BIT(GICR, 5);
			break;
	}	
}
void INT_stop(EN_externalInterruptNumber interruptNumber)
{

	switch (interruptNumber)
	{
		case EXINT0:
			CLR_BIT(GICR, 6);
			break;

		case EXINT1:
			CLR_BIT(GICR, 7);
			break;

		case EXINT2:
			CLR_BIT(GICR, 5);
			break;
	}	
}

/**External interrupt 0 subroten**/
ISR(INT0)
{
	INT0CallBackFunction();
	return;
}

/**External interrupt 1 subroten**/
ISR(INT1)
{
	INT1CallBackFunction();
	return;
}

/**External interrupt 2 subroten**/
ISR(INT2)
{
	INT2CallBackFunction();
	return;
}