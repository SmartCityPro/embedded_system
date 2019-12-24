/*
 * uart.c
 *
 * Created: 9/25/2019 5:38:37 PM
 *  Author: mohamed
 */ 

#include "uart.h"

void uart_init(){
	/* Use  serial_Confg to Change baud rate */
	
	REGISTER(UBRRL)=(myuint8_t)(UBRRH_VALUE);//use myuint8_t for typecast the value as 8bit 
	REGISTER(UBRRH)=(myuint8_t)((UBRRH_VALUE) >> 8);//send last 4bit to UBRRH
	REGISTER(UCSRB)=(1<<RXEN)|(1<<TXEN);	//Enable RX , TX
	REGISTER(UCSRC)=(1<<UCSZ0)|(1<<UCSZ1)|(1<< URSEL);//set frame  character size 8bits
	
	
}


void uart_writeChar(myuint8_t data){
/* Wait for empty transmit buffer */
while(!(BIT(UCSRA,UDRE)));
REGISTER(UDR)=data; 
}

///write data 
void uart_write(myuint8_t *data){	
	while(*data!='\0'){
		uart_writeChar(*data++);
	}
}



void uart_println(myuint8_t *data){

	while(*data!='\0'){
		uart_writeChar(*data++);
	}
	uart_writeChar('\r');//add new line in terminal
}

// myuint8_t* uart_read(){
// 	
// }

myuint8_t uart_readChar(){
	/* Wait for data to be received */
	while(!(BIT(UCSRA,RXC)));
	return REGISTER(UDR);
}