/*
 * SPI.c
 *
 * Created: 2/22/2023 8:27:48 PM
 *  Author: Mahmoud
 */ 
#include "SPI.h"
	
uint16_t SPInumberOfSlaves;

ST_SPISlave *SPIslaves;				
								
void SPI_init(EN_SPIMode mode, EN_SPIPrescaler prescaler, EN_SPIInterrupt interrupt, EN_SPIEnable SPIEnable, EN_SPIDataOrder dataOrder, EN_SPIClockPolarity clockPolarty, EN_SPICLockPhase clockPhase, EN_SPIDubleSpeed dubleSpeed)
{
	SPCR = 0x00;
	
	/**Set the SPI inturrpt**/
	if (interrupt == SPI_INT_ENABLE)
		SET_BIT(SPCR, 7);
		
	/**Enable the SPI**/
	if(SPIEnable == SPI_ENABLE)
		SET_BIT(SPCR, 6);
	
	/**Set the SPI mode**/
	if (mode == MASTERMODE)
	{
		/**Master mode enable**/
		SET_BIT(SPCR, 4);
		
		/**Slave select pin SS**/
		//DIO_pinInt(PIN4, PORT_B, OUTPUT);
		
		/**Master output slave input pin MOSI**/
		DIO_pinInt(PIN5, PORT_B, OUTPUT);
		
		/**Master input slave output pin MISO**/
		DIO_pinInt(PIN6, PORT_B, INPUT);
		
		/**Clock pin**/
		DIO_pinInt(PIN7, PORT_B, OUTPUT);	
	}
	else
	{
		/**slave select pin SS**/
		DIO_pinInt(PIN4, PORT_B, INPUT);
		
		/**Master output slave input pin MOSI**/
		DIO_pinInt(PIN5, PORT_B, INPUT);
		
		/**Master input slave output pin MISO**/
		DIO_pinInt(PIN6, PORT_B, OUTPUT);
		
		/**Clock pin**/
		DIO_pinInt(PIN7, PORT_B, INPUT);
	}
	/**Set the SPI prescaler**/
	switch (prescaler)
	{
		case SPI_PRESCALER_4:
			CLR_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);			
			break;
		case SPI_PRESCALER_16:
			SET_BIT(SPCR, 0);
			CLR_BIT(SPCR, 1);
			break;
		case SPI_PRESCALER_64:
			CLR_BIT(SPCR, 0);	
			SET_BIT(SPCR, 1);
			break;
		case SPI_PRESCALER_128:
			SET_BIT(SPCR, 0);
			SET_BIT(SPCR, 1);
			break;
	}
	
	/**Set the data order of the SPI**/
	if(dataOrder == SPI_LSB_FIRST)
		SET_BIT(SPCR, 5);
	
	/**Set the SPI clock polarty**/	
	if(clockPolarty == CLOCK_IDLE_HIGH)
		SET_BIT(SPCR, 3);
	
	/**Set the clock phase of rhe SPI**/	
	if(clockPhase  == SAMBLE_TE)
		SET_BIT(SPCR, 2);
		
	/**Set the SPI duble speed**/
	if(dubleSpeed == SPI_DSPEED_ENABLE)
		SET_BIT(SPSR, 0);
	else 
		CLR_BIT(SPSR, 0);
}

void SPI_setSlaveSelectPins(uint16_t numberOfSlaves, ST_SPISlave *slaves)
{
	/**Set the enternal number of slaves**/
	uint16_t count = 0;
	SPInumberOfSlaves = numberOfSlaves;
	if (!SPInumberOfSlaves)
		return;
	/****/
	SPIslaves = (ST_SPISlave *)malloc(numberOfSlaves*sizeof(ST_SPISlave));
	for(count = 0; count < SPInumberOfSlaves; count++)
	{
		SPIslaves[count].slavePin = slaves[count].slavePin;
		SPIslaves[count].slavePort = slaves[count].slavePort;
		DIO_pinInt(SPIslaves[count].slavePin, SPIslaves[count].slavePort, OUTPUT);
		DIO_pinWrite(SPIslaves[count].slavePin, SPIslaves[count].slavePort, HIGH);
	}
}

void SPI_masterSend(uint8_t data, uint16_t slaveNumber)
{
	
	/**Write the data to the SPI data register**/
	SPDR = data;
	
	/**drive the SS pin to low**/
	DIO_pinWrite(SPIslaves[slaveNumber - 1].slavePin, SPIslaves[slaveNumber - 1].slavePort, LOW);
	
	/**Wait tell the transmission complete**/
	while(!GET_BIT(SPSR, 7));
	
	/**drive the SS pin to high**/
	DIO_pinWrite(SPIslaves[slaveNumber - 1].slavePin, SPIslaves[slaveNumber - 1].slavePort, HIGH);
	
	/**Flush the received data**/
	data = SPDR;	
}

void SPI_masterRecive(uint8_t *data, uint16_t slaveNumber)
{		
	/**Write  dummy data to the SPI data register**/
	SPDR = 0x00;
	
	/**drive the SS pin to low**/
	DIO_pinWrite(SPIslaves[slaveNumber - 1].slavePin, SPIslaves[slaveNumber - 1].slavePort, LOW);
		
	/**Wait tell the reception complete**/
	while(!GET_BIT(SPSR, 7));
		
	/**drive the SS pin to high**/
	DIO_pinWrite(SPIslaves[slaveNumber - 1].slavePin, SPIslaves[slaveNumber - 1].slavePort, HIGH);
		
	/**Red the received data**/
	*data = SPDR;
}

void SPI_slaveSend(uint8_t data)
{			
	/**Write the data to the SPI data register**/
	SPDR = data;
			
	/**Wait tell the transmission complete**/
	while(!GET_BIT(SPSR, 7));
			
	/**Flush the received data**/
	data = SPDR;
}

void SPI_slaveRecive(uint8_t *data)
{
	/**Write dummy data to the SPI data register**/
	SPDR = 0x00;
	
	/**Wait tell the reseptin complete**/
	while(!GET_BIT(SPSR, 7));
	
	/**Red the received data**/
	*data = SPDR;	
}
