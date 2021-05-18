/*
 * a7_running_light_8bit.h
 *
 * Depending on the input of the delay (variable delay) a running light of leds is started. 
 * Here the leds are switched on one after the other. The lighted led runs first in one direction and then again in the other direction.
 *
 * Created: 10-May-21 16:14:46
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A7_RUNNING_LIGHT_8BIT_H_
#define A7_RUNNING_LIGHT_8BIT_H_

#include <util/delay.h>
  
/*
 * Pin mapping
 *			   D  D  D  D  B  B  B  B  B  B  B  D  D  D
 *			   0  1  2  3  4  5  6  7  8  9 10 11 12 13
 */
int pins[] = { 4, 5, 6, 7, 1, 2, 3, 4, 3, 2, 1, 7, 6, 5 };
uint8_t pos = 0;
uint16_t del;

/*
 * Config running light output pins and specify delay.
 * @param	delay	LED on time in milliseconds
 */
inline void runningLightSetup(uint16_t delay)
{
	DDRB |= (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);	// Set pin B1, B2, B3, B4 and
	DDRD |= (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);	// D4, D5, D6 and D7 as output.
	
	del = delay;
}

/*
 * Single running light step. Recommended use inside a loop.
 * Then walks through pin mapping array and switches selected LED on and off.
 */
inline static void runningLightLoop()
{
	PORTB &= ~((1 << PORTB1) | (1 << PORTB2) | (1 << PORTB3) | (1 << PORTB4));
	PORTD &= ~((1 << PORTD4) | (1 << PORTD5) | (1 << PORTD6) | (1 << PORTD7));
	
	if (pos < 4 || 10 < pos) 
	{
		PORTD |= 1 << pins[pos];
	}
	else
	{
		PORTB |= 1 << pins[pos];
	}
	
	for (uint16_t i = del; i; i--)
		_delay_ms(1);	// Quantum
	
	pos = (pos + 1) % 14;
}

#endif /* A7_RUNNING_LIGHT_8BIT_H_ */