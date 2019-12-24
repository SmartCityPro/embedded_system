/*
 * adc.h
 *
 * Created: 9/24/2019 5:55:57 PM
 *  Author: mohamed
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "hw.h"
#define  ADCL	0x24
#define  ADCH	0x25
#define  ADCSRA	0x26
#define  ADMUX	0x27
#define  SFOIR	0x50

/// Voltage Reference Selections for ADC  6:7 bits in [ADMUX]
typedef enum{
	External_AREF=0,
	External_AVCC=1,
	INTERNAL_2V5=3,
	}ADCVREF;



///select channel using 0:4 bits in [ADMUX] 
typedef enum{
	ADC0,
	ADC1,
	ADC2,
	ADC3,
	ADC4,
	ADC5,
	ADC6,
	ADC7,	
	}CHANNEL;
	
/// ADC Auto Trigger Source Selections
typedef enum{
	FreeRunningMode,
	AnalogComparator,
	ExternalInterrupt0,
	T0CompareMatch,
	T0Overflow,
	Timer1CompareMatchB,
	Timer1Overflow,
	Timer1CaptureEvent,
    }ADCMODE;
	
/// ADC PreScaler Selections	
typedef enum{
	DIV2 ,
	DIV4 = 2,
	DIV8,
	DIV16,
	DIV32,
	DIV64,
	DIV128
	}ADCPRESCALAR;
	
	
/// ADC init 	
void adc_init(ADCMODE adc_mode,ADCVREF adc_vref,ADCPRESCALAR pre_scalar);
/// read conversation 	
myuint16_t adc_read(CHANNEL channel);

#endif /* ADC_H_ */