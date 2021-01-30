/*
 * Use an STM32f031k6 nucleo board to talk
 * to a 320X240 TFT lcd with HX8347G controller
 *
 * 2/10/19 Moved to STM32f0 discovery board stm32f051R8T6
 *         A better Sine wave generator
 *
 * 2/11/19 encoder reading with timer 1 is going
 *
 * 2/23/19 updated sine table to 256 values
 *
 * 3/2/19 added triangle wave look up table
 *
 * 3/4/19 added Trent Cleghorn's button debounce code
 *        added square and sawtooth wave tables
 *        fixed button interrupt code! doh!
 *
 * 3/5/19 added clear some function to clean up lcd writes
 *
 * 3/6/19 added figFreq function for displaying frequency on screen
 *
 * 3/9/19 added make array for displaying frequency in my custom font
 *
 * 3/12/19 Fixed Hz display, made it follow the digits instead of
 *         just hanging out in space on the LCD.
 *         also added storing the period and state in flash
 *         for when the device gets used again.
 *
 * 3/26/19 Display wave form at bottom of LCD
 *         Wrote a scale function to use the same lookup tables
 *         as the wave form for the dac!
 *
 * 3/30/19 Gave up on flash writes, data was getting corrupted
 *         causing a system crash, spent some time trying to get it
 *         to work properly but oh well. Not really needed anyway.
 *
 * 4/1/19  Software is (considered) finished. Moving on to hardware.
 *
 */

#include "stm32f0xx.h"
#include "hx8347g.h"
#include "spi.h"
#include "delay.h"
//#include "flash.h"
#include "stdbool.h"
#include "button_debounce.h"

// portC
#define debugLed         GPIO_Pin_8                      // Blue
#define debugLow         GPIO_ResetBits(GPIOC, debugLed)
#define debugHigh        GPIO_SetBits(GPIOC, debugLed)

#define debugLed2        GPIO_Pin_9                      // Green
#define debug2Low        GPIO_ResetBits(GPIOC, debugLed2)
#define debug2High       GPIO_SetBits(GPIOC, debugLed2)

// portB
#define button           GPIO_Pin_6    // button on PB6

#define DAC_ADDRESS      0x40007408
#define TIM6_PERIOD      2500
#define numOfSamples     256

