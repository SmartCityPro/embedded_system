/*
 * lcd.c
 *
 * Created: 9/4/2019 11:26:12 AM
 *  Author: mohamed
 */ 

#include "lcd.h"
//sending commands to the LCD
void lcd_command(char command){
	//put command in data pins
	port_write(LCD_DATA,command);
	//RS&RW=0;
	pin_write(LCD_COMMAND,LCD_RS,0);//RS =0
	pin_write(LCD_COMMAND,LCD_RW,LOW);//RW =0
	//E high to low
	pin_write(LCD_COMMAND,LCD_EN,HIGH);//EN = 1
	delay_us(1);//to make enable wide
	pin_write(LCD_COMMAND,LCD_EN,0);//EN = 0
	//wait 100 us 
	delay_us(100);
}
	
	
///initializing the LCD
void lcd_init(){
	//make data and command ports as output 
	port_direction(LCD_DATA,OUTPUT);
	pin_direction(LCD_COMMAND,LCD_RS,OUTPUT);
	pin_direction(LCD_COMMAND,LCD_EN,OUTPUT);
	pin_direction(LCD_COMMAND,LCD_RW,OUTPUT);
	pin_write(LCD_COMMAND,LCD_EN,LOW);//LCD_E = 0
	delay_us(2000);	//wait for initialization	
	//Send command [INIT8BIT] 0x38 if using 8bit mode
	lcd_command(INIT8BIT);
	//Send command [BLINKING] 0x0E
	lcd_command(BLINKING);
	//Send Commend [CLEAR]    0x01
	lcd_command(CLEAR);
	delay_us(2000);
	lcd_command(SIFTRIGHT);//Shift cursor right
}
void lcd_data(char data){
	port_write(LCD_DATA,data);
	pin_write(LCD_COMMAND,LCD_RS,1);//RS = 1 for data
	pin_write(LCD_COMMAND,LCD_RW,0);//RW = 0 for write
	pin_write(LCD_COMMAND,LCD_EN,1);//EN = 1
	delay_us(1);//to make enable wide
	pin_write(LCD_COMMAND,LCD_EN,0);//EN = 0
	delay_us(100);
}


void lcd_print(char * data){
	unsigned char i = 0 ;
	while(data[i]!=0){
		lcd_data(data[i]);
		i++;
	}
}

void lcd_goto(unsigned char x ,unsigned char y){
	
	//todo:
	char firstAdr[]={0x80,0xc0};
	lcd_command(firstAdr[y-1]+x-1);
	delay_us(100);
		
}

void lcd_clear(){
    lcd_command(BLINKING);
	lcd_command(CLEAR);
	delay_us(2000);
}

void lcd_cursor_off(){
	lcd_command(CURSOROFF);
}

