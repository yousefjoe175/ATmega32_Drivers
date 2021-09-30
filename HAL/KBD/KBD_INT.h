/*
 * KBD_INT.h
 *
 * Created: 7/26/2020 1:26:31 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 


#ifndef KBD_INT_H_
#define KBD_INT_H_

#include "DIO_INT.h"
#include "STD_TYPES.h"
#include "Bit_math.h"
#include <util/delay.h>

#define KEY_PRT PORTC
#define KEY_DDR DDRC
#define KEY_PIN PINC

extern u8 keypad[4][4];
/*detect the key pressed and return the equivalent character*/
/*NOTE: Change the array according to the KBD index*/
u8 KBD_getKey(void);



#endif /* KBD_INT_H_ */