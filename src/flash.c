/*
 * flash.c
 *
 *  functions for writing to the flash memory of the stm32f0xx
 *
 *  Created on: Jun 28, 2016
 *      Author: Tim
 *
 */


#include "stm32f0xx.h"
#include "flash.h"

typedef enum {FAILED = 0, PASSED = !FAILED} TestStatus;
__IO uint32_t rData = 0;
__IO FLASH_Status flashStatus = FLASH_COMPLETE;
__IO TestStatus testResult = PASSED;

uint32_t pageSize = 0x00000400;
uint32_t pageStart = 0x08007C00;      // first address of user flash memory sector 15 page 63
uint32_t pageEnd = 0x08007FFF;        // last address of user flash
__IO uint32_t TEMP_ADDR = 0;

 /*
  * This writes the values from an array to the flash
  * @ ADDR: the start address of the page
  * @ DATA: pointer to array to be written
  * @ len:  length of array
  * The whole page will be erased 1024 bytes
  * incremented by 32, only 32 values per page
 */
void writeFlash(uint32_t ADDR, uint32_t *DATA, uint16_t len) {

  uint16_t i;
  TEMP_ADDR = ADDR;   // for reading after write

	// Unlock the Flash to enable the flash control register access
	FLASH_Unlock();

	// Clear pending flags (if any)
	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

	// Erase the FLASH page
	flashStatus = FLASH_ErasePage(pageStart);
	if (flashStatus != FLASH_COMPLETE) {

		// flash erase error!!!
//		TIM_Cmd(TIM14, DISABLE);       // turn off timer as it shares the debug led
		GPIO_SetBits(GPIOC, GPIO_Pin_9); // turn on board mounted led for error indicator green
		while (1);
	}

	// write the array to flash
	for (i = 0; i < len; i++) {
	    flashStatus = FLASH_ProgramWord(TEMP_ADDR, DATA[i]);
	    TEMP_ADDR += 4;   //  increment address by 4
	}
	if (flashStatus != FLASH_COMPLETE) {

		// flash write error!!!
//		TIM_Cmd(TIM14, DISABLE);          // turn off timer as it shares the debug led
		GPIO_SetBits(GPIOC, GPIO_Pin_9); // turn on board mounted led for error indicator
		while (1);
	}

	// Lock the Flash to disable the flash control register access
	FLASH_Lock();

	TEMP_ADDR = ADDR;
	// now lets check to make sure the data was written correctly
  for (i = 0; i < len; i++) {
      rData = *(__IO uint32_t *) TEMP_ADDR;

      if (rData != DATA[i]) {
          testResult = FAILED;
//		    TIM_Cmd(TIM14, DISABLE);          // turn off timer as it shares the debug led
          GPIO_SetBits (GPIOC, GPIO_Pin_9); // turn on board mounted led for error indicator
          while (1)
            ;
        }
      TEMP_ADDR += 4;
    }
}

// Read data from flash
// ADDR = address to read from
uint32_t getFlashData(uint32_t ADDR) {

	 return *(__IO uint32_t *) ADDR;

}
