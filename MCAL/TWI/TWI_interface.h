/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: TWI           ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/


#ifndef		TWI_INTERFACE_H_
#define		TWI_INTERFACE_H_

enum{
	NoError,
	StartConditionError,
	RepeatedStartError,
	SLAWError,
	SLARError,
	DataTransError,
	DataRecError
}TWI_status;



void TWI_voidInitMaster(void);

void TWI_voidInitSlave(u8 Copy_u8Address);

void TWI_voidSendStartCondition(void);

void TWI_voidSendRepeatedStart(void);

void TWI_voidSendSlaveAddressWithRead(u8 Copy_u8Slave);

void TWI_voidSendSlaveAddressWithWrite(u8 Copy_u8Slave);

void TWI_voidSendData(u8 Copy_u8Data);

void TWI_voidReadData(u8 *Ptr_u8Buffer);

void TWI_voidSendStop(void);



#endif
