/* 
 * ADC.c
 *
 * Created: 1/24/2023 9:59:11 AM
 *  Author: Mahmoud
 */ 
#include "ADC.h"

EN_adjust ADC_adjust= RIGHT_ADJUST;
void static (*ADCCallBackFunction)(void);

void ADC_init(EN_voltageRefrence ADC_voltageRefrence, EN_adjust ADC_adjust, EN_anlogChannelAndGainSelection channelAndGainSlection, EN_prescaler prescaler)
{
	/**ADC enable**/
	SET_BIT(ADCSRA, 7);

	switch(ADC_voltageRefrence)
	{
		case AREF:
			CLR_BIT(ADMUX,7);
			CLR_BIT(ADMUX,6);
			break;
		case AVCC:
			CLR_BIT(ADMUX,7);
			SET_BIT(ADMUX,6);			
			break;
		case INTERNAL2_56V:
			SET_BIT(ADMUX,7);
			SET_BIT(ADMUX,6);		
			break;
	}
	
	switch (ADC_adjust)
	{
		case LEFT_ADJUST:
			SET_BIT(ADMUX,5);
			ADC_adjust = LEFT_ADJUST;
			break;
		case RIGHT_ADJUST:
			ADC_adjust = RIGHT_ADJUST;
			CLR_BIT(ADMUX,5);
			break;
	}
	
	ADMUX &= 0xf0;
	ADMUX |= (channelAndGainSlection & 0x0f);  
	
	ADCSRA &= 0xf8;
	ADCSRA |= (prescaler & 0x07);  
	
}

void ADC_read(uint16_t* data, EN_anlogChannelAndGainSelection channel)
{
	*data = 0;
	uint16_t dataL = 0, dataH = 0;
		
	ADMUX &= 0xf0; 
	ADMUX |= (channel & 0x0f);
	
	SET_BIT(ADCSRA, 6);
	 
	while(GET_BIT(ADCSRA, 4) == 0);
	
	dataL = ADCL;
	dataH = ADCH;
	*data = dataL & 0xff;
	*data |= (dataH & 0xff) << 8;
	
	if (ADC_adjust == LEFT_ADJUST)
		*data = *data >> 6;
}

void ADC_controlAndStatus(EN_autoTrigger autoTrigger, EN_interruptEnable interruptEnable)
{
	if (autoTrigger == OT_ENABLE)
		SET_BIT(ADCSRA, 5);
	else
		CLR_BIT(ADCSRA, 5);
		
	if (interruptEnable == INT_ENABLE)
	{
		SET_BIT(ADCSRA, 3);
		SET_BIT(SREG, 7);	
	}
	else 
	{
		CLR_BIT(ADCSRA, 3);
		CLR_BIT(SREG, 7);
	}
	
}

void ADC_setCallback(void(*callBack)(void))
{
	ADCCallBackFunction = callBack;
}

/**ADC subroten**/
ADC(ADCvector)
{
	ADCCallBackFunction();
	return 0;
}
