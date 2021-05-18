/*
 * a4_summer.h
 *
 * Created: 10-May-21 16:08:08
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A4_SUMMER_H_
#define A4_SUMMER_H_

#include <avr/interrupt.h>

/*
 * Config out- and input pins (incl. pull-up).
 * Config external interrupt INT0 and INT1 for the buttons.
 * Config timer0 to trigger the summer to create a frequency
 * and therefore a sound.
 */
inline void summerSetup()
{
	DDRB |= (1 << DDB4);					// B4 output
	DDRD &= ~((1 << DDD2) | (1 << DDD3));	// D2 and D3 input
	PORTD |= (1 << DDD2) | (1 << DDD3);		// Pull-up resistor D2 and D3
	
	EICRA |= (1 << ISC00) | (1 << ISC10);		// Set interrupt on any logic change
	EICRA &= ~((1 << ISC01) | (1 << ISC11));	// ensure other bits are zero
	EIMSK |= (1 << INT0) | (1 << INT1);			// Enable interrupt INT0 and INT1
	
	OCR0A = 70;					// Concert pitch A 440 Hz
	TCCR0A |= (1 << WGM01);		// Set the Timer Mode to CTC.
	TIMSK0 |= (1 << OCIE0A);	// Set the ISR COMPA vect.
	TCCR0B |= (1 << CS02);		// Set prescaler to 256 and start the timer.
	
	sei();		// Enable interrupts globally
}

/*
 * Change the timer top value to switch to concert pitch A (440 Hz).
 */
ISR (INT0_vect) 
{
	OCR0A = 70;		// Concert pitch A (440 Hz)
}

/*
 * Change the timer top value to switch to concert pitch C (128 Hz).
 */
ISR (INT1_vect) 
{
	OCR0A = 117;	// Concert pitch C (128 Hz)
}

/*
 * Toggle the summer to create sound.
 */
ISR (TIMER0_COMPA_vect) 
{
	PORTB ^= (1 << (PORTB4));
}

#endif /* A4_SUMMER_H_ */