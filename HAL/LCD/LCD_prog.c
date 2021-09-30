/*
 * LCD_prog.c
 *
 * Created: 7/25/2020 8:14:39 PM
 *  Author: EGYPT_LAPTOP
 */ 

#include "LCD_INT.h"
#include <util/delay.h>


void LCD_voidSendCmnd(u8 data){
	LCD_DATA_PORT = data;	
	CLR_BIT(LCD_CONT_PORT, LCD_RS_PIN);	//to send a command
	CLR_BIT(LCD_CONT_PORT, LCD_RW_PIN); //to write on data register
    SET_BIT(LCD_CONT_PORT,  LCD_E_PIN); 	//high signal on Enable 
	_delay_us(2);
	CLR_BIT(LCD_CONT_PORT,  LCD_E_PIN);	//end the enable pulse to latch the data
	_delay_ms(1);
}

void LCD_voidSendData(u8 data){
	LCD_DATA_PORT = data;
	SET_BIT(LCD_CONT_PORT, LCD_RS_PIN);	//to send a data
	CLR_BIT(LCD_CONT_PORT, LCD_RW_PIN); //to write on data register
	 SET_BIT(LCD_CONT_PORT,  LCD_E_PIN); 	//high signal on Enable
	 _delay_us(2);
	 CLR_BIT(LCD_CONT_PORT,  LCD_E_PIN);	//end the enable pulse to latch the data
	_delay_ms(2);
	
}

void LCD_voidPrintString(u8 *str){
	u8 i = 0;	//counter for the array of chars
	while(*(str+i) != '\0'){	
		LCD_voidSendData(*(str+i));	
		i++;
	}
}

void LCD_voidGoTo(u8 x, u8 y){
	u8 firstChar[] = {0x80,0xC0};
	LCD_voidSendCmnd(firstChar[x-1] + (y-1));
	_delay_ms(1);
}

void LCD_voidInitLCD(){
	LCD_DATA_DIR = 0xFF;
	LCD_CONT_DIR = 0xFF;
	LCD_voidSendCmnd(LCD_FuncSet);	
	LCD_voidSendCmnd(LCD_DispCtrl);
	LCD_voidSendCmnd(LCD_DispClr);
	LCD_voidSendCmnd(LCD_EntrMod);
}


void LCD_voidSendNumber(u32 num){
	u8 c;
	u32 y = 1;
	while(num/(10*y) !=0){
		y*=10;
	}
	while(num !=0){
		c = (num/y)+'0';
		LCD_voidSendData(c);
		num %=y;
		y/=10;
	}
}


void init4(){
	cmnd4(0x2);
	cmnd4(0x28);
	cmnd4(0x0E);
	cmnd4(0x06);
	cmnd4(0x83);
	
	
}

void println4(unsigned char *str){
	unsigned char i = 0;
	while(*(str+i) != '\0'){
		sdata4(*(str+i));
		i++;
	}
}

void sdata4(unsigned char data){
	PORTA = data * 0xF0;
	PORTB = 0x05;
	_delay_us(2);
	PORTB = 0x01;
	_delay_ms(2);
	PORTA = data<<4;
	PORTB = 0x05;
	_delay_us(2);
	PORTB = 0x01;
	_delay_ms(2);
}

void cmnd4(unsigned char data){
	PORTA = data * 0xF0;
	PORTB = 0x04;
	_delay_us(2);
	PORTB = 0x00;
	_delay_ms(1);
	PORTA = data<<4;
	PORTB = 0x04;
	_delay_us(2);
	PORTB = 0x00;
	_delay_ms(1);
	
}