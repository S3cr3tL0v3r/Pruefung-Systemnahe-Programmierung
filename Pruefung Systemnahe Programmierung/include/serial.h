/*
 * serial.h
 *
 * Created: 10-May-21 15:49:53
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR ((F_CPU / 16 / BAUD) -1)

#include <avr/interrupt.h>

inline void serialInit()
{
	UBRR0H = (MYUBRR >> 8);		// Set baud rate
	UBRR0L = MYUBRR;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	UCSR0B |= (1 << RXCIE0);                    // Enable receiver interrupt
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

	sei();		// Enable interrupts globally
}

inline void sendChar(uint8_t value) {
	while ( !(UCSR0A & (1 << UDRE0)) ) ;
	UDR0 = value;
}

inline void sendString(uint8_t* message) {
	while(*message)
	sendChar(*message++);
}

inline void sendStringNewLine(uint8_t* message) {
	while(*message)
	sendChar(*message++);
	sendChar('\r');
	sendChar('\n');
}

#endif /* SERIAL_H_ */