/*
 * hw.h
 *
 * Created: 9/4/2019 10:05:46 AM
 *  Author: mohamed
 */ 


#ifndef HW_H_
#define HW_H_

///typedef
typedef unsigned char myuint8_t ;
typedef unsigned int  myuint16_t ;

///define ports base address
///use offset[0] for PIN reg , [1] for DDR reg and [2] for PORT reg
#define PORTA 0x39
#define PORTB 0x36
#define PORTC 0x33
#define PORTD 0x30

/// [SET_BIT] and [CLEAR_BIT] 
///use offset[0] for PIN reg , [1] for DDR reg and [2] for PORT reg
#define SET_BIT(reg,bit)   (*(volatile myuint8_t *)(reg)) |= (1<<bit)
#define CLEAR_BIT(reg,bit) (*(volatile myuint8_t *)(reg)) &= ~(1<<bit)
#define TOGEL_BIT(reg,bit) (*(volatile myuint8_t *)(reg)) ^= (1<<bit)
#define SET_REG(reg)       (*(volatile myuint8_t *)(reg)) = 0xff
#define CLEAR_REG(reg)     (*(volatile myuint8_t *)(reg)) = 0x00
#define REGISTER(reg)	   (*(volatile myuint8_t *)(reg))
#define BIT(reg,bit)   	   (*(volatile myuint8_t *)(reg))&(1<<bit)

#endif /* HW_H_ */