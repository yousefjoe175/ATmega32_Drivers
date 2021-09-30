/*
 * UART.c
 *
 * Created: 8/18/2020 6:42:38 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#include "UART.h"

static void (*UART_pvTransmitCompleteCallBack)(void) = NULL;
static void (*UART_pvReceiveCompleteCallBack)(void) = NULL;

static u8 *UART_pChToString = NULL;
static u8 *UART_ReceriveBuffer = NULL;
static u8 UART_Counter = 0;
static u8 UART_BufferSize;
void UART_voidInit(void){
	u8  ucsrb, ucsrc;	
	ucsrb = ucsrb |(1<<TXEN | 1<<RXEN);		//Enable TX and RX.    //we didn't set the interrupts yet
	ucsrc = ucsrc |(1<<URSEL| 3<<UCSZ);		//select UCSRC and set the character size to 8 bit.
	
	UBRRL = 51;		//baudrate 9600 for 8MHz
	
	UCSRB = ucsrb;	//Enable RX , TX only without interrupts
	UCSRC = ucsrc;	//8-bit data
}


//For Polling transmission and reception
void UART_voidSendDataSynch(u8 Copy_u8Data){
	
	while(GET_BIT(UCSRA,UDRE) == 0);	//wait until the Data Registe Embty is set
	UDR = Copy_u8Data;
	while(GET_BIT(UCSRA,TXC) == 0);	//wait until data is transmitted
	SET_BIT(UCSRA,TXC);	//clear the flag of TX complete
}

void UART_u8ReceiveDataSynch(u8 *Copy_pu8Data){
	while(GET_BIT(UCSRA,RXC)==0);	//wait until there's data to be read in the receive buffer
	SET_BIT(UCSRA,RXC);				//clear the receive flag 
	*Copy_pu8Data = UDR;			//send the received character to the addressed variable
}

void UART_voidSendStringSynch(u8* Copy_pu8String){
	u8 counter = 0;
		while(Copy_pu8String[counter] != '\0'){
			
			UART_voidSendDataSynch(Copy_pu8String[counter]);
			counter++;
		}
		
	
}
// needs Zero-input special case handling
void UART_voidSendNumberSynch(u32 Copy_u32Number){
	u8 SentChar;
	u32 y = 1;
	if(Copy_u32Number == 0){
		UART_voidSendDataSynch('0');
	}
	while(Copy_u32Number/(10*y) !=0){
		y*=10;
	}
	while(Copy_u32Number !=0){
		SentChar = (Copy_u32Number/y)+'0';
		UART_voidSendDataSynch(SentChar);
		Copy_u32Number %=y;
		y/=10;
	}
}

void UART_voidReceiveStringSynch(u8* Copy_pu8Data , u8 BufferSize){
	
	u8 counter = -1;
	do{
		counter++;
		UART_u8ReceiveDataSynch(Copy_pu8Data+counter);
		UART_voidSendDataSynch(Copy_pu8Data[counter]);
	}while(Copy_pu8Data[counter] != '+' && counter < BufferSize-1 );				//loop until Enter is pressed and is less than the last element of the buffer
	Copy_pu8Data[counter] = '\0';			//put the null character at the last element of the buffer
}

void UART_voidReceiveNumberSynch(u32 *Copy_pu32Number){
	u8 Buffer[10];
	u8 numlen = -1;
	u8 counter = 0;
	u32 number = 0;
	u32 decimal = 1;
	u8 temp;
	do{		//receive the number and put it into a buffer
		numlen++;
		UART_u8ReceiveDataSynch(&(Buffer[numlen]));
		UART_voidSendDataSynch(Buffer[numlen]);
		
	}while(Buffer[numlen] != '+' && numlen< 10);		//the last element storing Enter char.
	
	for( ;counter<=numlen/2;counter++){	//swap the buffer element	as it is stored inversely
		temp = Buffer[numlen - counter-1];
		Buffer[numlen - counter - 1] = Buffer[counter] - '0';
		Buffer[counter] = temp - '0';
		
	}
	for(counter = 0; counter<numlen; counter++){
		number = number + Buffer[counter]*decimal;
		decimal *= 10;
		//UART_voidSendNumberSynch(number);	
	}
	
	*Copy_pu32Number = number;
	
}

void UART_voidSendStringAsynch(u8* Copy_pu8String, void *(Copy_pvNotificationFunction)(void)){
		UART_pvTransmitCompleteCallBack = Copy_pvNotificationFunction;
		UART_pChToString = Copy_pu8String;
		SET_BIT(UCSRB, UDRIE);	//Enable The Data Register Empty Interrupt
		SET_BIT(SREG,7);	//Enable the global Interrupt
	
	
}

void UART_voidReceiveStringAsynch(u8* Copy_pu8Data , u8 BufferSize, void *(Copy_pvNotificationFunction)(void)){
	UART_pvReceiveCompleteCallBack = Copy_pvNotificationFunction;
	UART_ReceriveBuffer = Copy_pu8Data;
	UART_BufferSize = BufferSize;
	SET_BIT(UCSRB, RXIE);	//Enable The receive complete interrupt
	SET_BIT(SREG, 7);		//Enable the Global Interrupt
	
}

//Receive Complete ISR
void __vector_13(void)	__attribute__((signal));	
void __vector_13(void){
	*(UART_ReceriveBuffer + UART_Counter) = UDR;
	UDR = *(UART_ReceriveBuffer + UART_Counter); 
	
	if(UART_ReceriveBuffer[UART_Counter] == 13 || UART_Counter >= UART_BufferSize){
		UART_ReceriveBuffer[UART_Counter] = '\0';
		UART_Counter = 0;
		CLR_BIT(UCSRB,RXIE);
		CLR_BIT(SREG, 7);
		UART_pvReceiveCompleteCallBack();
	}else{
		UART_Counter++;
	}
}

//Data Register Empty ISR
void __vector_14(void)	__attribute__((signal));
void __vector_14(void){
	UDR = *(UART_pChToString + UART_Counter);
	UART_Counter++;
	if(UART_pChToString[UART_Counter] == '\0'){
		UART_Counter = 0;
		CLR_BIT(UCSRB,UDRIE);
		CLR_BIT(SREG,7);
		UART_pvTransmitCompleteCallBack();
	}
	
}