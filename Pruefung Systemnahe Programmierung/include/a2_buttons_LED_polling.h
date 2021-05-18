/*
 * a2_buttons_LED_polling.h
 *
 * Led is switched either on or off after polling the status of two buttons
 *
 * Created: 10-May-21 16:11:57
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A2_BUTTONS_LED_POLLING_H_
#define A2_BUTTONS_LED_POLLING_H_

#include "bit_macros.h"

/*
 * Config out- and input pins (incl. pull-up).
 * LED initially turned on.
 */
inline void buttonsLEDPollingSetup()
{
	SET_BIT(DDRB, PORTB4);						// B4 as output
	DDRD &= ~((1 << DDD2) | (1 << DDD3));		// D2 and D3 as input
	PORTD |= (1 << PORTD2) | (1 << PORTD3);		// Pull-up for D2 and D3
	
	SET_BIT(PORTB, PORTB4);						// Turn on LED initially
}

/*
 * Actively poll the button states and switch LED on or off.
 */
inline void buttonsLEDPollingLoop()
{
	if (!(PIND & (1 << PIND2)))		// Actively poll the state of the two buttons
		PORTB |= 1 << PORTB4;		// and turn the LED on
	if (!(PIND & (1 << PIND3)))
		PORTB &= ~(1 << PORTB4);	// or off.
}

#endif /* A2_BUTTONS_LED_POLLING_H_ */