/*
 * delay.c
 * 6/15/12
 */

#include "delay.h"
#include "stm32f0xx.h"

void longDelay(__IO uint32_t nCount) {
	__IO uint32_t index = 0;
	for (index = (65500 * nCount); index != 0; index--) {
	}
}

void delay(__IO uint32_t nCount) {
	while (nCount--) {
	}
}
