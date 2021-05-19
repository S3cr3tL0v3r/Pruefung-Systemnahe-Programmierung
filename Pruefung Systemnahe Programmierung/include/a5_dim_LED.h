/*
 * a5_dim_LED.h
 *
 * Dim a LED depending on the position of a potentiometer.
 *
 * Created: 10-May-21 16:11:28
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A5_DIM_LED_H_
#define A5_DIM_LED_H_

#include <avr/interrupt.h>
#include "bit_macros.h"

/*
 * Config analog input and PWM output pins.
 * Config timer0 to provide a PWM signal.
 * Config ADC to read continuous and set the PWM frequency.
 */
inline void dimLEDSetup()
{	
	DDRC &= ~(1 << DDC0);	// C0 is analog input
	DDRD |= (1 << DDD6);	// D6 is now output	
	
	OCR0A = 0;    // set PWM for 0% duty cycle

	TCCR0A |= (1 << COM0A1);				// set none-inverting mode
	TCCR0A |= (1 << WGM01) | (1 << WGM00);  // set fast PWM Mode
	TCCR0B |= (1 << CS01);                  // set prescaler to 8 and starts PWM
	
	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX |= (1 << ADLAR);    // Right adjust for 8 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// 128 prescaler for 16 MHz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();		// Enable interrupts globally
}

/*
 * Timer register content for the PWM frequency equals analog reading.
 */
ISR(ADC_vect)
{	
	OCR0A = ADCH;	// Only need to read the high value for 8 bit resolution.
}

#endif /* A5_DIM_LED_H_ */