const uint16_t SquareWave[256] = { 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
		4095, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const uint16_t SawtoothWave[256] = { 0, 16, 32, 48, 64, 80, 96, 112, 128, 145,
		161, 177, 193, 209, 225, 241, 257, 274, 290, 306, 322, 338, 354, 370,
		386, 403, 419, 435, 451, 467, 483, 499, 515, 532, 548, 564, 580, 596,
		612, 628, 644, 661, 677, 693, 709, 725, 741, 757, 773, 789, 806, 822,
		838, 854, 870, 886, 902, 918, 935, 951, 967, 983, 999, 1015, 1031, 1047,
		1064, 1080, 1096, 1112, 1128, 1144, 1160, 1176, 1193, 1209, 1225, 1241,
		1257, 1273, 1289, 1305, 1322, 1338, 1354, 1370, 1386, 1402, 1418, 1434,
		1450, 1467, 1483, 1499, 1515, 1531, 1547, 1563, 1579, 1596, 1612, 1628,
		1644, 1660, 1676, 1692, 1708, 1725, 1741, 1757, 1773, 1789, 1805, 1821,
		1837, 1854, 1870, 1886, 1902, 1918, 1934, 1950, 1966, 1983, 1999, 2015,
		2031, 2047, 2063, 2079, 2095, 2111, 2128, 2144, 2160, 2176, 2192, 2208,
		2224, 2240, 2257, 2273, 2289, 2305, 2321, 2337, 2353, 2369, 2386, 2402,
		2418, 2434, 2450, 2466, 2482, 2498, 2515, 2531, 2547, 2563, 2579, 2595,
		2611, 2627, 2644, 2660, 2676, 2692, 2708, 2724, 2740, 2756, 2772, 2789,
		2805, 2821, 2837, 2853, 2869, 2885, 2901, 2918, 2934, 2950, 2966, 2982,
		2998, 3014, 3030, 3047, 3063, 3079, 3095, 3111, 3127, 3143, 3159, 3176,
		3192, 3208, 3224, 3240, 3256, 3272, 3288, 3305, 3321, 3337, 3353, 3369,
		3385, 3401, 3417, 3433, 3450, 3466, 3482, 3498, 3514, 3530, 3546, 3562,
		3579, 3595, 3611, 3627, 3643, 3659, 3675, 3691, 3708, 3724, 3740, 3756,
		3772, 3788, 3804, 3820, 3837, 3853, 3869, 3885, 3901, 3917, 3933, 3949,
		3966, 3982, 3998, 4014, 4030, 4046, 4062, 4078, 4095, 0
};

const uint16_t SineWave[256] = { 3771, 3798, 3824, 3848, 3871, 3894, 3915, 3935,
		3954, 3972, 3989, 4004, 4018, 4031, 4043, 4054, 4064, 4072, 4079, 4085,
		4089, 4093, 4094, 4095, 4094, 4093, 4091, 4087, 4082, 4076, 4068, 4059,
		4049, 4038, 4025, 4012, 3997, 3981, 3963, 3945, 3925, 3905, 3883, 3860,
		3836, 3811, 3785, 3758, 3730, 3701, 3670, 3639, 3607, 3574, 3540, 3505,
		3469, 3433, 3395, 3357, 3318, 3278, 3238, 3196, 3155, 3112, 3069, 3025,
		2980, 2935, 2890, 2844, 2797, 2750, 2703, 2655, 2607, 2558, 2509, 2460,
		2411, 2361, 2311, 2262, 2212, 2161, 2111, 2061, 2011, 1960, 1910, 1860,
		1810, 1760, 1711, 1661, 1612, 1563, 1514, 1466, 1418, 1370, 1323, 1276,
		1230, 1184, 1139, 1094, 1050, 1006, 963, 921, 879, 838, 798, 759, 720,
		682, 645, 609, 574, 539, 506, 473, 441, 411, 381, 352, 325, 298, 272,
		248, 225, 202, 181, 161, 142, 124, 107, 92, 78, 65, 53, 42, 32, 24, 17,
		11, 7, 3, 1, 0, 1, 2, 5, 9, 14, 20, 28, 37, 47, 58, 71, 84, 99, 115,
		133, 151, 171, 191, 213, 236, 260, 285, 311, 338, 366, 395, 426, 457,
		489, 522, 556, 591, 627, 663, 701, 739, 778, 818, 858, 900, 941, 984,
		1027, 1071, 1116, 1161, 1206, 1252, 1299, 1346, 1393, 1441, 1489, 1538,
		1587, 1636, 1685, 1735, 1785, 1834, 1884, 1935, 1985, 2035, 2085, 2136,
		2186, 2236, 2286, 2336, 2385, 2435, 2484, 2533, 2582, 2630, 2678, 2726,
		2773, 2820, 2866, 2912, 2957, 3002, 3046, 3090, 3133, 3175, 3217, 3258,
		3298, 3337, 3376, 3414, 3451, 3487, 3522, 3557, 3590, 3623, 3655, 3685,
		3715, 3744 };

const uint16_t TriangleWave[256] = { 32, 64, 96, 128, 160, 192, 224, 256, 288,
		320, 352, 384, 416, 448, 480, 512, 544, 576, 608, 640, 672, 704, 736,
		768, 800, 832, 864, 896, 928, 960, 992, 1024, 1056, 1088, 1120, 1152,
		1184, 1216, 1248, 1280, 1312, 1344, 1376, 1408, 1440, 1472, 1504, 1536,
		1568, 1600, 1632, 1664, 1696, 1728, 1760, 1792, 1824, 1856, 1888, 1920,
		1952, 1984, 2016, 2048, 2079, 2111, 2143, 2175, 2207, 2239, 2271, 2303,
		2335, 2367, 2399, 2431, 2463, 2495, 2527, 2559, 2591, 2623, 2655, 2687,
		2719, 2751, 2783, 2815, 2847, 2879, 2911, 2943, 2975, 3007, 3039, 3071,
		3103, 3135, 3167, 3199, 3231, 3263, 3295, 3327, 3359, 3391, 3423, 3455,
		3487, 3519, 3551, 3583, 3615, 3647, 3679, 3711, 3743, 3775, 3807, 3839,
		3871, 3903, 3935, 3967, 3999, 4031, 4063, 4095, 4063, 4031, 3999, 3967,
		3935, 3903, 3871, 3839, 3807, 3775, 3743, 3711, 3679, 3647, 3615, 3583,
		3551, 3519, 3487, 3455, 3423, 3391, 3359, 3327, 3295, 3263, 3231, 3199,
		3167, 3135, 3103, 3071, 3039, 3007, 2975, 2943, 2911, 2879, 2847, 2815,
		2783, 2751, 2719, 2687, 2655, 2623, 2591, 2559, 2527, 2495, 2463, 2431,
		2399, 2367, 2335, 2303, 2271, 2239, 2207, 2175, 2143, 2111, 2079, 2048,
		2016, 1984, 1952, 1920, 1888, 1856, 1824, 1792, 1760, 1728, 1696, 1664,
		1632, 1600, 1568, 1536, 1504, 1472, 1440, 1408, 1376, 1344, 1312, 1280,
		1248, 1216, 1184, 1152, 1120, 1088, 1056, 1024, 992, 960, 928, 896, 864,
		832, 800, 768, 736, 704, 672, 640, 608, 576, 544, 512, 480, 448, 416,
		384, 352, 320, 288, 256, 224, 192, 160, 128, 96, 64, 32, 0 };

// Encoder
#define T_ENC1           GPIO_Pin_8     // TIM1_channel1 PA8
#define T_ENC2           GPIO_Pin_9     // TIM1_channel2 PA9
volatile int16_t encVal = 0;            // final encoder value
volatile uint16_t last_digit = 0;       // for decode function
volatile uint16_t lastPeriod = 0;             // for keeping track of period changes
//volatile uint16_t PERIOD = TIM6_PERIOD / 2;    // start point for TIM6 ARR
volatile uint16_t PERIOD = 1850;                 // start point for TIM6 ARR 100Hz

//__IO uint16_t CC2Value = 0;         // For timer 2
//__IO uint16_t DutyCycle = 0;
//__IO uint32_t Frequency = 0;
//__IO uint16_t cc_count = 0;

// for flash write
//uint32_t FLASH_address = 0x08007C00; // sector 15 page 63 start address
//uint32_t STATE_address = 0x08007D00;
//uint32_t PERIOD_address = 0x08007D04;
//uint32_t FLASH_vals [2] = {0,0};        // STATE first, PERIOD second

Debouncer pB;     // set up debounce struct for portB

uint16_t ITOA = 0;
uint8_t Counter = 0;                      // for systick
uint16_t press_count = 0;
char array[10] = {0,0,0,0,0,0,0,0,0,0};
char dArray[10] = {0,0,0,0,0,0,0,0,0,0};
uint16_t digit = 0;
bool button_flag = false;
bool dFlag = false;
bool start_flag = true;

typedef enum {Sine = 1, Square, Triangle, Saw} State;
State stype = Sine;                                     // start with sine wave

///////////////// functions /////////////////////

//void
//TIM14_Config(void) {
//
//	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
//	NVIC_InitTypeDef  NVIC_InitStructure;
//
//	// TIM14 clock enable
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);
//
//	// Time base configuration
//	TIM_TimeBaseStructure.TIM_Period = 11999;
//	TIM_TimeBaseStructure.TIM_Prescaler = 1;
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//
//	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseStructure);
//
//	// TIM Interrupts enable
//	TIM_ITConfig(TIM14, TIM_IT_Update, ENABLE);
//
//	// Enable the TIM14 global Interrupt
//	NVIC_InitStructure.NVIC_IRQChannel = TIM14_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	TIM_Cmd(TIM14, ENABLE);
//}
//void
//TIM14_IRQHandler(void) {
//
//	TIM_ClearITPendingBit(TIM14, TIM_IT_Update);
//	if(dFlag){
//		debug2Low;
//		dFlag = false;
//	}else{
//		debug2High;
//		dFlag = true;
//	}
//}
void
TIM1_Config(void) {

    // configured for encoder on PA8 PA9
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

	// TIM1 clock enable
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	// GPIOA Clocks enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	// GPIOA Configuration: Tim1Channel1 as alternate function push-pull
	GPIO_InitStructure.GPIO_Pin = T_ENC1 | T_ENC2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;  // 2Mhz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);

	// Time base configuration
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI1, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

	TIM_Cmd(TIM1, ENABLE);
}
//void
//TIM2_Config(void) {
//
//	GPIO_InitTypeDef GPIO_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_ICInitTypeDef TIM_ICInitStructure;
//
//	/* TIM2 clock enable */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
//
//	/* GPIOA clock enable */
//	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
//
//	/* TIM2 chennel2 configuration : PA.01 */
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	/* Connect TIM pin to AF2 */
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2);
//
//	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
//	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
//	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
//	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//	TIM_ICInitStructure.TIM_ICFilter = 0x11;
//
//	TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);
//
//	/* Select the TIM2 Input Trigger: TI2FP2 */
//	TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
//
//	/* Select the slave Mode: Reset Mode */
//	TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
//	TIM_SelectMasterSlaveMode(TIM2, TIM_MasterSlaveMode_Enable);
//
//	/* TIM enable counter */
//	TIM_Cmd(TIM2, ENABLE);
//
//	/* Enable the CC2 Interrupt Request */
//	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
//
//	/* Enable the TIM2 global Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
//void
//TIM2_IRQHandler(void) {
//
//	RCC_ClocksTypeDef RCC_Clocks;
//	RCC_GetClocksFreq(&RCC_Clocks);
//
//	// Clear TIM2 Capture compare interrupt pending bit
//	TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
//
//	CC1Value = TIM_GetCapture1(TIM2);
//	CC2Value = TIM_GetCapture2(TIM2);
//	Frequency = RCC_Clocks.HCLK_Frequency / CC2Value;
//}
void
TIM6_Config(void) {

	// Timer frequency = 48Mhz / ((prescaler + 1) * (timer period + 1))
	// Timer frequency = 48Mhz / ((PSC+1) * (ARR+1))
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// TIM6 Periph clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	// Initialize to default configuration
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Period = TIM6_PERIOD;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	// TIM6 TRGO selection
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

	// TIM6 enable counter
	TIM_Cmd(TIM6, ENABLE);
}
static void
GPIO_Config(void) {

	GPIO_InitTypeDef  GPIO_InitStructureC;
	GPIO_InitTypeDef  GPIO_InitStructureB;
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;

	// GPIOB Periph clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	// GPIOC Periph clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

	//Enable SYSCFG clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	// Configure PC8 and PC9 in output push pull mode
	GPIO_InitStructureC.GPIO_Pin = debugLed | debugLed2;
	GPIO_InitStructureC.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructureC.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructureC.GPIO_Speed = GPIO_Speed_Level_3;
	GPIO_InitStructureC.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructureC);

	// Configure PB6 pin as input pulled up for the button
	GPIO_InitStructureB.GPIO_Pin = button;
	GPIO_InitStructureB.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructureB.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructureB);
	ButtonDebounceInit(&pB, button);                // instantiate the button

	// Connect EXTI6 Line to PB6 pin
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource6);

	// Configure EXTI6 line
	EXTI_InitStructure.EXTI_Line = EXTI_Line6;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	// Enable and set EXTI6 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_15_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0x03;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
