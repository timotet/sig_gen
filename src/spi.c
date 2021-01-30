/*
 * spi.c
 * this is for stm32f0 discovery connected to a HX8347G lcd
 * 4/11/15
 * reworked for this project 2/10/19
 */

#include "stm32f0xx.h"
#include "spi.h"
#include "hx8347g.h"

//uint16_t DMA_Buffer_Size = 504;

/* Private typedef -----------------------------------------------------------*/
SPI_InitTypeDef SPI_InitStructure;
//NVIC_InitTypeDef NVIC_InitStructure;
//DMA_InitTypeDef DMA_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;

// Set up SPI1 peripheral
void
SPI_Config(void) {

	// enable SPI peripheral clock
	RCC_APB2PeriphClockCmd(SPI1_CLK, ENABLE);

	// enable the peripheral GPIO port clocks
	RCC_AHBPeriphClockCmd(
	SPI1_SCK_GPIO_CLK | SPI1_MOSI_GPIO_CLK | SPI1_MISO_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

	// SPI SCK pin configuration
	GPIO_InitStructure.GPIO_Pin = SPI1_SCK_PIN;
	GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStructure);

	// SPI MOSI pin configuration
	GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_PIN;
	GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStructure);

	// SPI MISO pin configuration
	GPIO_InitStructure.GPIO_Pin = SPI1_MISO_PIN;
	GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStructure);

	// SPI NSS pin configuration
	//GPIO_InitStructure.GPIO_Pin = SPI1_NSS_PIN;
	//GPIO_Init(SPI1_NSS_GPIO_PORT, &GPIO_InitStructure);

	// Connect GPIO pins for SPI as alternate function
	GPIO_PinAFConfig(SPI1_SCK_GPIO_PORT, SPI1_SCK_SOURCE, SPI1_SCK_AF);
	GPIO_PinAFConfig(SPI1_MOSI_GPIO_PORT, SPI1_MOSI_SOURCE, SPI1_MOSI_AF);
	GPIO_PinAFConfig(SPI1_MISO_GPIO_PORT, SPI1_MISO_SOURCE, SPI1_MISO_AF);
    //GPIO_PinAFConfig(SPI1_NSS_GPIO_PORT, SPI1_NSS_SOURCE, SPI1_NSS_AF);

	// set up the SPI peripheral
	SPI_I2S_DeInit(SPI1);
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_Init(SPI1, &SPI_InitStructure);

	// Configure the RX FIFO Threshold
	SPI_RxFIFOThresholdConfig(SPI1, SPI_RxFIFOThreshold_QF);

	// DMA
//	SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);

	//Enable the SPI port
	SPI_Cmd(SPI1, ENABLE);
}

//void
//DMA_Config(void) {
//
//	DMA_StructInit(&DMA_InitStructure);
//	// DMA setup
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
//	// reset DMA configuration
//	DMA_DeInit(DMA1_Channel3);
//	// configure DMA
//	DMA_InitStructure.DMA_MemoryBaseAddr = 0;
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) &(SPI1->DR);
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//	DMA_InitStructure.DMA_BufferSize = DMA_Buffer_Size;
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
//	DMA_Init(DMA1_Channel3, &DMA_InitStructure);
//
//	// Enable the DMA transfer complete interrupt
//	DMA_ITConfig(DMA1_Channel3, DMA_IT_TC, ENABLE);
//
//	// Enable the interrupt in the NVIC
//	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel2_3_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x00;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
//
//// DMA transfer
//void
//spiPutDMA(uint16_t *addr, uint16_t length) {
//
//	LCD_CS_Low;
//	LCD_WriteRAM_Prepare();
//	DMA1_Channel3->CNDTR = length;
//	DMA1_Channel3->CMAR = (uint32_t) addr;
//	DMA_Cmd(DMA1_Channel3, ENABLE);
//}
//
//// DMA interrupt routine
//void
//DMA1_Channel2_3_IRQHandler() {
//
//	DMA_ClearITPendingBit(DMA1_IT_GL3);
//	DMA_Cmd(DMA1_Channel3, DISABLE);
//	LCD_CS_High;
//}
