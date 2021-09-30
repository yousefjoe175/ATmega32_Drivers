/*
 * KBD_PROG.c
 *
 * Created: 7/26/2020 1:29:19 PM
 *  Author: Yousef Khaled Abu Elnaga
 */ 

#include "KBD_INT.h"

u8 keypad[4][4]={
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'c','0','=','+'}
};

u8 KBD_getKey(void)
{
	u8 colloc, rowloc;
	u8 i, j;
	u8 key ;
	KEY_DDR = 0xF0;	//columns are output, rows are input
	KEY_PRT = 0xF0; //pull up resistor for inputs and wait for grounding the output
	
	while(1){
		
		
		do{		//check if a key is pressed initially
			KEY_PRT &= 0x0F; //ground the columns
			if((KEY_PIN & 0x0F)!= 0x0F){		//check if any column is grounded
				_delay_ms(20);	//wait 5ms for the debounce
				(KEY_PIN & 0x0F); //repeat the last task
				if((KEY_PIN & 0x0F) != 0x0F){
					break;
				}
			}
		}while((KEY_PIN & 0x0F) == 0x0F);
		
		
		
		
		
		for(j=4;j<8;j++){ //iterate over the column pins and check if there any key is pressed
			KEY_PRT = 0xF0;
			CLR_BIT(KEY_PRT,j);
			if((KEY_PIN & 0x0F) != 0x0F){ //if any key is pressed
				colloc = j-4;	//mark the column
				for(i=0;i<4;i++){	//iterate over the rows and check the pressed row
					if(GET_BIT(KEY_PIN,i) == 0){ //if the row is pressed
						rowloc = i;
						break;
					}
				}
			}
			SET_BIT(KEY_PRT,j);
		}
		key = keypad[rowloc][colloc];	//store the correspond key
		
		while(GET_BIT(KEY_PIN,rowloc) ==0);	//wait until the key is released
		return key;
		
	}
	
}