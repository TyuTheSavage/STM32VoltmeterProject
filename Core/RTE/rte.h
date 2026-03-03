// ----------------------- rte.h --------------------------
//                 Author: Macovei Tudor
//               Project: _Preh_Voltmeter
//            Functionality: Header of rte.c
// --------------------------------------------------------

// Includes
#include "main.h"
#include "stm32f0xx_hal.h"
#include "customOS.h"
#include "displayTask.h"
#include "adcTask.h"
#include "lcd_st7565.h"
#include "lcd_st7565_pinconf.h"
#include "font.h"
#include <math.h>

//Defines for ports
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define SPICD_Pin GPIO_PIN_7
#define SPICD_GPIO_Port GPIOC
#define BL_Pin GPIO_PIN_8
#define BL_GPIO_Port GPIOA
#define SPIRST_Pin GPIO_PIN_9
#define SPIRST_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SPICS_Pin GPIO_PIN_6
#define SPICS_GPIO_Port GPIOB
#define BUF_LEN 128

// Function Declarations
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void MX_ADC_Init(void);
void MX_SPI1_Init(void);
void initHandler(void *argument);
void Error_Handler(void);
void pleaseInitRTE(void);
void pleaseADCRTE(void);
void animationNoVoltage(void);
void drawNeedle(float);
void pleaseLCDRTE(void);
void pleaseDrawStringRTE(uint8_t *buff, uint8_t x, uint8_t line, uint8_t *c);
void pleaseDrawLineRTE(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
void pleaseInitLCDRTE(void);
void pleaseTestRegisterRTE(int);
void pleaseInitADCRTE(uint16_t* result);
void doom_style_drawline(uint8_t *buff, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
void testLineSpeed(void);
void pleaseOscRTE(void);
int rawADCtoPixel(uint16_t value);
