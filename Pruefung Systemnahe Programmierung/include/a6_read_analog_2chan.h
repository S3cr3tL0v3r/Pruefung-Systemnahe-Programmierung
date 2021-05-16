/*
 * a6_read_analog_2chan.h
 *
 * Created: 10-May-21 16:14:00
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef A6_READ_ANALOG_2CHAN_H_
#define A6_READ_ANALOG_2CHAN_H_

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>
#include "serial.h"

volatile uint8_t adc0Low;
volatile uint8_t adc0High;
volatile uint8_t adc1Low;
volatile uint8_t adc1High;

inline void readAnalog2chanSetup()
{
	ADMUX = 0;                // use ADC0
	ADMUX |= (1 << REFS0);    // use AVcc as the reference
	ADMUX &= ~(1 << ADLAR);   // Set ADLAR to 0 for 10 bit resolution

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // 128 prescale for 16Mhz
	ADCSRA |= (1 << ADATE);   // Set ADC Auto Trigger Enable
	
	ADCSRB = 0;               // 0 for free running mode

	ADCSRA |= (1 << ADEN);    // Enable the ADC
	ADCSRA |= (1 << ADIE);    // Enable Interrupts

	ADCSRA |= (1 << ADSC);    // Start the ADC conversion

	sei();	// Enable interrupts globally
	
	serialInit();
}

inline static void readAnalog2chanLoop()
{
	int adcValue0, adcValue1;
	adcValue0 = (adc0High << 8) | adc0Low;
	adcValue1 = (adc1High << 8) | adc1Low;
	
	char str0[16];
	char str1[5];
	itoa(adcValue0, str0, 10);
	itoa(adcValue1, str1, 10);
	strcat(str0, " - ");
	strcat(str0, str1);
	sendStringNewLine(str0);
	
	_delay_ms(100);
}

ISR(ADC_vect)
{
	uint8_t tmp = ADMUX;
	tmp &= 0x0F;
	
	if (tmp == 0)
	{
		ADMUX++;
		adc0Low = ADCL;		// read the ADCL register first because
		adc0High = ADCH;	// reading the ADCH causes the ADC to update.
	}
	else if (tmp == 1)
	{
		ADMUX--;
		adc1Low = ADCL;		// read the ADCL register first because
		adc1High = ADCH;	// reading the ADCH causes the ADC to update.
	}
}

#endif /* A6_READ_ANALOG_2CHAN_H_ */