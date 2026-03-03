// ----------------------- rte.c --------------------------
//                 Author: Macovei Tudor
//               Project: _Preh_Voltmeter
//  Functionality: Layer between hardware and application
// --------------------------------------------------------

// Ignored warnings
#pragma GCC diagnostic ignored "-Wformat-truncation"  // String creation - cannot overflow
#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
#pragma GCC diagnostic ignored "-Wbuiltin-declaration-mismatch"

// Includes
#include "rte.h"

// Variables
// Init
ADC_HandleTypeDef hadc;
SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart2;

// OS


// Other
char voltsString[8];
float voltsRead = 0.00f;
uint16_t rawValue = 0;
extern volatile uint32_t myTicks;
uint16_t adcBuffer[BUF_LEN];
uint16_t displayBuffer[BUF_LEN];
uint8_t samplePos = 0;
uint8_t bufferReady = 0;

// Functions
// Default
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  HAL_GPIO_WritePin(SPICD_GPIO_Port, SPICD_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(GPIOA, BL_Pin|SPIRST_Pin, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(SPICS_GPIO_Port, SPICS_Pin, GPIO_PIN_RESET);

  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SPICD_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPICD_GPIO_Port, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = BL_Pin|SPIRST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = SPICS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPICS_GPIO_Port, &GPIO_InitStruct);

  // Clock enable channel A
  // RCC->AHBENR |= (1 << 17);

  // Mode 00 - input | 01 - output
  GPIOA->MODER   |=  (1 << 20);
  GPIOA->MODER   &= ~(1 << 21);

  // 0 - Push-pull | 1 - Open-drain
  GPIOA->OTYPER  &= ~(1 << 10);

  // x0 - low | 01 - med | 11 - high
  GPIOA->OSPEEDR &= ~(1 << 20);

  // 00 - None | 01 - Pull-up | 10 - Pull-down | 11 - Reserved
  GPIOA->PUPDR &= ~(1 << 20) & ~(1 << 21);

  // 1x - high | 01 - low
  GPIOA->BSRR &= ~(1 << 10);
  GPIOA->BSRR |=  (1 << 26);
}

void MX_USART2_UART_Init(void)
{
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
}

void MX_ADC_Init(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}

void MX_SPI1_Init(void)
{
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 7;
  hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}


// Exported RTE Functions
// For adcTask
void pleaseADCRTE(void)
{
	// ADC Interrogation and value conversion
	pleaseInitADCRTE(&rawValue);
	if(rawValue < 10)
		rawValue = 0;
	voltsRead = (rawValue / resolutionADC) *referenceVoltage;

	// Separate float into 2 values + rounding
	int whole = (int)voltsRead;
	int frac = (int)((voltsRead - whole) * 100 + 0.5f);
	if (frac >= 100)
	{
	    whole += 1;
	    frac = 0;
	}

	// Concatenation of numbers
	snprintf(voltsString, sizeof(voltsString), "%d.%02dV", whole, frac);

	// Add value to samples
    adcBuffer[samplePos++] = rawValue;
    if(samplePos >= BUF_LEN) {
        samplePos = 0;
        // buffer full, copy for drawing (atomic/interrupt safe)
        __disable_irq();
        for(int i=0; i<BUF_LEN; ++i)
            displayBuffer[i] = adcBuffer[i];
        __enable_irq();
        bufferReady = 1;
    }


}


