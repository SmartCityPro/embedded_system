/*
 * utils.h
 *
 * Created: 12/2/2019 7:40:50 PM
 *  Author: fathy
 */ 


#ifndef UTILS_H_
#define UTILS_H_
#define  F_CPU 1000000UL
#include "avr/io.h"
#include "stdint.h"
#include "stdio.h"
#include "util/delay.h"
#include "avr/interrupt.h"

#define true  0x01;
#define flase 0x00;

#define _bv(bit)                        (1<<bit)
#define sbi(reg,bit)                    (reg |= _bv(bit))
#define cbi(reg,bit)                    (reg &= ~_bv(bit))
#define tbi(reg,bit)                    (reg ^= _bv(bit))
#define rbi(reg,bit)                    ((reg>>bit)&0x01) 
#define IS_BIT_SET(reg,bit)             ((reg) & (1<<bit))
#define IS_BIT_CLEAR(reg,bit)           (!((reg) & (1<<bit)))

#define SOUND_VELOCITY 34300          // cm/s
#endif /* UTILS_H_ */