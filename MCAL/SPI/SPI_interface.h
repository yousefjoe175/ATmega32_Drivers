/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: SPI           ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/

#ifndef		SPI_INTERFACE_H
#define		SPI_INTERFACE_H

#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "DIO_INT.h"
#include "SPI_registers.h"

void SPI_voidMasterInit(void);
void SPI_voidSlaveInit(void);

void SPI_voidSlaveSelect(u8 state);

u8 SPI_u8MasterTranscieve(u8 copy_u8Data);
u8 SPI_u8SlaveTranscieve(u8 copy_u8Data);



/* configurations */

/*
 * 0 or 1
 */
#define LSB_FIRST	1

/* Clock polarity and phase
 *	rising edge leading sample	 0
 *	rising edge trailing sample  1
 *	falling edge leading sample  2
 *	falling edge trailing sample 3
 */
 #define CLOCK_PLOARITY_PHASE 
 
 
/* clock rate select
 *	Fosc/4		0
 *	Fosc/16		1
 *	Fosc/64		2
 *	Fosc/128	3
 *	Fosc/2		4
 *	Fosc/8		5
 *	Fosc/32		6
 *	Fosc/64		7
 */
 #define CLOCK_RATE 
 
 
 
 
 
 
 
#endif