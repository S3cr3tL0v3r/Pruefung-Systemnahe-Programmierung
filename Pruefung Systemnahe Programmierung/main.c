/************************************************************************/
/* Pruefung Systemnahe Programmierung                                   */
/************************************************************************/

/*
 * main.c
 *
 * This program provides all other programs and tasks. All header programs can be called up via this. 
 * In addition, an endless loop is provided here which is necessary for many programs.
 *
 * Created: 10-May-21 15:47:46
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>

//#include "include/a1_traffic_light.h"
//#include "include/a2_buttons_LED_polling.h"
//#include "include/a3_buttons_led_interrupts.h"
//#include "include/a4_summer.h"
//#include "include/a5_dim_LED.h"
//#include "include/a6_read_analog_2chan.h"
#include "include/a7_running_light_8bit.h"

int main(void)
{
    /* setup function */
	//trafficLightSetup();
	//buttonsLEDPollingSetup();
	//buttonsLEDInterruptSetup();
	//summerSetup();
	//dimLEDSetup();
	//readAnalog2chanSetup();
	runningLightSetup(100);
	
    while (1) 
    {
		/* loop function */
		//trafficLightLoop();
		//buttonsLEDPollingLoop();
		//readAnalog2chanLoop();
		runningLightLoop();
    }
}
