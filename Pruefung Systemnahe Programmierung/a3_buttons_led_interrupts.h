/*
 * a3_buttons_led_interrupts.h
 *
 * Created: 10-May-21 16:12:30
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A3_BUTTONS_LED_INTERRUPTS_H_
#define A3_BUTTONS_LED_INTERRUPTS_H_

#include <avr/interrupt.h>
#include "bit_macros.h"

inline void buttonsLEDInterruptSetup() {
	DDRB |= (1 << DDB4);					// B4 output.
	DDRD &= ~((1 << DDD2) | (1 << DDD3));	// D2 and D3 input.
	PORTD |= (1 << DDD2) | (1 << DDD3);		// Pull-up resistor D2 and D3.
	
	EICRA |= (1 << ISC00) | (1 << ISC10);		// Set interrupt on any logic change
	EICRA &= ~((1 << ISC01) | (1 << ISC11));	// ensure other bits are zero
	EIMSK |= (1 << INT0) | (1 << INT1);			// Enable interrupt INT0 and INT1
	
	sei();	// Enable interrupts globally
}

// Interrupt service routine to turn the LED on
#ifndef __vetor_1
#define __vetor_1
ISR (INT0_vect) {
	PORTB |= (1 << PORTB4);
}
#endif /* __vetor_1 */

// Interrupt service routine to turn the LED off
#ifndef __vetor_2
#define __vetor_2
ISR (INT1_vect) {
	PORTB &= ~(1 << PORTB4);
}
#endif /* __vetor_2 */

#endif /* A3_BUTTONS_LED_INTERRUPTS_H_ */