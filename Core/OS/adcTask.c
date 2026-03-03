// -------------- adcTask.c -----------------
//          Author: Macovei Tudor
//         Project: _Preh_Voltmeter
//   Functionality: OS#1 read ADC + prepare
// ------------------------------------------


// Includes
#include "adcTask.h"

// Imported functions
extern void pleaseADCRTE();

// Main OS function
void readVoltsHandler(void *argument)
{
	// ADC Interrogation and value conversion
	pleaseADCRTE();

	// 20ms delay <=> 50Hz (to match screen)
}
