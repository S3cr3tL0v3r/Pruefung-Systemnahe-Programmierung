/*
 * a6_read_analog_2chan.h
 *
 * Created: 10-May-21 16:14:00
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A6_READ_ANALOG_2CHAN_H_
#define A6_READ_ANALOG_2CHAN_H_

#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "serial.h"

volatile uint8_t adc0L;
volatile uint8_t adc0H;
volatile uint8_t adc1L;
volatile uint8_t adc1H;

/*
 * Config
 */
inline void readAnalog2chanSetup()
{
	ADMUX = 0;					// Use ADC0
	ADMUX |= (1 << REFS0);		// Use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);		// Set ADLAR zero for 10 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);	// 128 prescaler for 16 MHz
	ADCSRA |= (1 << ADEN);		// Enable the ADC
	ADCSRA |= (1 << ADIE);		// Enable Interrupts
	ADCSRA |= (1 << ADSC);		// Start the ADC conversion

	sei();				// Enable interrupts globally
	
	serialBegin(9600);		// Begin serial connection with baud rate
}

/*
 * Merge high and low register into a single integer.
 */
inline int highLowToInt(uint8_t high, uint8_t low)
{
	return (high << 8) | low;
}

/*
 * Make a nice readable output format out of two sensor values.
 */
inline char* formatOutput(char* buffer, char* val0str, char* val1str)
{
	strcpy(buffer, "0:");
	strcat(buffer, val0str);
	strcat(buffer, " - ");
	strcat(buffer, "1:");
	strcat(buffer, val1str);
	return buffer;
}

/*
 * 
 */
inline static void readAnalog2chanLoop()
{
	int adc0Val = highLowToInt(adc0H, adc0L);	// Merge high and low register into
	int adc1Val = highLowToInt(adc1H, adc1L);	// a single integer variable.
	
	char val0str[5];
	char val1str[5];
	itoa(adc0Val, val0str, 10);		// Convert values to strings
	itoa(adc1Val, val1str, 10);		//
	
	char buffer[16];
	formatOutput(buffer, val0str, val1str);		// make a nice readable output format
	sendStringNewLine(buffer);					// and send to serial interface.
	
	_delay_ms(100);
}

/*
 * 
 */
ISR(ADC_vect)
{
	uint8_t tmp = ADMUX & 0x0F;		// Only get the mux bits
	
	if (tmp == 0)		// ADC0
	{
		ADMUX++;			// Add 1 to ADMUX to go to the next sensor
		adc0L = ADCL;		// Read the ADCL register first because
		adc0H = ADCH;		// reading the ADCH causes the ADC to update.
	}
	else if (tmp == 1)	// ADC1
	{
		ADMUX &= 0xF0;		// Clear the last 4 bits to reset the mux to ADC0 
		adc1L = ADCL;		// Read the ADCL register first because
		adc1H = ADCH;		// reading the ADCH causes the ADC to update.
	}
	
	ADCSRA |= (1 << ADSC);	// Start the ADC conversion again
}

#endif /* A6_READ_ANALOG_2CHAN_H_ */