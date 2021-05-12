/*
 * a1_traffic_light.h
 *
 * Created: 10-May-21 15:49:23
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A1_TRAFFIC_LIGHT_H_
#define A1_TRAFFIC_LIGHT_H_

#define LED1 PORTB2
#define LED2 PORTB3
#define LED3 PORTB4

#define F_CPU 16000000UL
#include <util/delay.h>
#include "bit_macros.h"

// 
inline void trafficLightSetup() 
{
	DDRB = (1 << DDB2) | (1 << DDB3) | (1 << DDB4);	// Set pin B2, B3 and B4 as output
}

// '_delay_ms' is static but used in inline function 'trafficLightLoop' which is not static
inline static void trafficLightLoop() 
{
	SET_BIT(PORTB, LED1);	// LEDs 1 and LED 2 on for 200 ms
	SET_BIT(PORTB, LED2);
	_delay_ms(200);
	CLEAR_BIT(PORTB, LED1);
	CLEAR_BIT(PORTB, LED2);
	
	SET_BIT(PORTB, LED3);	// LED 3 on for 1000 ms
	_delay_ms(1000);
	CLEAR_BIT(PORTB, LED3);
	
	SET_BIT(PORTB, LED2);	// LED 2 on for 200 ms
	_delay_ms(200);
	CLEAR_BIT(PORTB, LED2);
	
	SET_BIT(PORTB, LED1);	// LED 1 on for 1000 ms
	_delay_ms(1000);
	CLEAR_BIT(PORTB, LED1);
}

#endif /* A1_TRAFFIC_LIGHT_H_ */