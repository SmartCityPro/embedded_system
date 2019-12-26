/*
 * i2c.h
 *
 * Created: 12/8/2019 11:13:52 PM
 *  Author: fathy
 */ 


#ifndef I2C_H_
#define I2C_H_

#include "utils.h"

#define SCL_CLK 100000L							/* Define SCL clock frequency */

/* Define bit rate */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))


typedef enum{
	Prescaler_Value_1,
	Prescaler_Value_4,
	Prescaler_Value_16,
	Prescaler_Value_64,
	}Prescaler_Select;
void i2c_init();
uint8_t i2c_start_master(uint8_t);
uint8_t I2C_Repeated_Start_master(uint8_t);
void I2C_Start_Wait(char);
uint8_t i2c_write_master(char);
char i2c_read_Ack();
char I2C_Read_Nack();
void I2C_Stop()	;
void i2c_write_string(char*);
char I2C_Slave_Receive();
int8_t I2C_Slave_Transmit(uint8_t data);
int8_t I2C_Slave_Listen();
void i2c_start_slave(uint8_t slaveAdd);

#endif /* I2C_H_ */