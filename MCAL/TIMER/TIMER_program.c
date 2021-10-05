/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: TIMER         ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/

#include "TIMER_interface.h"


static volatile u16 Ton;
static volatile u16 Toff;
static volatile u8 flag;
static volatile u16	IntervalCounter = 0;
static u16 Global_u16OVFcount = 0;
static volatile u8 PWMflag;

void (*TIMER0_OverflowCallBack)(void);
void (*TIMER0_CompareMatchCallBack)(void);

void TIMER0_PWMGeneratorNormalOFCallBack(void){
	DIO_voidSetPinValue(OC0_PIN, DIO_HIGH);

}

void TIMER0_PWMGeneratorNormalOCCallBack(void){
	DIO_voidSetPinValue(OC0_PIN, DIO_LOW);

}

/*
 * 1. at first falling edge it will start the timer and set to rising edge
 * 2. at rising edge it will reset TCNT0 and set to falling edge
 * 3. at second falling it will read the value of TCNT0 in Ton and reset it and set to rising edge again
 * 4. at second rising edge it will  read the value of TCNT0 in Toff and disable the timer and the interrupt
 */
void TIMER0_voidSoftwareICUCallBack(void){
	static u8 edgeFlag;
	if(edgeFlag == 0){
		//reset TCNT0 
		TCNT0 = 0;
		//enable the timer by applying the clock source
		SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
		//set to rising edge
		EXTI_voidSetSenseMode(INT0, RISING_EDGE);
		edgeFlag = 1;
	}
	else if(edgeFlag == 1){	// first rising edge
		//reset TCNT0 
		TCNT0 = 0;
		//set to falling edge
		EXTI_voidSetSenseMode(INT0, FALLING_EDGE);
		edgeFlag = 2;
	}
	else if(edgeFlag == 2){ //second falling edge
		//read the value of the high period in Ton
		Ton = TCNT0;
		//reset TCNT0 
		TCNT0 = 0;
		//set to rising edge
		EXTI_voidSetSenseMode(INT0, RISING_EDGE);
		edgeFlag = 3;
	}
	else if(edgeFlag == 3){ // second rising edge
		//read the value of the low period in Toff
		Toff = TCNT0;
		//disable the interrupt
		EXTI_voidDisableInterruptLine(INT0);
		//disable the timer
		CLR_BIT(TCCR0,CS0);
		CLR_BIT(TCCR0,CS1);
		CLR_BIT(TCCR0,CS2);
		//set flag to 1
		flag = 1;
	}
}

//init function
void TIMER0_voidInitialize(void){
	
	#if  COMPARE_MODE == TOGGLE
		SET_VAL(TCCR0,COM0,1);
	#elif COMPARE_MODE == CLEAR	//also non-inverting
		SET_VAL(TCCR0,COM0,2);
	#elif COMPARE_MODE == SET	//also inverting
		SET_VAL(TCCR0,COM0,3);
	#endif
	//set the pin as output 
	DIO_voidSetPinDirection(OC0_PIN, DIO_OUTPUT);
}

//delay polling (Synch.)
void TIMER0_voidSetBusyWait(u32 copy_u32ticks){
	// how many overflows need to be done
	u16 Local_u16OVFcount;
	//counter to count the overflows
	u16 counter = 0;
	//Load the Counter register
	u8 Local_u8Load;
	//set the mode of timer to normal
	CLR_BIT(TCCR0,WGM0);
	CLR_BIT(TCCR0,WGM1);
	//calculate how many overflows needed
	Local_u16OVFcount = copy_u32ticks/OVF_COUNTS;
	//calculate the initial value
	Local_u8Load = 256 - copy_u32ticks%OVF_COUNTS;
	//write the initial value
	TCNT0 = Local_u8Load;
	//enable the timer by applying the clock source
	SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
	//wait for the timer to finish
	while(counter < Local_u16OVFcount){
		while(GET_BIT(TIFR,TOV0) == 0);
		SET_BIT(TIFR,TOV0);
		counter ++;
	}
	while(GET_BIT(TIFR,TOV0) == 0);
	SET_BIT(TIFR,TOV0);
	//disable the timer
	CLR_BIT(TCCR0,CS0);
	CLR_BIT(TCCR0,CS1);
	CLR_BIT(TCCR0,CS2);
}

