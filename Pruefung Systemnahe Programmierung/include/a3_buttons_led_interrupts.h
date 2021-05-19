/*
 * a3_buttons_led_interrupts.h
 *
 * LED is switched either on or off using extern interrupts from buttons.
 *
 * Created: 10-May-21 16:12:30
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A3_BUTTONS_LED_INTERRUPTS_H_
#define A3_BUTTONS_LED_INTERRUPTS_H_

#include <avr/interrupt.h>

/*
 * Config out- and input pins (incl. pull-up).
 * Config external interrupt INT0 and INT1 for the buttons.
 * LED initially turned on.
 */
inline void buttonsLEDInterruptSetup()
{
	DDRB |= (1 << DDB4);					// B4 output.
	PORTB |= (1 << PORTB4);					// LED initially on.
	DDRD &= ~((1 << DDD2) | (1 << DDD3));	// D2 and D3 input.
	PORTD |= (1 << PORTD2) | (1 << PORTD3);	// Pull-up resistor D2 and D3.
	
	EICRA = (1 << ISC00) | (1 << ISC10);	// Set interrupt on any logic change
	EIMSK |= (1 << INT0) | (1 << INT1);		// Enable interrupt INT0 and INT1
	
	sei();		// Enable interrupts globally
}

/*
 * Turn the LED on.
 */
ISR (INT0_vect) 
{
	PORTB |= (1 << PORTB4);
}

/*
 * Turn the LED off.
 */
ISR (INT1_vect) 
{
	PORTB &= ~(1 << PORTB4);
}

#endif /* A3_BUTTONS_LED_INTERRUPTS_H_ */