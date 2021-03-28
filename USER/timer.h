#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
	
extern int scount;
void TIM3_Int_Init(u16 arr,u16 psc);
extern void Serial_Interpret(void);//

#endif
