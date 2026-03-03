// ------------ displayTask.c ---------------
//          Author: Macovei Tudor
//         Project: _Preh_Voltmeter
//   Functionality: OS#2 Send to LCD via SPI
// ------------------------------------------

// Includes
#include "displayTask.h"

// Imported functions
extern void pleaseDrawLineRTE(uint8_t *buff, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);
extern void pleaseDrawStringRTE(uint8_t *buff, uint8_t x, uint8_t line, uint8_t *c);
extern void testLineSpeed(void);
extern void pleaseOscRTE();

// Imported functions
extern char voltsString[8];
extern float voltsRead;

// Functions
// Function that animates 0.00V reading
void animationNoVoltage(void)
{
    static int toggle = 0;
    static int taskTime = 0;

    taskTime += 20;
    if (taskTime >= 1000)
    {
        toggle = !toggle;
        taskTime = 0;
    }

    if (toggle)
    {
    	pleaseDrawLineRTE(buffer, 42, 30, 80, 15, 1);
    	pleaseDrawLineRTE(buffer, 42, 31, 80, 16, 1);
        pleaseDrawStringRTE(buffer, 0, 7, (uint8_t* ) "EMPTY OR DISCONNECTED");
    }
    else
    {
    	pleaseDrawLineRTE(buffer, 42, 30, 84, 30, 1);
    	pleaseDrawLineRTE(buffer, 42, 31, 84, 31, 1);
        pleaseDrawStringRTE(buffer, 3, 7, (uint8_t* ) "CHECK PA1 CONNECTION");
    }
}

// Function for the needle
void drawNeedle(float voltsRead)
{
	// VU meter numerical values
	pleaseDrawStringRTE(buffer, 2, 5, (uint8_t* ) "0.0");
	if(voltsRead)
	{
		pleaseDrawStringRTE(buffer, 20, 2, (uint8_t* ) "0.8");
		pleaseDrawStringRTE(buffer, 56, 0, (uint8_t* ) "1.6");
		pleaseDrawStringRTE(buffer, 90, 2, (uint8_t* ) "2.5");
		pleaseDrawStringRTE(buffer, 105, 5, (uint8_t* ) "3.3");
	}

	// Origin of needle
    int centerX = 63;
    int centerY = 50;
    float radius = 40.0f;

    // Angle limits and current angle calculation
    float angle_min = 190.0f * (M_PI/180.0f);
    float angle_max = 350.0f * (M_PI/180.0f);
    float t = voltsRead / 3.3f;
    float angle = angle_min + t * (angle_max - angle_min);

    // Calculation of raw location of needle
    int needleX = centerX + (int)(radius * cosf(angle) + 0.5f);
    int needleY = centerY + (int)(radius * sinf(angle) + 0.5f);

    // Send to screen (2x for thicker appearance)
    pleaseDrawLineRTE(buffer, centerX, centerY, needleX, needleY, 1);
    pleaseDrawLineRTE(buffer, centerX-1, centerY-1, needleX-1, needleY-1, 1);

    // testLineSpeed();
}

// Main OS function
void screenHandler(void *argument)
{
	//Screen Display
	//pleaseLCDRTE();
	pleaseOscRTE();

}
