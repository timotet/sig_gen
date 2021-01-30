/*
 * flash.h
 *
 *  Created on: Jun 28, 2016
 *      Author: Tim
 */

#ifndef FLASH_H_
#define FLASH_H_

void writeFlash(uint32_t ADDR, uint32_t *DATA, uint16_t len);
uint32_t getFlashData(uint32_t ADDR);

#endif /* FLASH_H_ */


