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

#define DELAY _delay_ms(100)

inline void runningLightSetup() 
{
	/*DDRB = (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);	// Set pin B1, B2, B3, B4 and
	DDRD = (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);	// D4, D5, D6 and D7 as output.*/
	DDRB = 0b00011110;	// Set pin B1, B2, B3, B4 and
	DDRD = 0b11110000;	// D4, D5, D6 and D7 as output.
}

inline static void runningLightLoop()
{
	PORTB = (1 << PORTB4);
	DELAY;
	PORTB = (1 << PORTB3);
	DELAY;
	PORTB = (1 << PORTB2);
	DELAY;
	PORTB = (1 << PORTB1);
	DELAY;
	PORTB = 0;
	PORTD = (1 << PORTD7);
	DELAY;
	PORTD = (1 << PORTD6);
	DELAY;
	PORTD = (1 << PORTD5);
	DELAY;
	PORTD = (1 << PORTD4);
	DELAY;
	PORTD = (1 << PORTD5);
	DELAY;
	PORTD = (1 << PORTD6);
	DELAY;
	PORTD = (1 << PORTD7);
	DELAY;
	PORTD = 0;
	PORTB = (1 << PORTB1);
	DELAY;
	PORTB = (1 << PORTB2);
	DELAY;
	PORTB = (1 << PORTB3);
	DELAY;
}



#endif /* A7_RUNNING_LIGHT_8BIT_H_ */