void
EXTI4_15_IRQHandler(void) {

	if (EXTI_GetITStatus(EXTI_Line6) != RESET) {
		button_flag = true;
		// Clear the EXTI line 6 pending bit
		EXTI_ClearITPendingBit(EXTI_Line6);
	}
}
static void
SysTick_Init(void) {

	// Configure a SysTick Base time to 10 ms.
	SysTick_Config(1000u); // Setup SysTick Timer
	if (SysTick_Config(SystemCoreClock / 100)) {

		while (1);        // Capture error
	}

	NVIC_SetPriority(SysTick_IRQn, 0x00); // Configure the SysTick handler priority
}
void
SysTick_Handler(void) {

	if (Counter < 10) {
		Counter++;
		debugLow;  // PC8 is blue led

	} else {
		Counter = 0;
		debugHigh;
	}
}
void
DAC_Config(void) {

	GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef   DAC_InitStructure;

	// DAC Periph clock enable
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);

	// GPIOA clock enable
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

	//Configure PA.04 (DAC_OUT1) as analog
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// DAC channel1 Configuration
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T6_TRGO; // set the trigger source
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable; // enable the DAC output buffer
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_LFSRUnmask_TriangleAmplitude = DAC_TriangleAmplitude_4095;

	// DAC Channel1 Init
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	// Enable DAC Channel1: Once the DAC channel1 is enabled, PA.04 is
	// automatically connected to the DAC converter.
	DAC_Cmd(DAC_Channel_1, ENABLE);

	// Enable DMA for DAC Channel1
	DAC_DMACmd(DAC_Channel_1, ENABLE);
}
void
DMA_Config(const uint16_t *baseADDR) {

  DMA_InitTypeDef   DMA_InitStructure;

	// DMA1 clock enable (to be used with DAC)
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	// DMA1 channel3 Configuration
	DMA_DeInit(DMA1_Channel3);
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_ADDRESS;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)baseADDR;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 256;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel3, &DMA_InitStructure);

	// Enable DMA1 Channel3
	DMA_Cmd(DMA1_Channel3, ENABLE);
}
int16_t
decode(uint32_t count) {
  /*
   * decodes the encoder position
   * @ count: the timer count
   * returns: the decoded position to be added to the final encoder count
   */

	uint16_t digit = count & 0x0f;  // get the last byte

	if (digit == last_digit) return 0;

	if (digit > last_digit) {
		last_digit = digit;
		return 25;
	}
	else {
		last_digit = digit;
		return -25;
	}
}
int
itoa(int val, char *str) {

	// This itoa handles negative numbers
	int i = 0;
	if (val < 0) {
		str[0] = '-';
		return 1 + itoa(-val, str + 1);
	}
	if (val / 10) {
		i = itoa(val / 10, str);
	}
	str[i] = val % 10 + '0';
	str[++i] = '\0';

	return i;
}
uint16_t
figFreq(uint16_t val) {
  /*
   * @ val: the timer period
   * returns: the frequency of the wave form in Hertz
   */

	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);

	uint32_t freq = 0;
	uint32_t t6freq = RCC_Clocks.HCLK_Frequency / (val - 1);
	freq =  t6freq / numOfSamples;
	return freq;
}
void
plot_screen(const uint16_t *wave, uint16_t color, State state) {
  /*
   * plots the wave forms to the string using the wave table data
   * scaled to fit the LCD
   * @ wave: pointer to wave table array
   * @ color: the color to display the wave in
   *
   */

  uint16_t i, j;
  float y_scale_val = 0;
  float x_scale_val = 0;
  uint16_t xplot = 0;
  uint16_t yplot = 0;

  for (j = 0; j < 3; j++) {
      for (i = 0; i < 255; i++) {
          x_scale_val = (255 - (float) i) / 255;
          xplot = (x_scale_val * 106);
          y_scale_val = (4095 - (float) wave[i]) / 4095;
          yplot = 234 - (y_scale_val * 130);

          switch (j){
            case 0:
              setPixel (xplot, yplot, color);
              break;
            case 1:
              setPixel (xplot + 106, yplot, color);
              break;
            case 2:
              setPixel (xplot + 212, yplot, color);
              break;
            default:
              j = 0;
            }
        }
    }
  switch (state) {
    case Sine:
      break;
    case Square:
      LCD_DrawLine (53, 104, 130, LCD_DIR_VERTICAL);
      LCD_DrawLine (106, 104, 130, LCD_DIR_VERTICAL);
      LCD_DrawLine (159, 104, 130, LCD_DIR_VERTICAL);
      LCD_DrawLine (212, 104, 130, LCD_DIR_VERTICAL);
      LCD_DrawLine (265, 104, 130, LCD_DIR_VERTICAL);
      break;
    case Triangle:
      break;
    case Saw:
      LCD_DrawLine(106, 104, 130, LCD_DIR_VERTICAL);
      LCD_DrawLine(212, 104, 130, LCD_DIR_VERTICAL);
      break;
  }

  LCD_SetTextColor (LCD_COLOR_RED);
  LCD_DrawRect (0, 100, 318, 139);
  LCD_SetTextColor (LCD_COLOR_GREEN);
}
void
wave_sine(void) {

	stype = Sine;
	LCD_Clear_Some(1, 101, 317, 238, LCD_COLOR_BLACK);
	plot_screen(SineWave, LCD_COLOR_GREEN, Sine);
	DMA_Config(SineWave);
}
void
wave_square(void) {

	stype = Square;
	LCD_Clear_Some(1, 101, 317, 238, LCD_COLOR_BLACK);
	plot_screen(SquareWave, LCD_COLOR_GREEN, Square);
	DMA_Config(SquareWave);
}
void
wave_triangle(void) {

	stype = Triangle;
	LCD_Clear_Some(1, 101, 317, 238, LCD_COLOR_BLACK);
	plot_screen(TriangleWave, LCD_COLOR_GREEN, Triangle);
	DMA_Config(TriangleWave);
}
void
wave_saw(void) {

	stype = Saw;
	LCD_Clear_Some(1, 101, 317, 238, LCD_COLOR_BLACK);
	plot_screen(SawtoothWave, LCD_COLOR_GREEN, Saw);
	DMA_Config(SawtoothWave);
}
void
clear_array(char *a) {

	uint8_t len;
	for (len = 0; len < 10; len++) {
		a[len] = 0;
	}
}
uint8_t
make_array(uint16_t number, char *a) {
  /*
   * Builds the seven segment number string
   * @ number: number to be put in the string
   * @ a: pointer to empty array
   * returns: the length of the string for use
   * with drawStringSeven function
   */

	uint16_t temp = number;
	int8_t count = 0;
	int8_t rCount = 0;

	// get the number of digits
	while (temp > 0) {
		count++;
		temp = temp / 10;
	}

	rCount = count;
	count -= 1;
	while (count >= 0) {
	    a[count] = number % 10;
	    number = number / 10;
	    if (count == 0) {
	        break;
	    }else
	        count--;
	}
	return rCount;
}

