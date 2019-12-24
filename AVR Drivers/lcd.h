/*
 * lcd.h
 *
 * Created: 9/4/2019 11:26:00 AM
 *  Author: mohamed
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000

#include "hw.h"
#include "gpio.h"
#include "util/delay.h"

#define delay_us(x) _delay_us(x)
///define commands of LCD

#define CLEAR 0X01
#define HOME 0X02
#define SHIFTLIFT 0X04 
#define SIFTRIGHT 0X06
#define BLINKING 0X0E
#define INIT4BIT 0X28
#define INIT8BIT 0X38 
#define CURSOROFF 0X0C


#define LCD_DATA PORTC
#define LCD_COMMAND PORTD
#define LCD_RS 0
#define LCD_EN  1
#define LCD_RW 2
//lcd_command
void lcd_command(char command);
//lcd_init
void lcd_init();
//lcd_data
void lcd_data(char data);
//lcd_print
void lcd_print(char * data);
//lcd_goto
void lcd_goto(unsigned char x,unsigned char y);
//lcd_clear
void lcd_clear();
//lcd_cursor_off
void lcd_cursor_off();
#endif /* LCD_H_ */