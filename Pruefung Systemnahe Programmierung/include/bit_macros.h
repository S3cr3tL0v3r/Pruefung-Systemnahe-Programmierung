/*
 * bit_makros.h
 *
 * Created: 10-May-21 15:50:12
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef BIT_MAKROS_H_
#define BIT_MAKROS_H_

#define SET_BIT(port, bit) ((port) |= (1 << (bit)))
#define CLEAR_BIT(port, bit) ((port) &= ~(1 << (bit)))
#define TOGGLE_BIT(port, bit) ((port) ^= (1 << (bit)))

#endif /* BIT_MAKROS_H_ */