/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: UART          ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "../LIB/Bit_math.h"
#include "../LIB/STD_TYPES.h"
#include "DIO_INT.h"
#include "UART_register.h"

#define F_CPU 8000000
#define NULL 0


void UART_voidInit(void);

void UART_voidSendDataSynch(u8 Copy_u8Data);

void UART_u8ReceiveDataSynch(u8 *Copy_pu8Data);

void UART_voidSendStringSynch(u8* Copy_pu8String);

void UART_voidSendNumberSynch(u32 Copy_u32Number);

void UART_voidReceiveStringSynch(u8* Copy_pu8Data , u8 BufferSize);

void UART_voidReceiveNumberSynch(u32 *Copy_pu32Number);

void UART_voidSendStringAsynch(u8* Copy_pu8String, void *(Copy_pvNotificationFunction)(void));

void UART_voidReceiveStringAsynch(u8* Copy_pu8Data , u8 BufferSize, void *(Copy_pvNotificationFunction)(void));


#endif /* UART_H_ */