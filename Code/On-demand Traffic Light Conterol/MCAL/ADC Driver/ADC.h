/*
 * ADC.h
 *
 * Created: 1/24/2023 9:59:27 AM
 *  Author: Mahmoud
 */ 


#ifndef ADC_H_
#define ADC_H_

#include "../../Utilities/BIT_MATH.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/std_types.h"

/**ADC vector number**/
#define ADCvector		__vector_16

typedef enum EN_voltageRefrence
{
	AREF,
	AVCC,
	INTERNAL2_56V
	}EN_voltageRefrence;

typedef enum EN_adjust
{
	RIGHT_ADJUST,
	LEFT_ADJUST
	}EN_adjust;

typedef enum EN_anlogChannelAndGainSelection
{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,
	
	ADC0_ADC0_x10,
	ADC1_ADC0_x10,
	ADC0_ADC0_x200,
	ADC1_ADC0_x200,
	ADC2_ADC2_x10,
	ADC3_ADC2_x10,	
	ADC2_ADC2_x200,
	ADC3_ADC2_x200,
		
	ADC0_ADC1_x1,
	ADC1_ADC1_x1,
	ADC2_ADC1_x1,
	ADC3_ADC1_x1,
	ADC4_ADC1_x1,
	ADC5_ADC1_x1,
	ADC6_ADC1_x1,
	ADC7_ADC1_x1,
	
	ADC0_ADC2_x1,
	ADC1_ADC2_x1,
	ADC2_ADC2_x1,
	ADC3_ADC2_x1,
	ADC4_ADC2_x1,
	ADC5_ADC2_x1,
	
	V_BG,
	GND		
	}EN_anlogChannelAndGainSelection;
	
typedef enum EN_ADC_Enable
{
	ADC_ON,
	ADC_OFF
	}EN_ADC_Enable;	

typedef enum EN_autoTrigger
{
	OT_ENABLE,
	OT_DESABLE
	}EN_autoTrigger;

typedef enum EN_interruptEnable
{
	INT_ENABLE,
	INT_DESABLE
	}EN_interruptEnable;

typedef enum EN_prescaler
{
	PRESCALER_1,
	PRESCALER_2,
	PRESCALER_4,
	PRESCALER_8,
	PRESCALER_16,
	PRESCALER_32,
	PRESCALER_64,
	PRESCALER_128
	}EN_prescaler;

void ADC_init(EN_voltageRefrence ADC_voltageRefrence, EN_adjust ADC_adjust, EN_anlogChannelAndGainSelection channelAndGainSlection, EN_prescaler prescaler);

void ADC_read(uint16_t* data, EN_anlogChannelAndGainSelection channel);

void ADC_controlAndStatus(EN_autoTrigger autoTrigger, EN_interruptEnable interruptEnable);

void ADC_setCallback(void(*callBack)(void));
//void ADC_
#endif /* ADC_H_ */