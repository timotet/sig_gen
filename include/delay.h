/*
 * delay.h
 * 6/15/12
 */

#ifndef DELAY_H_
#define DELAY_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"

void longDelay(__IO uint32_t nCount);
void delay(__IO uint32_t nCount);

#ifdef	__cplusplus
}
#endif

#endif /* DELAY_H_ */
