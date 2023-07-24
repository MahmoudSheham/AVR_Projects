/*
 * app.c
 *
 * Created: 11/25/2022 1:59:27 PM
 *  Author: Mahmoud
 */ 

#include "app.h"

EN_trafficState carLED, pedestriansLED;

const uint64_t crystalFreq = 16000000;
const uint64_t prescaler = 1024;
const uint64_t timerOCR = 0;

uint8_t limetOfTOV = 3 ,LimetOfSecounCounter = 5; 


uint8_t secounCounter = 0, numberOfTOV = 0;

void appStart(void)
{
	appInit();	
	carLED = YELLOW_TO_GREEN;
	
	pedestriansLED = YELLOW_TO_RED;
	
	/**initiate port B pins 0, 1 and 2 for cars LED**/
	/**Green LED**/
	LED_init(PORT_A, PIN0);
	LED_off(PORT_A, PIN0);
	
	/**Yellow LED**/
	LED_init(PORT_A, PIN1);
	LED_on(PORT_A, PIN1);
	
	/**Red LED**/
	LED_init(PORT_A, PIN2);
	LED_off(PORT_A, PIN2);
	
	/**initiate port B pins 0, 1 and 2 for pedestrians LEDs**/
	/**Green LED**/
	LED_init(PORT_B, PIN0);
	LED_off(PORT_B, PIN0);	
	
	/**Yellow LED**/
	LED_init(PORT_B, PIN1);
	LED_on(PORT_B, PIN1);	
	
	/**Red LED**/
	LED_init(PORT_B, PIN2);
	LED_off(PORT_B, PIN2);		
	
	/**initiate the external interrupt 0**/
	INT_init(EXINT0, RISINGEDG ,PULLUP_ON);
	/**Set interrup call back function**/
	INT_setCallBack(EXINT0, INTCallBack);
	/**start interrupt 0**/
	INT_start(EXINT0);
	
	/**initiate Timer 0 in the normal mode**/
	/****/
	Timer0_init(NORMAL_MODE, NORMAL);
	Timer0_setCallBack(TimerCallBack);
	Timer0_interruptEnable(ENABLE, DISABLE);
	Timer0_start( PRESCALER_8, 0, 0);

}

void appInit()
{
	limetOfTOV = (uint8_t) (crystalFreq / (prescaler*(256 - timerOCR)*2)),
	LimetOfSecounCounter = LimetOfSecounCounter * 2;
}

void TimerCallBack(void)
{

	if (numberOfTOV < limetOfTOV )
	{
		numberOfTOV ++;
		return;
	}
	numberOfTOV = 0;
	if (secounCounter < LimetOfSecounCounter)
	{
		secounCounter++;
		if (pedestriansLED == YELLOW_TO_GREEN || carLED == YELLOW_TO_GREEN)
		{
			LED_toggel(PORT_A, PIN1);
			LED_toggel(PORT_B, PIN1);
		}	
	}
	else 
	{
		secounCounter = 0;
		switch(pedestriansLED)
		{
			case GREEN:
				pedestriansLED = YELLOW_TO_RED;
				carLED = YELLOW_TO_GREEN;
				
				/**turn off green LED for pedestrians**/
				LED_off(PORT_B, PIN0);
				
				/**turn off red LED for cars**/
				LED_off(PORT_A, PIN2);
				
				/**turn on the yellow LEDs**/
				LED_on(PORT_A, PIN1);
				LED_on(PORT_B, PIN1);
				break;

			case RED:
				pedestriansLED = YELLOW_TO_GREEN;
				carLED = YELLOW_TO_RED;
				
				/**turn off red LED for pedestrians**/
				LED_off(PORT_B, PIN2);
				
				/**turn off green LED for cars**/
				LED_off(PORT_A, PIN0);
				
				/**turn on the yellow LEDs**/
				LED_on(PORT_A, PIN1);
				LED_on(PORT_B, PIN1);
				break;

			case YELLOW_TO_GREEN:
				pedestriansLED = GREEN;
				carLED = RED;
				
				/**turn off yellow LED for pedestrians**/
				LED_off(PORT_B, PIN1);
				
				/**turn off yellow for cars**/
				LED_off(PORT_A, PIN1);
				
				/**turn on the red LED for cars**/
				LED_on(PORT_A, PIN2);
				
				/**turn on the green LED for pedestrians**/
				LED_on(PORT_B, PIN0);			
			
				break;
			
			case YELLOW_TO_RED:
				pedestriansLED = RED;
				carLED = GREEN;
				
				/**turn off yellow LED for pedestrians**/
				LED_off(PORT_B, PIN1);
				
				/**turn off yellow LED for cars**/
				LED_off(PORT_A, PIN1);
				
				/**turn on the green LED for cars**/
				LED_on(PORT_A, PIN0);
				
				/**turn on the red LED for pedestrians**/
				LED_on(PORT_B, PIN2);
				
				break;		
		}
	}
	
}
void INTCallBack(void)
{
	switch (carLED)
	{
		case RED:
			secounCounter = 0;
			numberOfTOV = 0;
			Timer0_reset(0);
			break;
		case  GREEN:
			secounCounter = 0;
			numberOfTOV = 0;
			Timer0_reset(0);	
					
			pedestriansLED = YELLOW_TO_GREEN;
			carLED = YELLOW_TO_RED;
				
			/**turn off red LED for pedestrians**/
			LED_off(PORT_B, PIN2);
				
			/**turn off green LED for cars**/
			LED_off(PORT_A, PIN0);
				
			/**turn on the yellow LEDs**/
			LED_on(PORT_A, PIN1);
			LED_on(PORT_B, PIN1);
			break;
		case YELLOW_TO_RED:
			secounCounter = 0;
			numberOfTOV = 0;
			Timer0_reset(0);
			break;
		case YELLOW_TO_GREEN:					
			secounCounter = 0;
			numberOfTOV = 0;
			Timer0_reset(0);
			
			pedestriansLED = YELLOW_TO_GREEN;
			carLED = YELLOW_TO_RED;
			
			/**turn off red LED for pedestrians**/
			LED_off(PORT_B, PIN2);
			
			/**turn off green LED for cars**/
			LED_off(PORT_A, PIN0);
			
			/**turn on the yellow LEDs**/
			LED_on(PORT_A, PIN1);
			LED_on(PORT_B, PIN1);
			break;
	}
}