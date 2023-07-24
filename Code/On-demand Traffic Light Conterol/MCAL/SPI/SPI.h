/*
 * SPI.h
 *
 * Created: 2/22/2023 8:28:02 PM
 *  Author: Mahmoud
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdlib.h>
#include "../DIO Driver/DIO.h"
#include "../../Utilities/BIT_MATH.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/std_types.h"

typedef enum EN_SPIMode
{
	MASTERMODE,
	SLAVEMODE
	}EN_SPIMode;
	
typedef enum EN_SPIPrescaler
{
	SPI_PRESCALER_4,
	SPI_PRESCALER_16,
	SPI_PRESCALER_64,
	SPI_PRESCALER_128
	}EN_SPIPrescaler;

typedef enum EN_SPIInterrupt
{
	SPI_INT_ENABLE,
	SPI_INT_DESABLE
	}EN_SPIInterrupt;

typedef enum EN_SPIEnable
{
	SPI_ENABLE,
	SPI_DESABLE
	}EN_SPIEnable;
	
typedef enum EN_SPIDataOrder
{
	SPI_MSB_FIRST,
	SPI_LSB_FIRST
	}EN_SPIDataOrder;
	
typedef enum EN_SPIClockPolarity
{
	CLOCK_IDLE_LOW,
	CLOCK_IDLE_HIGH
	}EN_SPIClockPolarity;
	
typedef enum EN_SPICLockPhase
{
	SAMBLE_LE,
	SAMBLE_TE
	}EN_SPICLockPhase;
	
typedef enum EN_SPIDubleSpeed
{
	SPI_DSPEED_ENABLE,
	SPI_DSPEED_DESABLE
	}EN_SPIDubleSpeed;
	
typedef struct ST_SPISlave
{
	EN_portName slavePort;
	EN_pinNumber slavePin;
	}ST_SPISlave;
	
void SPI_init(EN_SPIMode mode, EN_SPIPrescaler prescaler, EN_SPIInterrupt interrupt, EN_SPIEnable SPIEnable, EN_SPIDataOrder dataOrder, EN_SPIClockPolarity clockPolarty, EN_SPICLockPhase clockPhase, EN_SPIDubleSpeed dubleSpeed);

void SPI_setSlaveSelectPins(uint16_t numberOfSlaves, ST_SPISlave *slaves);

void SPI_masterSend(uint8_t data, uint16_t slaveNumber);

void SPI_masterRecive(uint8_t *data, uint16_t slaveNumber);

void SPI_slaveSend(uint8_t data);

void SPI_slaveRecive(uint8_t *data);
		
#endif /* SPI_H_ */