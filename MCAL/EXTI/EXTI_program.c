/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: EXTI          ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/

#include "EXTI_interface.h" 

void (*EXTI_CallBack0)(void);
void (*EXTI_CallBack1)(void);
void (*EXTI_CallBack2)(void);

void EXTI_voidEnableInterruptLine(u8 copy_u8Line, u8 copy_u8SenseMode, void(*ptr)(void)){
	switch(copy_u8Line){
		case INT0:
			/*set the sense mode falling edge, rising edge, on change, low level */
			SET_VAL(EXTI_MCUCR, EXTI_ISC00, copy_u8SenseMode);
			/* enable the interrupt line */
			SET_BIT(EXTI_GICR, EXTI_INT0);
			/* assign the callback */
			EXTI_CallBack0 = ptr;
			break;
		case INT1:
			/*set the sense mode falling edge, rising edge, on change, low level */
			SET_VAL(EXTI_MCUCR, EXTI_ISC10, copy_u8SenseMode);
			/* enable the interrupt line */
			SET_BIT(EXTI_GICR, EXTI_INT1);
			/* assign the callback */
			EXTI_CallBack1 = ptr;
			break;
		case INT2:
			/* sense INT2 has only rising or falling edge so we make if statement to check */
			if(copy_u8SenseMode == FALLING_EDGE){
				CLR_BIT(EXTI_MCUCSR, EXTI_ISC2);
			}else if(copy_u8SenseMode == RISING_EDGE){
				SET_BIT(EXTI_MCUCSR, EXTI_ISC2);
			}
			/* enable the interrupt line */
			SET_BIT(EXTI_GICR, EXTI_INT2);
			/* assign the callback */
			EXTI_CallBack2 = ptr;
			break;
		default:
			//error
			break;
	}
	//enable the globale interrupt
	SET_BIT(EXTI_SREG, EXTI_I);
}

void EXTI_voidDisableInterruptLine(u8 copy_u8Line){
	switch(copy_u8Line){
		case INT0:
			CLR_BIT(EXTI_GICR, EXTI_INT0);
			break;
		case INT1:
			CLR_BIT(EXTI_GICR, EXTI_INT1);
			break;
		case INT2:
			CLR_BIT(EXTI_GICR, EXTI_INT2);
			break;
		default:
			//error
			break;
	}
}

void EXTI_voidWaitForEventSynchronous(u8 copy_u8Line, u8 copy_u8SenseMode){
	/* just hold the system (delay) until certain event happens*/
	switch(copy_u8Line){
		case INT0:
			/*set the sense mode falling edge, rising edge, on change, low level */
			SET_VAL(EXTI_MCUCR, EXTI_ISC00, copy_u8SenseMode);
			/*wait until event occurs */
			while(!GET_BIT(EXTI_GIFR, EXTI_INTF0));
			/* clear the flag */
			SET_BIT(EXTI_GIFR, EXTI_INTF0);
			break;
		case INT1:
			/*set the sense mode falling edge, rising edge, on change, low level */
			SET_VAL(EXTI_MCUCR, EXTI_ISC10, copy_u8SenseMode);
			/*wait until event occurs */
			while(!GET_BIT(EXTI_GIFR, EXTI_INTF1));
			/* clear the flag */
			SET_BIT(EXTI_GIFR, EXTI_INTF1);
			break;
		case INT2:
			/* sense INT2 has only rising or falling edge so we make if statement to check */
			if(copy_u8SenseMode == FALLING_EDGE){
				CLR_BIT(EXTI_MCUCSR, EXTI_ISC2);
			}else if(copy_u8SenseMode == RISING_EDGE){
				SET_BIT(EXTI_MCUCSR, EXTI_ISC2);
			}
			/*wait until event occurs */
			while(!GET_BIT(EXTI_GIFR, EXTI_INTF2));
			/* clear the flag */
			SET_BIT(EXTI_GIFR, EXTI_INTF1);
			break;
		default:
		//error
			break;
	}
}

void EXTI_voidSetSenseMode(u8 copy_u8Line, u8 copy_u8SenseMode){
	switch(copy_u8Line){
			case INT0:
				/*set the sense mode falling edge, rising edge, on change, low level */
				SET_VAL(EXTI_MCUCR, EXTI_ISC00, copy_u8SenseMode);
				break;
			case INT1:
				/*set the sense mode falling edge, rising edge, on change, low level */
				SET_VAL(EXTI_MCUCR, EXTI_ISC10, copy_u8SenseMode);
				break;
			case INT2:
				/* sense INT2 has only rising or falling edge so we make if statement to check */
				if(copy_u8SenseMode == FALLING_EDGE){
					CLR_BIT(EXTI_MCUCSR, EXTI_ISC2);
				}else if(copy_u8SenseMode == RISING_EDGE){
					SET_BIT(EXTI_MCUCSR, EXTI_ISC2);
				}
				break;
			default:
			//error
				break;
		}
}


void __vector_1(void) __attribute__((signal));
void __vector_1(void){
	EXTI_CallBack0();
	SET_BIT(EXTI_GIFR, EXTI_INTF0);
}

void __vector_2(void) __attribute__((signal));

void __vector_2(void){
	EXTI_CallBack1();
	SET_BIT(EXTI_GIFR, EXTI_INTF1);
}

void __vector_3(void) __attribute__((signal));
void __vector_3(void){
	EXTI_CallBack2();
	SET_BIT(EXTI_GIFR, EXTI_INTF2);
}

