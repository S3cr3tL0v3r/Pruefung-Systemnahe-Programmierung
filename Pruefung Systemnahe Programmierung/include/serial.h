/*
 * serial.h
 *
 * This program is used to enable serial output of characters, strings and new lines.
 *
 * Created: 10-May-21 15:49:53
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef SERIAL_H_
#define SERIAL_H_

#include <avr/interrupt.h>

/*
 * Config serial interface. Set baud rate and frame.
 * @param	baud	Baud rate
 */
inline void serialBegin(int baud)
{
	int myubrr = (F_CPU / 16 / baud) - 1;
	UBRR0H = (myubrr >> 8);						// Set baud rate
	UBRR0L = myubrr;							//
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);      // Enable receiver and transmitter
	UCSR0B |= (1 << RXCIE0);                    // Enable receiver interrupt
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);    // Set frame: 8data, 1 stp

	sei();										// Enable interrupts globally
}

/*
 * Send a single character as soon as transmitter is ready.
 * @param	value	Character to be sent
 */
inline void sendChar(char value) 
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = value;
}

/*
 * Send a string by calling sendChar on every character until '\0'.
 * @param	message	String to be sent
 */
inline void sendString(char* message) 
{
	while(*message)
		sendChar(*message++);
}

/*
 * Send a string by calling sendChar on every character until '\0'.
 * Add CR and NL.
 * @param	message	String to be sent
 */
inline void sendStringNewLine(char* message) 
{
	while (*message)
		sendChar(*message++);
	sendChar('\r');
	sendChar('\n');
}

#endif /* SERIAL_H_ */