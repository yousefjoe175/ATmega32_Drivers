/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: TWI           ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/


#ifndef 	TWI_REGISTERS_H_
#define 	TWI_REGISTERS_H_


#define TWCR	*((volatile u8*)(0x56))
#define TWDR	*((volatile u8*)(0x23))
#define TWAR	*((volatile u8*)(0x22))
#define TWSR	*((volatile u8*)(0x21))
#define TWBR	*((volatile u8*)(0x20))

/* TWCR */
#define TWIE	0	/*TWI interrupt enable */
#define TWEN	2	/*TWI enable */
#define TWWC	3	/*TWI write collision */
#define TWSTO	4	/*TWI Stop generator cleared automatically*/
#define TWSTA	5	/*TWI Start generator (needs to be cleared after INT*/
#define TWEA	6	/*TWI Acknowledge enable */
#define TWINT	7	/*TWI interrupt flag */


/* TWSR */
#define TWPS0	0
#define TWPS1	1

/*TWAR*/
#define TWGCE	0

#endif