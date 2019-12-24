/*
 * uart.h
 *
 * Created: 9/25/2019 5:38:18 PM
 *  Author: mohamed
 */ 


#ifndef UART_H_
#define UART_H_
#include "hw.h"
#include "uart_Confg.h"

#define UBRRH_VALUE FOSC/16/BAUD-1


#define UBRRH 0x40
#define UCSRC 0x40
#define UDR 0x2C
#define UCSRA 0x2B
#define UCSRB 0x2A
#define UBRRL 0x29
//bits in UCSRA
#define RXC		7	
#define TXC		6	
#define UDRE	5		

//bits in UCSRB
#define RXCIE	7
#define TXCIE	6
#define UDRIE	5
#define RXEN	4
#define TXEN	3		
#define UCSZ2	2
//bits in USCRC
#define UCSZ0	1	 
#define UCSZ1	2
#define USBS	3
#define UPM0	4
#define UPM1	5
#define UMSEL	6
#define URSEL	7

///inti UART set baud rate in uart_Confg.h
void uart_init(void);
///write character
void uart_writeChar(myuint8_t data);
///write String
void uart_write(myuint8_t *data);
///write String with new line
void uart_println(myuint8_t *data);
///read String
myuint8_t* uart_read();
///read character
myuint8_t uart_readChar(void);


#endif /* SERIAL_H_ */