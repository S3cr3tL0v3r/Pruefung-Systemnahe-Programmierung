/*
 * bit_makros.h
 *
 * Created: 10-May-21 15:50:12
 * Authors: Henrik Kaltenbach, Michael Oder and Philipp Küchenmeister
 */ 


#ifndef BIT_MAKROS_H_
#define BIT_MAKROS_H_

#define SET_BIT(PORT, BIT) ((PORT) |= (1 << (BIT)))
#define CLEAR_BIT(PORT, BIT) ((PORT) &= ~(1 << (BIT)))
#define TOGGLE(PORT, BIT) ((PORT) ^= (1 << (BIT)))

#endif /* BIT_MAKROS_H_ */