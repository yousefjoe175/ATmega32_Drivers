/*
 * TIMER_reigster.h
 *
 * Created: 7/23/2020 7:08:39 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef TIMER_REGISTER_H_
#define TIMER_REGISTER_H_


#define  SREG  *((volatile u8*) 0x5f)	//register containing the global interrupt flag ISERG bit
#define	 TIFR  *((volatile u8*) 0x58)	//register containing the timers flags
#define  TIMSK *((volatile u8*) 0x59)	//register containing the timers interrupts enables (masks)

//TIMER0
#define  TCNT0 *((volatile u8*) 0x52)	//the timer counter
#define  TCCR0 *((volatile u8*) 0x53)	//the timer register for operation mode and prescaler 
#define  OCR0  *((volatile u8*) 0x5C)	//the register containg the compared value

//TIMER1
#define ICR1   *((volatile u16*) 0x46)
#define TCNT1  *((volatile u16*) 0x4C)
#define OCR1B  *((volatile u8*) 0x48)
#define OCR1A  *((volatile u8*) 0x4A)
#define TCCR1B *((volatile u8*) 0x4E)
#define TCCR1A *((volatile u8*) 0x4F)

//TIMER2
#define  TCNT2 *((volatile u8*) 0x44)
#define  TCCR2 *((volatile u8*) 0x45)
#define  OCR2  *((volatile u8*) 0x43)




//SREG
#define ISERG  7

//TCCR0
#define FOC0   7
#define WGM0   6
#define COM1   5 
#define COM0   4
#define WGM1   3
#define CS2	   2
#define CS1    1
#define CS0    0

//TIMSK
#define TOIE0  0
#define OCIE0  1
#define TOIE1  2
#define OCIE1B 3
#define OCIE1A 4
#define TICIE1 5
#define TOIE2  6
#define OCIE2  7

//TIFR
#define TOV0	0
#define OCF0	1
#define TOV1	2
#define OCF1B	3
#define OCF1A	4
#define ICF1	5
#define TOV2	6
#define OCF2	7

//TCCR1B
#define ICES1	6


/* MODE */
#define NORMAL		0
#define CTC			1
#define FAST_PWM	2
#define PHASE_PWM	3

/* compare match mode */
#define NO_OPERATION	0
#define TOGGLE			1
#define CLEAR			2
#define SET				3
/*for PWM */
#define NON_INVERT		2
#define INVERT			3

/* clock source */
#define NO_CLOCK	0
#define CLOCK_1		1
#define CLOCK_8		2
#define CLOCK_64	3
#define CLOCK_256	4
#define CLOCK_1024	5
#define EXT_FALLING	6
#define EXT_RISING	7



#endif 