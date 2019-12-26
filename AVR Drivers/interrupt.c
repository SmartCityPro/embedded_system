/*
 * interrupt.c
 *
 * Created: 12/10/2019 1:03:14 AM
 *  Author: fathy
 */ 

#include "interrupt.h"

void interrupt_init(Select_Interrupt_Num num,Select_Edge_Type mode){
	switch(num){
		case INT_NUM_0:
		DDRD &= (~(1<<2));
		PORTD |= (1<<2); 
		GICR = 1<<6;		       // Enable INT0
		MCUCR |= (mode<<0) ; 
		break;
		case INT_NUM_1:
		DDRD &= (~(1<<3));
		PORTD |= (1<<3);
		GICR = 1<<7;		      // Enable INT1
		MCUCR |= (mode<<2) ;	
		break;
		case INT_NUM_2:
		DDRB &= (~(1<<2));
		PORTB |= (1<<2);
		GICR = 1<<5;		      // Enable INT2
		MCUCSR |= ((mode-3)<<6);
	}
	
}