#ifndef		EXTI_REGISTERS_H
#define		EXTI_REGISTERS_H

#define EXTI_MCUCR		*((volatile u8*)(0x55))
#define EXTI_MCUCSR		*((volatile u8*)(0x54))
#define EXTI_GIFR		*((volatile u8*)(0x5A))
#define EXTI_GICR		*((volatile u8*)(0x5B))
#define EXTI_SREG	    *((volatile u8*)(0x2F))

/* MCUCR */
#define EXTI_ISC00		0
#define EXTI_ISC01		1
#define EXTI_ISC10		2
#define EXTI_ISC11		3

/* MCUCSR */
#define EXTI_ISC2		6

/* GICR */
#define EXTI_INT0		6
#define EXTI_INT1		7
#define EXTI_INT2		5

/* GIFR */
#define EXTI_INTF0		6
#define EXTI_INTF1		7
#define EXTI_INTF2		5

/* SERG */
#define EXTI_I			7


#define INT0	0
#define INT1	1
#define INT2	2

#define LOW_LEVEL		0
#define ON_CHANGE 		1
#define FALLING_EDGE	2
#define RISING_EDGE 	3

#endif