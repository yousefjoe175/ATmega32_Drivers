/*********************************************************************/
/*********************************************************************/
/******** Author:    Yousef Khaled ***********************************/
/******** Component: WDT           ***********************************/
/******** Layer:     MCAL          ***********************************/
/*********************************************************************/
/*********************************************************************/

#ifndef WDT_INTERFACE_H
#define WDT_INTERFACE_H

#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "WDT_register.h"

/* prescalers
 * 0	17.1ms
 * 1    34.1ms
 * 2	68.5ms
 * 3	0.14s
 * 4	0.27s
 * 5	0.55s
 * 6	1.1s
 * 7	2.2s
 */
#define WDT_PRESCALER 7

void WDT_voidInitialize(void);

void WDT_voidDisableWD(void);


#endif