//GNU ARM Plugin stuff
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


int main(int argc, char* argv[]) {

	SysTick_Init();
//	TIM14_Config();
	TIM1_Config();      // encoder
//	TIM2_Config();    // for DAC frequency computation
	TIM6_Config();      // for DAC timing
	GPIO_Config();
	SPI_Config();
	DMA_Config(SineWave);
	DAC_Config();
	hx8347g_Init();
	FLASH_SetLatency(FLASH_Latency_1);

	LCD_Clear(LCD_COLOR_BLACK);
	LCD_SetColors(LCD_COLOR_GREEN, LCD_COLOR_BLACK);

	drawString5_7(5, 5, "Retrieving wave and frequency data");
//	uint32_t STATE = getFlashData(STATE_address);
//	if (STATE < 1 || STATE > 4) {
//	    STATE = 1;
//	}
//	stype = STATE;
//	uint32_t period = getFlashData(PERIOD_address);
//	PERIOD = period;
//	if (PERIOD > 9036) {
//	    PERIOD = 9036;                     // don't go lower than 20Hz
//	}
//	else if (PERIOD < 100) {               // or greater than 3Khz
//	    PERIOD = 100;
//	}
	TIM_SetAutoreload(TIM6, PERIOD);       // last saved frequency
	drawString5_7(5, 15, "STATE = ");
	itoa(stype, array);
	drawString5_7(50,15, array);
	drawString5_7(5, 25, "FREQ = ");
	itoa(PERIOD, array);
	drawString5_7(45, 25, array);

	longDelay(50);
	LCD_flipOrientation(DISABLE);
	LCD_Clear(LCD_COLOR_BLACK);
	LCD_flipOrientation(ENABLE);
	LCD_SetTextColor(LCD_COLOR_GREEN);

	while (1) {

		encVal = decode(TIM1->CNT);
		PERIOD += encVal;
		if (PERIOD != lastPeriod) {

			TIM_SetAutoreload(TIM6, PERIOD);

			digit = figFreq(PERIOD);
			ITOA = itoa(PERIOD, array);
			LCD_Clear_Some(0, 30, 200, 100, LCD_COLOR_BLACK);
			drawString8_12(5, 85, "Period = ");                // Timer reload frequency
			drawString8_12(75,85, array);
			uint8_t len = make_array(digit, dArray);           // Frequency in Hz
			drawStringSeven(5, 30, len, dArray);
			drawString11_16(35 * len, 65, "Hz");
			lastPeriod = PERIOD;
			clear_array(array);
			clear_array(dArray);
//			FLASH_vals[0] = stype;
//			FLASH_vals[1] = PERIOD;
//			writeFlash(STATE_address, FLASH_vals, 2);
		}

		if (button_flag || start_flag) {
		  button_flag = false;
		  ButtonProcess(&pB, GPIO_ReadInputData(GPIOB));
			if (ButtonPressed(&pB, button) || start_flag) {
				press_count++;
				TIM_Cmd(TIM6, DISABLE);

				switch (press_count) {
				case Sine:
//					debug2High;
					LCD_Clear_Some(5, 0, 170, 30, LCD_COLOR_BLACK);
					drawString11_16(5, 10, "Sine Wave");
					wave_sine();
					break;
				case Square:
//					debug2High;
					LCD_Clear_Some(5, 0, 170, 30, LCD_COLOR_BLACK);
					drawString11_16(5, 10, "Square Wave");
					wave_square();
					break;
				case Triangle:
//					debug2High;
					LCD_Clear_Some(5, 0, 170, 30, LCD_COLOR_BLACK);
					drawString11_16(5, 10, "Triangle Wave");
					wave_triangle();
					break;
				case Saw:
//					debug2High;
					LCD_Clear_Some(5, 0, 170, 30, LCD_COLOR_BLACK);
					drawString11_16(5, 10, "Saw Wave");
					wave_saw();
					break;
				default:
					debug2Low;
				}

				TIM_Cmd(TIM6, ENABLE);
				if (press_count >= 4) {
					press_count = 0;
				}
//				FLASH_vals[0] = stype;
//				FLASH_vals[1] = PERIOD;
//				writeFlash(STATE_address, FLASH_vals, 2);
				start_flag = false;
			}
		}
	}
}


#pragma GCC diagnostic pop

