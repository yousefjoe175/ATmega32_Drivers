/*
 *  SPI_program.c
 *
 *  Created: 1/9/2021
 *  Author: Yousef Khaled Abu Elnaga
 */ 



#include "SPI_interface.h"

void SPI_voidMasterInit(void){
	u8 Local_u8SPCR = 0;
	
	//set MOSI as output
	DIO_voidSetPinDirection(SPI_MOSI, DIO_OUTPUT);
	//set SCK as output
	DIO_voidSetPinDirection(SPI_SCK, DIO_OUTPUT);
	//set SS as output
	DIO_voidSetPinDirection(SPI_SS, DIO_OUTPUT);
	//set SS high
	DIO_voidSetPinValue(SPI_SS, DIO_HIGH);
	
	//set data order as LSB first
	SET_BIT(Local_u8SPCR, DORD);
	//set as master
	SET_BIT(Local_u8SPCR, MSTR);
	//set the polarity and phase
	SET_VAL(Local_u8SPCR, SPI_CPHA, CLOCK_PLOARITY_PHASE );
	//set the clock rate
	SET_VAL(Local_u8SPCR, SPI_SPR0, CLOCK_RATE);
	//enable the SPI
	SET_BIT(Local_u8SPCR, SPE);
	
	// set the register
	SPI_SPCR = Local_u8SPCR;
}


void SPI_voidSlaveInit(void){
	u8 Local_u8SPCR = 0;
	
	//set MISO as output
	DIO_voidSetPinDirection(SPI_MISO, DIO_OUTPUT);
	
	//set data order as LSB first
	SET_BIT(Local_u8SPCR, DORD);
	//set the polarity and phase
	SET_VAL(Local_u8SPCR, SPI_CPHA, CLOCK_PLOARITY_PHASE );
	//set the clock rate
	SET_VAL(Local_u8SPCR, SPI_SPR0, CLOCK_RATE);
	//enable the SPI
	SET_BIT(Local_u8SPCR, SPE);
	
	// set the register
	SPI_SPCR = Local_u8SPCR;
	
}

void SPI_voidSlaveSelect(u8 state){
	if(state == 1){
		DIO_voidSetPinValue(SPI_SS, DIO_LOW);
	}else if(state == 0){
		DIO_voidSetPinValue(SPI_SS, DIO_HIGH);
	}
}

u8 SPI_u8MasterTranscieve(u8 copy_u8Data){
	SPI_SPDR = copy_u8Data;
	while(!GET_BIT(SPI_SPSR,SPIF));
	return SPI_SPDR;
}

u8 SPI_u8SlaveTranscieve(u8 copy_u8Data){
	SPI_SPDR = copy_u8Data;
	while(!GET_BIT(SPI_SPSR,SPIF));
	return SPI_SPDR;
}