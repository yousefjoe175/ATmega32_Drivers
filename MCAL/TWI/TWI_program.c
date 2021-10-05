/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: TWI           ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/


#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "TWI_registers.h"
#include "TWI_private.h"
#include "TWI_interface.h"


void TWI_voidInitMaster(void){
	/*set the acknowledge enable */
	SET_BIT(TWCR, TWEA);
	
	/*set the bitrate to 400 Kbps*/	/*	SCL frequency = CPU Clock frequency/(16 + 2*TWBR* 4^TWPS) */
	TWBR = 2;
	
	/*clearing the prescaler*/
	CLR_BIT(TWSR, TWPS0);
	CLR_BIT(TWSR, TWPS1);
	
	/*enable the TWI module */
	SET_BIT(TWCR, TWEN);
}

void TWI_voidInitSlave(u8 Copy_u8Address){
	/* set the acknowledge enable */
	SET_BIT(TWCR, TWEA);
	
	/*set the slave address shifted out of TWGCE bit*/
	TWAR = Copy_u8Address<<1;
	
	/*enable the TWI module */
	SET_BIT(TWCR, TWEN);
}

void TWI_voidSendStartCondition(void){
	/* set the START bit in TWCR */
	SET_BIT(TWCR, TWSTA);
	
	/*set TWINT to clear the flag and start the execution */
	SET_BIT(TWCR, TWINT);
	
	/*wait until flag is raised again */
	while(GET_BIT(TWCR, TWINT) == 0);
	
	/*check for the status */
	if((TWSR & 0xF8) != START_ACK){
		//error
	}
	
	/*clear the start bit */
	CLR_BIT(TWCR, TWSTA);
}

void TWI_voidSendRepeatedStart(void){
	/* set the START bit in TWCR */
	SET_BIT(TWCR, TWSTA);
	
	/*set TWINT to clear the flag and start the execution */
	SET_BIT(TWCR, TWINT);
	
	/*wait until flag is raised again */
	while(GET_BIT(TWCR, TWINT) == 0);
	
	/*check for the status */
	if((TWSR & 0xF8) != REPEATED_START_ACK){
		//error
	}
	
	/*clear the start bit */
	CLR_BIT(TWCR, TWSTA);
}

void TWI_voidSendSlaveAddressWithRead(u8 Copy_u8Slave){
	/*check if TWINT is high to write to TWDR */
	if(GET_BIT(TWCR, TWINT) == 1){
		
		/*put the address in TWDR with read*/
		TWDR = Copy_u8Address<<1 | 0x01;
	
		/*set TWINT to clear the flag and start the execution */
		SET_BIT(TWCR, TWINT);
		
		/*wait until flag is raised again */
		while(GET_BIT(TWCR, TWINT) == 0);
		
		if((TWSR & 0xF8) != SLAR_ACK){
			//error send stop or repeated start
		}
		
	}
}

void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8Slave){
	/*check if TWINT is high to write to TWDR */
	if(GET_BIT(TWCR, TWINT) == 1){
		
		/*put the address in TWDR with write command*/
		TWDR = Copy_u8Address<<1 ;
		
		/*set TWINT to clear the flag and start the execution */
		SET_BIT(TWCR, TWINT);
		
		/*wait until flag is raised again */
		while(GET_BIT(TWCR, TWINT) == 0);
		
		if((TWSR & 0xF8) != SLAW_ACK){
			//error send stop or repeated start
		}
		
	}
}

void TWI_voidSendData(u8 Copy_u8Data){
	/*check if TWINT is high to write to TWDR */
	if(GET_BIT(TWCR, TWINT) == 1){
		
		/* put the data in TWDR */
		TWDR = Copy_u8Data;
		
		/*set TWINT to clear the flag and start the execution */
		SET_BIT(TWCR, TWINT);
		
		/*wait until flag is raised again */
		while(GET_BIT(TWCR, TWINT) == 0);
		if((TWSR & 0xF8) != DATA_TRAN_ACK){
			//error send stop or repeated start
		}
	
	}
}

void TWI_voidReadData(u8 *Ptr_u8Buffer){
	/* clear the interrupt flag to start receive from slave */
	SET_BIT(TWCR, TWINT);
	
	/*wait until flag is raised again */
	while(GET_BIT(TWCR, TWINT) == 0);
	
	if((TWSR & 0xF8) != DATA_REC_ACK){
		//error send stop or repeated start
	}
	else{
	
		*Ptr_u8Buffer = TWDR;

	}
}

void TWI_voidSendStop(void){
	/* set the TWSTO bit in TWCR */
	SET_BIT(TWCR, TWSTO);
	
	/*set TWINT to clear the flag and start the execution */
	SET_BIT(TWCR, TWINT);
}