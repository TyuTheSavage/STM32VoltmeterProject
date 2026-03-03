// ------------ adcTask.h ---------------
//        Author: Macovei Tudor
//       Project: _Preh_Voltmeter
//   Functionality: Header of adcTask.c
// --------------------------------------

#ifndef ADC_TASK_H
#define ADC_TASK_H

// Includes
#include "rte.h"

// Constants
#define referenceVoltage (3.3f)
#define resolutionADC (4095.0f)

// Function Declarations
void readVoltsHandler(void *argument);

#endif
