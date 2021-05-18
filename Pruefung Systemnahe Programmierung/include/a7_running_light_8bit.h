/*
 * a7_running_light_8bit.h
 *
 * Created: 10-May-21 16:14:46
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A7_RUNNING_LIGHT_8BIT_H_
#define A7_RUNNING_LIGHT_8BIT_H_

#include <util/delay.h>

int del;
uint8_t b = 1;
uint8_t d = 4;

/*
 * Config 2x4 output pins for 8 bit running light.
 * Delay specifies LED on time.
 */
inline void runningLightSetup(int delay)
{
	DDRB = (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4);	// Set pin B1, B2, B3, B4 and
	DDRD = (1 << DDD4) | (1 << DDD5) | (1 << DDD6) | (1 << DDD7);	// D4, D5, D6 and D7 as output.
	del = delay;
}

/*
 * 
 */
inline static void turnOnDelInc(uint8_t port, uint8_t pin)
{
	port = 1 << pin++;
	_delay_ms(del);
}

/*
 * 
 */
inline static void turnOnDelDec(uint8_t port, uint8_t pin)
{
	port = 1 << pin--;
	_delay_ms(del);
}

/*
 * Running light logic. Walk every four pins of both ports up and down.
 */
inline static void runningLightLoop()
{
	while (d != 8)
		turnOnDelInc(PORTD, d);
	d--;
	PORTD = 0;
	
	while (b != 5)
		turnOnDelInc(PORTB, b);
	b -= 2;
	
	while (b)
		turnOnDelDec(PORTB, b);
	b++;
	PORTB = 0;
	
	while (d != 3)
		turnOnDelDec(PORTD, d);
	d += 2;
}

#endif /* A7_RUNNING_LIGHT_8BIT_H_ */