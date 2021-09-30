/*
 * LCD_INT.h
 *
 * Created: 7/25/2020 8:15:13 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef LCD_INT_H_
#define LCD_INT_H_
#include "../MCAL/DIO_INT.h"
#include "../LIB/STD_TYPES.h"
#include "../LIB/Bit_math.h"

#define LCD_DATA_PORT    PORTC	//to send data or command
#define LCD_CONT_PORT    PORTD	//to control RS RW E
#define LCD_DATA_DIR     DDRC
#define LCD_CONT_DIR     DDRD
#define LCD_RS_PIN       0
#define LCD_RW_PIN       1
#define LCD_E_PIN        2

#define LCD_FuncSet	 0x38	//1st init cmnd with 2 line display
#define LCD_DispCtrl 0x0E	//2nd init cmnd with cursor On blink off
#define LCD_DispClr	 0x01	//3rd init cmnd clear display
#define LCD_EntrMod	 0x06	//4th init cmnd with increment mode

#define LCD_RtrnHom 0x02	//return home with no change of content

void LCD_voidInitLCD();	//initialize the LCD

void LCD_voidSendCmnd(u8 data);	//send command to the LCD

void LCD_voidSendData(u8 data); //send data to be displayed on LCD

void LCD_voidPrintString(u8 *str);	//print a whole string on LCD

void LCD_voidgoto(u8 x, u8 y);	//go to a certain location on the screen to start printing from

void LCD_voidSendNumber(u32 num); //display an integer on the LCD




#endif /* LCD_INT_H_ */