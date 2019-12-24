/*
 * adc.c
 *
 * Created: 9/24/2019 5:56:15 PM
 *  Author: mohamed
 */ 


#include "adc.h"

void adc_init(ADCMODE adc_mode,ADCVREF adc_vref,ADCPRESCALAR pre_scalar){
	//set voltage ref bits 6:7

  	REGISTER(ADMUX)|=(adc_vref<<6);
	//The result in the ADC Data Register is right adjusted
	CLEAR_BIT(ADMUX,5);
	//set clock preScalar
	REGISTER(ADCSRA)|=(pre_scalar<<0);
	//select mode
	REGISTER(SFOIR) |=(adc_mode << 5);
	// auto trigger enable
	SET_BIT(ADCSRA,5) ;
	// inter enable
// 	SET_BIT(ADCSRA,3) ;
// 	SET_BIT(0x5f,7);
	//set ADC enable bit
	SET_BIT(ADCSRA,7);
	
}


myuint16_t adc_read(CHANNEL channel){
	
	//select channel
// 	myuint16_t val = 0;
	// REGISTER(ADMUX) &= ~0x1f;
	REGISTER(ADMUX)|=(channel<<0);
	SET_BIT(ADCSRA,6);//start conversation
	while (BIT(ADCSRA,4));//wait for con complete
	//read data 
	//val = ADCL| (ADCH << 8);
// 	val = (REGISTER(ADCL));
// 	val |= ( REGISTER(ADCH) << 8);
	
	return (REGISTER(ADCL))|( REGISTER(ADCH) << 8);
	
}