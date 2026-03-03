// -------------------- customOS.c ------------------------
//                 Author: Macovei Tudor
//               Project: _Preh_Voltmeter
//           Functionality: Header of customOS.h
// --------------------------------------------------------

// Includes
#include <stdint.h>
#include "stm32f0xx.h"

// Function Declarations
void delayMe(uint8_t);
void initOS(void);
void runOS(void);
void SysTick_Handler(void);
