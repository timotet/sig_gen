/*
 * spi.h
 * this is for stm32f031K6 connected to a HX8347G lcd
 * 4/11/15
 */

#ifndef SPI_H_
#define SPI_H_

#ifdef	__cplusplus
extern "C" {
#endif

#include "stm32f0xx.h"

/* SPIx Communication Interface */
#define SPI                            SPI1
#define SPI1_CLK                       RCC_APB2Periph_SPI1
#define SPI1_CLK_CMD                   RCC_APB2PeriphClockCmd
//#define SPI1_IRQn                      SPI1_IRQn
//#define SPI1_IRQHANDLER                SPI1_IRQn

#define SPI1_SCK_PIN                   GPIO_Pin_5
#define SPI1_SCK_GPIO_PORT             GPIOA
#define SPI1_SCK_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define SPI1_SCK_SOURCE                GPIO_PinSource5
#define SPI1_SCK_AF                    GPIO_AF_0

#define SPI1_MISO_PIN                  GPIO_Pin_6
#define SPI1_MISO_GPIO_PORT            GPIOA
#define SPI1_MISO_GPIO_CLK             RCC_AHBPeriph_GPIOA
#define SPI1_MISO_SOURCE               GPIO_PinSource6
#define SPI1_MISO_AF                   GPIO_AF_0

#define SPI1_MOSI_PIN                  GPIO_Pin_7
#define SPI1_MOSI_GPIO_PORT            GPIOA
#define SPI1_MOSI_GPIO_CLK             RCC_AHBPeriph_GPIOA
#define SPI1_MOSI_SOURCE               GPIO_PinSource7
#define SPI1_MOSI_AF                   GPIO_AF_0


/* Definition for DMAx resources **********************************************/
#define SPI_PORT_DR_ADDRESS                SPI1->DR

#define SPI_PORT_DMA                       DMA1
#define SPI_PORT_DMAx_CLK                  RCC_AHBPeriph_DMA1

#define SPI_PORT_TX_DMA_CHANNEL            DMA1_Channel3
#define SPI_PORT_TX_DMA_STREAM             DMA1_Channel3
#define SPI_PORT_TX_DMA_FLAG_TEIF          DMA_IT_TE
#define SPI_PORT_TX_DMA_FLAG_HTIF          DMA_IT_HT
#define SPI_PORT_TX_DMA_FLAG_TCIF          DMA_IT_TC

//#define SPI_DMA_TX_IRQn                    DMA1_Channel2_3_IRQn
//#define SPI_PORT_DMA_TX_IRQHandler         DMA1_Channel2_3_IRQHandler

//////////function prototypes//////////
void
SPI_Config(void);
//void
//DMA_Config(void);
//void
//spiPutDMA(uint16_t * addr, uint16_t length);

#ifdef	__cplusplus
}
#endif

#endif /* SPI_H_ */
