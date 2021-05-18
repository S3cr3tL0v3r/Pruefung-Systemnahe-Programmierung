/*
 * a1_traffic_light.h
 *
 * Here a traffic light is simulated, which changes its traffic light switching after certain time intervals
 *
 * Created: 10-May-21 15:49:23
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A1_TRAFFIC_LIGHT_H_
#define A1_TRAFFIC_LIGHT_H_

#define LED1 PORTB2
#define LED2 PORTB3
#define LED3 PORTB4

#include <util/delay.h>
#include "bit_macros.h"

/*
 * Config output pins.
 */
inline void trafficLightSetup() 
{
	DDRB = (1 << DDB2) | (1 << DDB3) | (1 << DDB4);	// Set pin B2, B3 and B4 as output
}

/*
 * Traffic light logic with required LED on times.
 */
inline static void trafficLightLoop() 
{
	// RED YELLOW
	SET_BIT(PORTB, LED1);		// LEDs 1 and LED 2 on for 200 ms
	SET_BIT(PORTB, LED2);
	_delay_ms(200);
	CLEAR_BIT(PORTB, LED1);
	CLEAR_BIT(PORTB, LED2);
	
	// GREEN
	SET_BIT(PORTB, LED3);		// LED 3 on for 1000 ms
	_delay_ms(1000);
	CLEAR_BIT(PORTB, LED3);
	
	// YELLOW
	SET_BIT(PORTB, LED2);		// LED 2 on for 200 ms
	_delay_ms(200);
	CLEAR_BIT(PORTB, LED2);
	
	// RED
	SET_BIT(PORTB, LED1);		// LED 1 on for 1000 ms
	_delay_ms(1000);			// Don't turn off, as immediately switched on again in next stage.
}

#endif /* A1_TRAFFIC_LIGHT_H_ */
