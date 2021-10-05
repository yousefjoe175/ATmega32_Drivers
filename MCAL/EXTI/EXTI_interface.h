/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: EXTI          ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/


#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H
#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "EXTI_registers.h"

#define EXTI_INT0_PIN	DIO_PORTD,DIO_PIN2
#define EXTI_INT1_PIN	DIO_PORTD,DIO_PIN3
#define EXTI_INT2_PIN	DIO_PORTB,DIO_PIN2

/*	Interrupt Lines
 *	INT0
 *	INT1
 *	INT2
 */

/*	Sense Modes
 *	LOW_LEVEL	 0
 *	ON_CHANGE 	 1
 *	FALLING_EDGE 2
 *	RISING_EDGE  3
 *
 *	NOTE: for INT2 you can change only falling edge or rising edge
 */
void EXTI_voidEnableInterruptLine(u8 copy_u8Line, u8 copy_u8SenseMode, void(*ptr)(void));

void EXTI_voidDisableInterruptLine(u8 copy_u8Line);

void EXTI_voidWaitForEventSynchronous(u8 copy_u8Line, u8 copy_u8SenseMode);

void EXTI_voidSetSenseMode(u8 copy_u8Line, u8 copy_u8SenseMode);

#endif /* INTERRUPT_H_ */
