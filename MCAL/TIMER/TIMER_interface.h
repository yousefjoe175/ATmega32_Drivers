/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: TIMER         ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/


#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#include "../LIB/STD_TYPES.h"
#include "../LIB/Bit_math.h"
#include "TIMER_register.h"

#include "DIO_INT.h"
#include "EXTI_interface.h"

#define F_CPU		8000000
#define OVF_COUNTS	256

#define OC0_PIN 	DIO_PORTB,DIO_PIN3
#define ICP_PIN		DIO_PORTD,DIO_PIN6

/* mode of timer
 * NORMAL
 * CTC
 * FAST_PWM
 * PHASE_PWM
 *
 */
#define Mode	NORMAL

/* compare match mode
 * NO_OPERATION
 * TOGGLE
 * CLEAR
 * SET
 * NON_INVERT
 * INVERT
 */
#define COMPARE_MODE NO_OPERATION

/* clock source (prescaler)
 * NO_CLOCK
 * CLOCK_1
 * CLOCK_8
 * CLOCK_64
 * CLOCK_256
 * CLOCK_1024
 * EXT_FALLING
 * EXT_RISING
 *
 */ 
#define CLOCK_SOURCE CLOCK_8
 
/* define the Clock frequency of the timer */
#if 	CLOCK_SOURCE == CLOCK_1
	#define CLOCK_FREQ 	F_CPU
#elif	CLOCK_SOURCE == CLOCK_8
	#define CLOCK_FREQ 	(F_CPU/8)
#elif	CLOCK_SOURCE == CLOCK_64
	#define CLOCK_FREQ 	(F_CPU/64)
#elif	CLOCK_SOURCE == CLOCK_256
	#define CLOCK_FREQ 	(F_CPU/256)
#elif	CLOCK_SOURCE == CLOCK_1024
	#define CLOCK_FREQ 	(F_CPU/1024)
#endif
 
typedef struct{
	u32 freq;
	u8 dutyCyle;
}ICU_calc; 

//init function
void TIMER0_voidInitialize(void);
//delay polling (Synch.)
void TIMER0_voidSetBusyWait(u32 copy_u32ticks);
//interval interrupt (Asynch.)
void TIMER0_voidSetIntervalSingleAsynch(u32 copy_u32ticks,void(*ptr)(void) );
//delay interrupt (Synch.)
void TIMER0_voidSetIntervalSingleSynch(u32 copy_u32ticks,void(*ptr)(void) );
//periodic timer
void TIMER0_voidSetIntervalPeriodic(u32 copy_u32ticks,void(*ptr)(void) );
//stop periodic timer
void TIMER0_voidStopTimer(void);
// force output compare (only affect the OC0 pin)
void TIMER0_voidForceOutputCompare(void);
//Wave Generator Using CTC Mode, pass the prescaler of the main frequency
void TIMER0_voidWaveGeneratorCTC(u8 copy_u8FreqPrescaler);
/* apply PWM generator using Normal Mode */ /* 1 -> 100 */
void TIMER0_voidPWMGeneratorNormal(u8 copy_u8DutyCycle);
/* apply PWM generator using FAST PWM Mode */
void TIMER0_voidPWMGeneratorFAST(u8 copy_u8DutyCycle);
/* apply PWM generator using PHASE PWM Mode */
void TIMER0_voidPWMGeneratorPHASE(u8 copy_u8DutyCycle);
/* Input Capture by software using Timer 0 */
ICU_calc TIMER0_ICU_calcSoftwareICU(void);
/* Input Capture Unit using Timer 1 */
ICU_calc TIMER1_ICU_calcICUDetector(void);



#endif 
