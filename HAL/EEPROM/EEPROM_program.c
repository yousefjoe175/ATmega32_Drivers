/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: EEPROM        ***********************************/
/******** Layer:     HAL           ***********************************/
/*********************************************************************/
/*********************************************************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TIMER_interface.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"

void EEPROM_voidInit(void)
{
	TWI_voidInitMaster();
}



void EEPROM_voidSendDataByte(u16 Copy_u16address, u8 Copy_u8data)
{
	/*initiate the transmission with start condition */
    TWI_voidSendStartCondition();
	/*send the device address */
	TWI_voidSendSlaveAddressWithWrite(0b01010000);
	/*send the data address */
	TWI_voidSendData((u8)Copy_u16address);
	/*write the actual data */
	TWI_voidSendData(Copy_u8data);
	/*send the STOP condition to terminate the transmission */
	TWI_voidSendStop();
	/*delay for 100 ms */
	TIMER0_voidSetBusyWait(100000);
}



u8   EEPROM_u8ReadDataByte(u16 Copy_u16address);
{
	u8 Local_u8Data;
	/* initiate the connection with start condition */
	TWI_voidSendStartCondition();
	/* send the device address */
	TWI_voidSendSlaveAddressWithWrite(0b01010000);
	/* send the data address */
	TWI_voidSendData((u8)Copy_u16address);
	/* send repeated start to initiate the reception */
	TWI_voidSendRepeatedStart();
	/* send the device address with read request */
	TWI_voidSendSlaveAddressWithRead(0b01010000);
	/* read the data coming from the device in Local_u8Data*/
	TWI_voidReadData(&Local_u8Data);
	/* send STOP condition to terminate the reception */
	TWI_voidSendStop();
	/*delay for 100 ms */
	TIMER0_voidSetBusyWait(100000);
	/* return the data received */
	return Local_u8Data;
}
