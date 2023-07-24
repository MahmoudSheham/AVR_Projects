/*
 * DIO.h
 *
 * Created: 11/22/2022 2:43:04 PM
 *  Author: Mahmoud
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../../Utilities/BIT_MATH.h"
#include "../../Utilities/registers.h"
#include "../../Utilities/std_types.h"

/************************************************************************/
/* DIO Driver Macros                                                    */
/************************************************************************/
#define LOW			0
#define HIGH		1

/************************************************************************/
/* DIO Driver enums                                                     */
/************************************************************************/
typedef enum EN_direction
{
	INPUT,
	OUTPUT
	}EN_direction;
	
typedef enum EN_portName
{
	PORT_A,
	PORT_B,
	PORT_C,
	PORT_D
	}EN_portName;
	
typedef enum EN_pinNumber
{
	PIN0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}EN_pinNumber;

/************************************************************************/
/* DIO Driver Functions                                                 */
/************************************************************************/
/**Intialzatin Function**/
void DIO_pinInt(EN_pinNumber pinNumber, EN_portName portName, EN_direction direction);
void DIO_portInt(EN_portName portName, EN_direction direction);

/**Write Function**/
void DIO_pinWrite(EN_pinNumber pinNumber, EN_portName portName, uint8_t value);
void DIO_portWrite(EN_portName portName, uint8_t value);

/**Read Function**/
void DIO_pinRead(EN_pinNumber pinNumber, EN_portName portName, uint8_t *value);
void DIO_portRead(EN_portName portName, uint8_t *value);

/**Togel Function**/
void DIO_pinToggle(EN_pinNumber pinNumber, EN_portName portName);
void DIO_portToggle(EN_portName portName);

#endif /* DIO_H_ */