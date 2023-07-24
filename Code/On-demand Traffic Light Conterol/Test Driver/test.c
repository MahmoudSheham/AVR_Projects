/*
 * test.c
 *
 * Created: 1/23/2023 11:01:38 AM
 *  Author: Mahmoud
 */ 
#include "test.h"

/**------------MCAL test functions------------**/
/**DIO test functions**/
void DIOTest(void)
{
	uint8_t value = 1;
	while (1)
	{
		/**Set PIN0 &PIN1 in POTR A as an output Pins**/
		DIO_pinInt(PIN0, PORT_A, OUTPUT);
		DIO_pinInt(PIN1, PORT_A, OUTPUT);
		
		/**Set PIN0 in PORT B as an input pin**/
		DIO_pinInt(PIN0, PORT_B, INPUT);

		/**Read Function**/
		DIO_pinRead(PIN0, PORT_B, &value);
		
		//value = 1;
		/**Write Function**/
		DIO_pinWrite(PIN0, PORT_A, value);

		/**Togel Function**/
		for (uint64_t i = 0; i < 100000; i++)
		{}
		DIO_pinToggle(PIN1, PORT_A);
	}
}

/**interrupt test functions**/
void interruptTest(void)
{
	INT_init(EXINT0, FALINGEDG, PULLUP_ON);
	
	DIO_pinInt(PIN1, PORT_A, OUTPUT);
	
	INT_setCallBack(EXINT0, interruptTestCallBack);
	
	INT_start(EXINT0);
}
void interruptTestCallBack(void)
{
	
	DIO_pinToggle(PIN1, PORT_A);
}

/**Timer test functions**/
void timerTest(void)
{
	
	Timer0_init(NORMAL_MODE, NORMAL);
	
	DIO_pinInt(PIN1, PORT_A, OUTPUT);
	
	Timer0_setCallBack(timerTestCallBack);
	
	Timer0_interruptEnable(ENABLE, DISABLE);
	
	Timer0_start(PRESCALER_1024, 0, 0);
}
void timerTestCallBack(void)
{
	static uint8_t counter = 0;
	if (counter < 10)
	{
		counter++;
		return;
	}
	counter = 0;
	DIO_pinToggle(PIN1, PORT_A);
}

/**------------ECUAL test functions------------**/
/**Button and LED test functions**/
void button_LEDTest(void)
{
	
	EN_buttonState button;
	
	while(1)
	{
		
		button_init(PORT_B, PIN0);
	
		LED_init(PORT_A, PIN0);
	
		button = buttonRead(PORT_B, PIN0);
	
		if (button == LOW_STATE)
			LED_off(PORT_A, PIN0);
		else
			LED_on(PORT_A, PIN0);
	}
}