//delay interrupt (Asynch.)
void TIMER0_voidSetIntervalSingleAsynch(u32 copy_u32ticks,void(*ptr)(void) ){
	PWMflag = 0;
	TIMER0_OverflowCallBack = ptr;
	//Load the Counter register
	u8 Local_u8Load;
	
	//set the mode of timer to normal
	CLR_BIT(TCCR0,WGM0);
	CLR_BIT(TCCR0,WGM1);
	
	//calculate how many overflows needed
	Global_u16OVFcount = copy_u32ticks/OVF_COUNTS;

	//calculate the initial value
	Local_u8Load = 256 - copy_u32ticks%OVF_COUNTS;
	//write the initial value
	TCNT0 = Local_u8Load;
	
	//Enable the interrupt for overflow
	SET_BIT(TIMSK,TOIE0);
	SET_BIT(SREG,ISERG);
	//enable the timer by applying the clock source
	SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
	
}
void TIMER0_voidSetIntervalPeriodic(u32 copy_u32ticks,void(*ptr)(void) ){
	
	
	
}
//delay interrupt (Asynch.)
void TIMER0_voidSetIntervalSingleSynch(u32 copy_u32ticks,void(*ptr)(void) ){
	PWMflag = 0;
	TIMER0_OverflowCallBack = ptr;
	// how many overflows need to be done
	u16 Local_u16OVFcount;
	//counter to count the overflows
	u16 counter = 0;
	//Load the Counter register
	u8 Local_u8Load;

	//set the mode of timer to normal
	CLR_BIT(TCCR0,WGM0);
	CLR_BIT(TCCR0,WGM1);

	//calculate how many overflows needed
	Local_u16OVFcount = copy_u32ticks/OVF_COUNTS;
	//calculate the initial value
	Local_u8Load = 256 - copy_u32ticks%OVF_COUNTS;
	//write the initial value
	TCNT0 = Local_u8Load;

	//enable the timer by applying the clock source
	SET_VAL(TCCR0,CS0,CLOCK_SOURCE);

	//wait for the timer to finish
	while(counter < Local_u16OVFcount){
		while(GET_BIT(TIFR,TOV0) == 0);
		SET_BIT(TIFR,TOV0);
		counter ++;
	}

	//Enable the interrupt for overflow
	SET_BIT(TIMSK,TOIE0);
	SET_BIT(SREG,ISERG);
	//wait until flag is set and interrupt is fired
	while(GET_BIT(TIFR,TOV0) == 0);
}


// force output compare (only affect the OC0 pin)
void TIMER0_voidForceOutputCompare(void){
	SET_BIT(TCCR0, FOC0);
}

//Wave Generator Using CTC Mode, pass the prescaler of the main frequency
void TIMER0_voidWaveGeneratorCTC(u8 copy_u8FreqPrescaler){
	//set mode to CTC
	CLR_BIT(TCCR0,WGM0);
	SET_BIT(TCCR0,WGM1);
	//set the OC0 mode as Toggle
	SET_VAL(TCCR0,COM0,1);
	OCR0 = copy_u8FreqPrescaler - 1;
	//enable the timer by applying the clock source
	SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
}

/* 1 -> 100 */
/* apply PWM generator using Normal Mode */
void TIMER0_voidPWMGeneratorNormal(u8 copy_u8DutyCycle){
	PWMflag = 1;
	if(copy_u8DutyCycle > 0 && copy_u8DutyCycle < 101){
		//set mode to NORMAL
		CLR_BIT(TCCR0,WGM0);
		CLR_BIT(TCCR0,WGM1);
		//set compare mode to no operation
		CLR_BIT(TCCR0,COM0);
		CLR_BIT(TCCR0,COM1);
		//enable both interrupt and general interrupt
		SET_BIT(TIMSK,OCIE0);
		SET_BIT(TIMSK,TOIE0);
		SET_BIT(SREG,ISERG);
		//set the callbacks
		TIMER0_OverflowCallBack     = TIMER0_PWMGeneratorNormalOFCallBack;
		TIMER0_CompareMatchCallBack = TIMER0_PWMGeneratorNormalOCCallBack;
		//set the value of OCR0
		OCR0 = (copy_u8DutyCycle * 256)/100;
		//enable the timer by applying the clock source
		SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
	}
}

void TIMER0_voidPWMGeneratorFAST(u8 copy_u8DutyCycle){
	if(copy_u8DutyCycle > 0 && copy_u8DutyCycle < 101){
		//set mode to FAST PWM
		SET_BIT(TCCR0,WGM0);
		SET_BIT(TCCR0,WGM1);
		//set compare mode to clear on compare
		CLR_BIT(TCCR0,COM0);
		SET_BIT(TCCR0,COM1);
		//set the value of OCR0
		OCR0 = (copy_u8DutyCycle * 256)/100;
		//enable the timer by applying the clock source
		SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
	} 
}

