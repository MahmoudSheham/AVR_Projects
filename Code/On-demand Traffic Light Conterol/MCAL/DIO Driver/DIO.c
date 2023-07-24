/*
 * DIO.c
 *
 * Created: 11/22/2022 2:42:44 PM
 *  Author: Mahmoud
 */ 

#include "DIO.h"

/**Intialzatin Function**/
void DIO_pinInt(EN_pinNumber pinNumber, EN_portName portName, EN_direction direction)
{
	switch(portName)
	{
		/**Set Port A Direction**/
		case PORT_A:
			if(direction == OUTPUT)
			{
				SET_BIT(DDRA, pinNumber);
			}
			else if (direction == INPUT)
			{
				CLR_BIT(DDRA, pinNumber);
			} 
			else
			{
				/**Error**/
			}
			break;
		/**Set Port B direction**/
		case PORT_B:
			if(direction == OUTPUT)
			{
				SET_BIT(DDRB, pinNumber);
			}
			else if (direction == INPUT)
			{
				CLR_BIT(DDRB, pinNumber);
			}
			else
			{
				/**Error**/
			}
			break;
		/**Set Port C direction**/
		case PORT_C:
			if(direction == OUTPUT)
			{
				SET_BIT(DDRC, pinNumber);
			}
			else if (direction == INPUT)
			{
				CLR_BIT(DDRC, pinNumber);
			}			
			else
			{
				/**Error**/
			}
			break;
		/**Set Port D direction**/
		case PORT_D:
			if(direction == OUTPUT)
			{
				SET_BIT(DDRD, pinNumber);
			}
			else if (direction == INPUT)
			{
				CLR_BIT(DDRD, pinNumber);
			}			
			else
			{
				/**Error**/
			}
		break;
		default:
			/**Error**/
			break;
	}
	
	return;
}
void DIO_portInt(EN_portName portName, EN_direction direction)
{
	switch (portName)
	{
		/**Set the direction of port A**/
		case PORT_A:
			if (direction == OUTPUT)
			{
				DDRA = 0xFF;
			}
			else if (direction == INPUT)
			{
				DDRA = 0x00;
			} 
			else
			{
				/**Error**/
			}
			break;
		/**Set the direction of port B**/
		case PORT_B:
			if (direction == OUTPUT)
			{
				DDRB = 0xFF;
			}
			else if (direction == INPUT)
			{
				DDRB = 0x00;
			}
			else
			{
				/**Error**/
			}
			break;
		/**Set the direction of port C**/
		case PORT_C:
			if (direction == OUTPUT)
			{
				DDRC = 0xFF;
			}
			else if (direction == INPUT)
			{
				DDRC = 0x00;
			}
			else
			{
				/**Error**/
			}
			break;
		/**Set the direction of port D**/				
		case PORT_D:
			if (direction == OUTPUT)
			{
				DDRD = 0xFF;
			}
			else if (direction == INPUT)
			{
				DDRD = 0x00;
			}
			else
			{
				/**Error**/
			}
			break;
	}
	return;
}

/**Write Function**/
void DIO_pinWrite(EN_pinNumber pinNumber, EN_portName portName, uint8_t value)
{
	switch(portName)
	{
		/**Set Port A Value**/
		case PORT_A:
			if(value == HIGH)
			{
				SET_BIT(PORTA, pinNumber);
			}
			else if (value == LOW)
			{
				CLR_BIT(PORTA, pinNumber);
			}
			else
			{
				/**Error**/
			}
			break;
		/**Set Port B Value**/
		case PORT_B:
			if(value == HIGH)
			{
				SET_BIT(PORTB, pinNumber);
			}
			else if (value == LOW)
			{
				CLR_BIT(PORTB, pinNumber);
			}
			else
			{
				/**Error**/
			}
			break;
		/**Set Port C Value**/
		case PORT_C:
						if(value == HIGH)
			{
				SET_BIT(PORTC, pinNumber);
			}
			else if (value == LOW)
			{
				CLR_BIT(PORTC, pinNumber);
			}
			else
			{
				/**Error**/
			}
			break;
		/**Set Port D Value**/
		case PORT_D:
			if(value == HIGH)
			{
				SET_BIT(PORTD, pinNumber);
			}
			else if (value == LOW)
			{
				CLR_BIT(PORTD, pinNumber);
			}
			else
			{
				/**Error**/
			}
			break;
		default:
		/**Error**/
		break;
	}
	
	return;
}
void DIO_portWrite(EN_portName portName, uint8_t value)
{
	switch (portName)
	{
		case PORT_A:
			PORTA = value; 		
			break;
		case PORT_B:
			PORTB = value;
			break;
		case PORT_C:
			PORTC = value;
			break;
		case PORT_D:
			PORTD = value;
			break;
		default:
			break;
	}
	return;
}

/**Read Function**/
void DIO_pinRead(EN_pinNumber pinNumber, EN_portName portName, uint8_t *value)
{
	//uint8_t value_temp;
	
	switch (portName)
	{
		case PORT_A:
			*value = GET_BIT(PINA, pinNumber);
			break;
		case PORT_B:
			*value = GET_BIT(PINB, pinNumber);
			break;
		case PORT_C:
			*value = GET_BIT(PINC, pinNumber);
			break;
		case PORT_D:
			*value = GET_BIT(PIND, pinNumber);
			break;
		default:
			break;
	}

	return;
}
void DIO_portRead(EN_portName portName, uint8_t *value)
{

	switch (portName)
	{
	case PORT_A:
		*value = PINA;
		break;
	case PORT_B:
		*value = PINB;
		break;
	case PORT_C:
		*value = PINC;
		break;
	case PORT_D:
		*value = PIND;
		break;
	default:
		break;
	}
	return;
}

/**Togel Function**/
void DIO_pinToggle(EN_pinNumber pinNumber, EN_portName portName)
{
	switch (portName)
	{
		case PORT_A:
			TOG_BIT(PORTA, pinNumber);  
			break;
		case PORT_B:
			TOG_BIT(PORTB, pinNumber);
			break;
		case PORT_C:
			TOG_BIT(PORTC, pinNumber);
			break;
		case PORT_D:
			TOG_BIT(PORTD, pinNumber);
			break;
		default:
			break; 
	}
	return;
}
void DIO_portToggle(EN_portName portName)
{
	switch (portName)
	{
		case PORT_A:
			PORTA ^= 0xFF;
			break;
		case PORT_B:
			PORTB ^= 0xFF;
			break;
		case PORT_C:
			PORTC ^= 0xFF;
			break;
		case PORT_D:
			PORTD ^= 0xFF;
			break;
		default:
			break;
	}	
	return;
}
