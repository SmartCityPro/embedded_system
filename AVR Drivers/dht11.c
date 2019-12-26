/*
 * CFile1.c
 *
 * Created: 12/10/2019 11:58:03 PM
 *  Author: fathy
 */ 

#include "dht11.h"

void Request()						/* Microcontroller send start pulse or request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);		/* set to low pin */
	_delay_ms(20);					/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN);		/* set to high pin */
}

void Response()						/* receive response from DHT11 */
{
	DDRD &= ~(1<<DHT11_PIN);
	while(PIND & (1<<DHT11_PIN));
	while((PIND & (1<<DHT11_PIN))==0);
	while(PIND & (1<<DHT11_PIN));
}

uint8_t Receive_data()							/* receive data */
{	uint8_t c = 0;
	for (int q=0; q<8; q++)
	{
		while((PIND & (1<<DHT11_PIN)) == 0);	/* check received bit 0 or 1 */
		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))				/* if high pulse is greater than 30ms */
		c = (c<<1)|(0x01);						/* then its logic HIGH */
		else									/* otherwise its logic LOW */
		c = (c<<1);
		while(PIND & (1<<DHT11_PIN));
	}
	return c;
}


void dht11_process(uint8_t *I_RH,uint8_t *D_RH,uint8_t *I_Temp,uint8_t *D_Temp,uint8_t *CheckSum){
	Request();				/* send start pulse */
	Response();				/* receive response */
	*I_RH=Receive_data();	/* store first eight bit in I_RH */
	*D_RH=Receive_data();	/* store next eight bit in D_RH */
	*I_Temp=Receive_data();	/* store next eight bit in I_Temp */
	*D_Temp=Receive_data();	/* store next eight bit in D_Temp */
	*CheckSum=Receive_data();/* store next eight bit in CheckSum */
}