void TIMER0_voidPWMGeneratorPHASE(u8 copy_u8DutyCycle){
	if(copy_u8DutyCycle > 0 && copy_u8DutyCycle < 101){
		//set mode to PHASE PWM
		SET_BIT(TCCR0,WGM0);
		CLR_BIT(TCCR0,WGM1);
		//set compare mode to clear on compare
		CLR_BIT(TCCR0,COM0);
		SET_BIT(TCCR0,COM1);
		//set the value of OCR0
		OCR0 = (copy_u8DutyCycle * 256)/100;
		//enable the timer by applying the clock source
		SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
	} 
}

//stop timer
void TIMER0_voidStopTimer(void){
	//disable the timer
	CLR_BIT(TCCR0,CS0);
	CLR_BIT(TCCR0,CS1);
	CLR_BIT(TCCR0,CS2);
}

ICU_calc TIMER0_ICU_calcSoftwareICU(void){
	ICU_calc Local_ICUcalc;
	//reset TCNT0 
	TCNT0 = 0;
	//enable the timer by applying the clock source
	SET_VAL(TCCR0,CS0,CLOCK_SOURCE);
	//enable the external interrupt
	EXTI_voidEnableInterruptLine(INT0, FALLING_EDGE, TIMER0_voidSoftwareICUCallBack);
	//wait for ICU to finish
	while(flag == 0);
	Local_ICUcalc.freq = CLOCK_FREQ/(Ton + Toff);
	Local_ICUcalc.dutyCyle = (Ton * 100)/(Ton +Toff);
	return  Local_ICUcalc;
}

ICU_calc TIMER1_ICU_calcICUDetector(void){
	ICU_calc Local_ICUcalc;
	//set the trigger to falling edge 
	CLR_BIT(TCCR1B, ICES1);
	//wait for the first falling edge
	while(GET_BIT(TIFR,ICF1) == 0);
	//reset TCNT0 
	TCNT0 = 0;
	//enable the timer by applying the clock source
	SET_VAL(TCCR1B,CS0,CLOCK_SOURCE);
	//set to rising edge
	SET_BIT(TCCR1B, ICES1);
	//wait for the first rising edge
	while(GET_BIT(TIFR,ICF1) == 0);
	//reset TCNT0 
	TCNT0 = 0;
	//set the trigger to falling edge 
	CLR_BIT(TCCR1B, ICES1);
	//wait for the second falling edge 
	while(GET_BIT(TIFR,ICF1) == 0);
	//read the value of the high period in Ton
	Ton = ICR1;
	//reset TCNT0 
	TCNT0 = 0;
	//set to rising edge
	SET_BIT(TCCR1B, ICES1);
	//wait for the second rising edge 
	while(GET_BIT(TIFR,ICF1) == 0);
	//read the value of the low period in Toff
	Toff = ICR1;
	//disable the timer
	CLR_BIT(TCCR1B,CS0);
	CLR_BIT(TCCR1B,CS1);
	CLR_BIT(TCCR1B,CS2);
	
	/* start the calculations */
	Local_ICUcalc.freq = CLOCK_FREQ/(Ton + Toff);
	Local_ICUcalc.dutyCyle = (Ton * 100)/(Ton +Toff);
	return  Local_ICUcalc;
}

/* OVERFLOW Interrupt */
void __vector_11(void)	__attribute__((signal));	
void __vector_11(void){
	if(IntervalCounter < Global_u16OVFcount){
		SET_BIT(TIFR,TOV0);
		IntervalCounter++;
		return;
	}
	if(PWMflag == 0){
		SET_BIT(TIFR,TOV0);
		IntervalCounter = 0;
		Global_u16OVFcount = 0;
		//disable the interrupt
		CLR_BIT(TIMSK,TOIE0);
		CLR_BIT(SREG,ISERG);
		//disable the timer
		CLR_BIT(TCCR0,CS0);
		CLR_BIT(TCCR0,CS1);
		CLR_BIT(TCCR0,CS2);
	}
	TIMER0_OverflowCallBack();
}

/* compare match */
void __vector_10(void)	__attribute__((signal));	
void __vector_10(void){
	SET_BIT(TIFR,OCF0);
	TIMER0_CompareMatchCallBack();

}
