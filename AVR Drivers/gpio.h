/*
 * gpio.h
 *
 * Created: 9/4/2019 10:07:32 AM
 *  Author: mohamed006
 */ 

#include "hw.h"
#ifndef GPIO_H_
#define GPIO_H_


typedef enum direction{
	INPUT,				//INPUT =0
	OUTPUT				//OUTPUT =1
}Direction;

typedef enum state{
	LOW,				//LOW =0
	HIGH				//HIGH =1
}State;

///port_direction
void port_direction(myuint8_t port , Direction direction);
///port_write
void port_write(myuint8_t port , myuint8_t state);
///port_read
myuint8_t port_read(myuint8_t port);
///pin_direction
void pin_direction(myuint8_t port ,myuint8_t pin , Direction direction);
///pin_write
void pin_write(myuint8_t port, myuint8_t  pin , State state);
///pin_read
myuint8_t pin_read(myuint8_t port,myuint8_t pin);
#endif /* GPIO_H_ */