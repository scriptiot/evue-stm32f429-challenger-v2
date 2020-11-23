#ifndef __SYSTICK_H
#define __SYSTICK_H

#include "stm32f4xx.h"

void TimingDelay_Decrement(void);
void SysTick_Init(void);
void Delay_us(__IO u32 nTime);
#define Delay_ms(x) Delay_us(x)	 //��λms

#endif /* __SYSTICK_H */