// For displayTask
void pleaseLCDRTE(void)
{
	//Screen preparing
	st7565_clear_buffer(buffer);

	// Screen information send
	//VU meter
	drawNeedle(voltsRead);

	if(voltsRead > 0.0f)
	{
		// Text and read values
		st7565_drawstring(buffer, 49, 7, (uint8_t *) voltsString);
		st7565_drawstring(buffer, 10, 7, (uint8_t *) "LIVE");
		if(voltsRead < 3.00f)
			st7565_drawstring(buffer, 87, 7, (uint8_t *) "SEVERE");
		else if(voltsRead < 3.10f)
			st7565_drawstring(buffer, 95, 7, (uint8_t *) "LOW");
		else if(voltsRead < 3.20f)
			st7565_drawstring(buffer, 87, 7, (uint8_t *) "MEDIUM");
		else
			st7565_drawstring(buffer, 98, 7, (uint8_t *) "OK");

		// Cassettes
		st7565_drawline(buffer, 0, 54, 127, 54, 1);
		st7565_drawline(buffer, 46, 54, 46, 63, 1);
		st7565_drawline(buffer, 80, 54, 80, 63, 1);

		// Write buffer
		st7565_write_buffer(buffer);
	}
	else
	{
		// Bottom text and line
		st7565_drawline(buffer, 0, 54, 127, 54, 1);

		// Main screen
		st7565_drawline(buffer, 0, 30, 42, 30, 1);
		st7565_drawline(buffer, 0, 31, 42, 31, 1);
		st7565_drawline(buffer, 84, 30, 127, 30, 1);
		st7565_drawline(buffer, 84, 31, 127, 31, 1);

		// Animation function
		animationNoVoltage();

		// Write buffer
		st7565_write_buffer(buffer);
	}
}
void pleaseOscRTE(void) {
    if(!bufferReady) return;
    bufferReady = 0;

    st7565_clear_buffer(buffer);
    int trigger = -1;
    uint16_t triggerLevel = 2050;
    for(int i=0; i<BUF_LEN-1; ++i) {
        if(displayBuffer[i] < triggerLevel && displayBuffer[i+1] >= triggerLevel) {
            trigger = i;
            break;
        }
    }
    int start = (trigger!=-1) ? trigger : 0;
    for(int i=0; i<BUF_LEN-1; ++i) {
        int idx0 = (start+i)%BUF_LEN, idx1 = (start+i+1)%BUF_LEN;
        int y0 = rawADCtoPixel(displayBuffer[idx0]);
        int y1 = rawADCtoPixel(displayBuffer[idx1]);
        pleaseDrawLineRTE(buffer, i, y0, i+1, y1, 1);
    }
    st7565_write_buffer(buffer);
}
int rawADCtoPixel(uint16_t value)
{
	int y = 63 - (value *64 /4095);
	if(y < 0)
		y = 0;
	if(y >= 64)
		y = 63;
	return y;
}

// Implemented functions to connect LCD to Task
void pleaseDrawStringRTE(uint8_t *buff, uint8_t x, uint8_t line, uint8_t *c)
{
	st7565_drawstring(buff, x, line, c);
}

void pleaseDrawLineRTE(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{
	st7565_drawline(buff, x0, y0, x1, y1, color);
}

void pleaseInitLCDRTE(void)
{
	st7565_init();
	st7565_backlight_enable();
	st7565_clear_screen();
}

void pleaseInitADCRTE(uint16_t *result)
{
    // Clocks
    RCC->AHBENR  |= (1 << 17);
    RCC->APB2ENR |= (1 << 9);

    // PA1 analog mode
    GPIOA->MODER |= (1 << 2) | (1 << 3);

    // Sample time fastest
    ADC1->SMPR |= (1 << 0);

    // Disable ADC if enabled and wait
    if (ADC1->CR & (1 << 0))
        ADC1->CR |= (1 << 1);
    while (ADC1->CR & (1 << 0));

    // Enable ADC and wait
    ADC1->CR |= (1 << 0);
    while (!(ADC1->ISR & (1 << 0)));
    ADC1->ISR |= (1 << 0);

    // Channel 1 for PA1
    ADC1->CHSELR = (1 << 1);

    // Start conversion and wait
    ADC1->CR |= (1 << 2);
    while (!(ADC1->ISR & (1 << 2)));

    // Result
    *result = ADC1->DR;
    ADC1->ISR |= (1 << 2);
}

void doom_style_drawline(uint8_t *buff, int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color)
{
    int16_t dx = abs(x1 - x0);
    int16_t dy = -abs(y1 - y0);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx + dy;
    int16_t e2;

    while (1) {
        st7565_setpixel(buff, x0, y0, color);

        if (x0 == x1 && y0 == y1) break;

        e2 = 2 * err;

        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }

        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void testLineSpeed()
{
	int regular = myTicks;
	for(int i = 0; i < 67; ++i)
		st7565_drawline(buffer, 0, i, 127, i, 1);
	regular = myTicks - regular;
	int doom = myTicks;
	for(int i = 0; i < 67; ++i)
		doom_style_drawline(buffer, 0, i, 127, i, 1);
	doom = myTicks - doom;
}

// For main
void pleaseInitRTE(void)
{
	HAL_Init();
	SystemClock_Config();
	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_ADC_Init();
	MX_SPI1_Init();
	pleaseInitLCDRTE();
	SysTick_Config(SystemCoreClock / 1000);
	initOS();
	runOS();
}
