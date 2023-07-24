/*
 * test.h
 *
 * Created: 1/23/2023 11:01:53 AM
 *  Author: Mahmoud
 */ 


#ifndef TEST_H_
#define TEST_H_

#include "../Application/app.h"

/************************************************************************/
/*				DIO test functions                                      */
/************************************************************************/
void DIOTest(void);

/************************************************************************/
/*				Interrupt test functions                                */
/************************************************************************/
void interruptTest();
void interruptTestCallBack(void);

/************************************************************************/
/*				Timer test functions                                    */
/************************************************************************/
void timerTest(void);
void timerTestCallBack(void);

/************************************************************************/
/*				Button and LED test functions                           */
/************************************************************************/
void button_LEDTest(void);
#endif /* TEST_H_ */