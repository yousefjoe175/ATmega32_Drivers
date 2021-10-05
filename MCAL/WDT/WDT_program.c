/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: WDT           ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/

#include "WDT_interface.h"

void WDT_voidInitialize(void){
	//set the period
	SET_VAL(WDTCR,WDP0,WDT_PRESCALER);
	// enable the WD
	SET_BIT(WDTCR,WDE);
}

void WDT_voidDisableWD(void){
	SET_BIT(WDTCR,WDTOE);
	CLR_BIT(WDTCR,WDE);
}