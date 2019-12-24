/*
 * CFile1.c
 *
 * Created: 9/4/2019 10:11:08 AM
 *  Author: mohamed006
 */ 
#include "gpio.h"


///port direction using [ DDRX ] reg

void port_direction(myuint8_t port , Direction direction){
	if(direction==OUTPUT){
		SET_REG(port+1);
	} else CLEAR_REG(port+1);
}

///port_write using [ PORTX ] reg

void port_write(myuint8_t port , myuint8_t state){
	(*(volatile myuint8_t *)(port+2)) = state;
}

///pin_direction using [ DDRX ] reg
void pin_direction(myuint8_t port ,myuint8_t pin , Direction direction){
	if(direction==OUTPUT){
		SET_BIT(port+1,pin);
	} else CLEAR_BIT(port+1,pin);
}
///pin_write using [ PORTX ] reg
void pin_write(myuint8_t port, myuint8_t  pin , State state){
	if (state == HIGH)
	{
		(*(volatile myuint8_t *)(port+2)) |= (1<<pin);//port+2 => [base+offset]
	}
	else{
		 REGISTER(port+2) &=~(1<<pin);
	}
}

///TODO: pin read and port read
///read from [ PINX ] reg
myuint8_t port_read(myuint8_t port){
	return REGISTER(port);
	
}
myuint8_t pin_read(myuint8_t port,myuint8_t pin){
	return  REGISTER(port) & (1<<pin);
}

