/*
 * a7_running_light_8bit.h
 *
 * Created: 10-May-21 16:14:46
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A7_RUNNING_LIGHT_8BIT_H_
#define A7_RUNNING_LIGHT_8BIT_H_

#ifndef F_CPU 
#define F_CPU 16000000UL 
#endif
#include <util/delay.h>
#include "bit_macros.h"

#define DELAY 100
#define TURN_ON_DELAY_OFF_INCR(port, pin) ({\
	(port) = (1 << (pin)++);\
	_delay_ms(DELAY);\
})
#define TURN_ON_DELAY_OFF_DECR(port, pin) ({\
	(port) = (1 << (pin)--);\
	_delay_ms(DELAY);\
})

uint8_t b = 1;
uint8_t d = 4;

inline void runningLightSetup()
{
	DDRB = (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);	// Set pin B1, B2, B3, B4 and
	DDRD = (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);	// D4, D5, D6 and D7 as output.
}

inline static void runningLightLoop()
{
	while (d != 8)
		TURN_ON_DELAY_OFF_INCR(PORTD, d);
	d--;
	PORTD = 0;
	
	while (b != 5)
		TURN_ON_DELAY_OFF_INCR(PORTB, b);
	b -= 2;
	
	while (b)
		TURN_ON_DELAY_OFF_DECR(PORTB, b);
	b++;
	PORTB = 0;
	
	while (d != 3)
		TURN_ON_DELAY_OFF_DECR(PORTD, d);
	d += 2;
}

inline static void naiveRunningLightLoop()
{
	PORTD = (1 << PORTD4);
	_delay_ms(DELAY);
	PORTD = (1 << PORTD5);
	_delay_ms(DELAY);
	PORTD = (1 << PORTD6);
	_delay_ms(DELAY);
	PORTD = (1 << PORTD7);
	_delay_ms(DELAY);
	PORTD = 0;
	
	PORTB = (1 << PORTB1);
	_delay_ms(DELAY);
	PORTB = (1 << PORTB2);
	_delay_ms(DELAY);
	PORTB = (1 << PORTB3);
	_delay_ms(DELAY);
	PORTB = (1 << PORTB4);
	_delay_ms(DELAY);
	PORTB = (1 << PORTB3);
	_delay_ms(DELAY);
	PORTB = (1 << PORTB2);
	_delay_ms(DELAY);
	PORTB = (1 << PORTB1);
	_delay_ms(DELAY);
	PORTB = 0;
	
	PORTD = (1 << PORTD7);
	_delay_ms(DELAY);
	PORTD = (1 << PORTD6);
	_delay_ms(DELAY);
	PORTD = (1 << PORTD5);
	_delay_ms(DELAY);
}

#endif /* A7_RUNNING_LIGHT_8BIT_H_ */