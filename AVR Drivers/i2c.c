/*
 * i2c.c
 *
 * Created: 12/8/2019 11:14:07 PM
 *  Author: fathy
 */ 

#include "i2c.h"

void i2c_init( ){                         /* I2C initialize function */
	TWBR = BITRATE(TWSR = 0x00);                  /* Get bit rate register value by formula */
}


/*
I2C_Start function

This function initiate START condition

Input argument : - it has input argument of slave device write address (SLA+W).

Return                 : - it returns status of event.
*/


uint8_t i2c_start_master(uint8_t write_address){                        /* I2C start function */
    uint8_t status;		                                      /* Declare variable */
    TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);                     /* Enable TWI, generate START */
    while(!(TWCR&(1<<TWINT)));	                              /* Wait until TWI finish its current job */
    status=TWSR&0xF8;		                                  /* Read TWI status register */
    if(status!=0x08)		                                  /* Check weather START transmitted or not? */
    return 0;			                                      /* Return 0 to indicate start condition fail */
    TWDR=write_address;		                                  /* Write SLA+W in TWI data register */
    TWCR=(1<<TWEN)|(1<<TWINT);	                              /* Enable TWI & clear interrupt flag */
    while(!(TWCR&(1<<TWINT)));	                              /* Wait until TWI finish its current job */
    status=TWSR&0xF8;		                                  /* Read TWI status register */
    if(status==0x18)	                                      /* Check for SLA+W transmitted &ack received */
    return 1;			                                      /* Return 1 to indicate ack received */
    if(status==0x20)	                                   	  /* Check for SLA+W transmitted &nack received */
    return 2;			                                      /* Return 2 to indicate nack received */
    else
    return 3;		                    	                  /* Else return 3 to indicate SLA+W failed */
}


/*
This function generates REPEATED START condition for read operation.

Input argument : - it has input argument of slave device read address (SLA+R).

Return                 : - it returns status of event.
*/

uint8_t I2C_Repeated_Start_master(uint8_t read_address){ /* I2C repeated start function */
      uint8_t status;		/* Declare variable */
      TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);/* Enable TWI, generate start */
      while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
      status=TWSR&0xF8;		/* Read TWI status register */
      if(status!=0x10)		/* Check for repeated start transmitted */
      return 0;			/* Return 0 for repeated start condition fail */
      TWDR=read_address;		/* Write SLA+R in TWI data register */
      TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
      while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
      status=TWSR&0xF8;		/* Read TWI status register */
      if(status==0x40)		/* Check for SLA+R transmitted &ack received */
      return 1;			/* Return 1 to indicate ack received */
      if(status==0x48)		/* Check for SLA+R transmitted &nack received */
      return 2;			/* Return 2 to indicate nack received */
      else
      return 3;			/* Else return 3 to indicate SLA+W failed */
}



void I2C_Start_Wait(char write_address)						/* I2C start wait function */
{
	uint8_t status;											/* Declare variable */
	while (1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Enable TWI, generate start condition and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x08)									/* Check weather start condition transmitted successfully or not? */
		continue;											/* If no then continue with start loop again */
		TWDR = write_address;								/* If yes then write SLA+W in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Enable TWI and clear interrupt flag */
		while (!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if (status != 0x18 )								/* Check weather SLA+W transmitted & ack received or not? */
		{
			I2C_Stop();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}




/*
WRITE (W)

WRITE data/address event is issued by master after successful acknowledgment of START received from slave device.
I2C_Write function

This function write data/address on bus

Input argument : - it has input argument of data/address.

Return                 : - it returns status of event.
*/


uint8_t i2c_write_master(char data){
	uint8_t status;
	TWDR = data;
	TWCR = (1<<TWEN) | (1<<TWINT);
	while(!(TWCR&(1<<TWINT)));
	status = TWSR & 0XF8;
	if(status==0x28)		              /* Check for data transmitted &ack received */
	return 0;			                  /* Return 0 to indicate ack received */
	if(status==0x30)		              /* Check for data transmitted &nack received */
	return 1;			                  /* Return 1 to indicate nack received */
	else
	return 2;			                  /* Else return 2 for data transmission failure */
}


/*
READ (R)

Read data event is issued by master after successful REPEATED START condition.
I2C_Read_Ack function

This function read data available on SDA line and returns its acknowledgment to slave device about data read successful and also tells slave to transmit another data.

Input argument : - it has no input argument.

Return                 : - it returns received data.
*/

char i2c_read_Ack(){                                  /* I2C read ack function */
      TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);           /* Enable TWI, generation of Ack */
      while(!(TWCR&(1<<TWINT)));	                 /* Wait until TWI finish its current job */
      return TWDR;		                           	/* Return received data */
}

/*
I2C_Read_Nack function

This function read last needed data byte available on SDA line but do not returns acknowledgment of it. It used to indicate slave that master don’t want next data and want to stop communication.

Input argument : - it has no input argument.

Return                 : - it returns received data.
*/

char I2C_Read_Nack()		                  /* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);	            /* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	           /* Wait until TWI finish its current job */
	return TWDR;		                   /* Return received data */
}


/*
STOP (P)

STOP event issued by master to indicate it has to stop.
It is generated by Low to High transition on SDA while SCL is High.

I2C_Stop function

This function initiate STOP condition

Input argument : - it has no input argument.

Return         : - it not returns any data type.
*/

void I2C_Stop()			/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));	/* Wait until stop condition execution */
}


void i2c_write_string(char* data){
	for(int i=0;data[i]!=0;i++)		 
	{
		i2c_write_master (data[i]);
	}
}



void i2c_start_slave(uint8_t slaveAdd){
    TWAR=slaveAdd;		/* Assign Address in TWI address register */
    TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI, Enable ack generation */
}



/*
Listen to bus

Slave device always need to listen to TWI bus to check whether it get addressed by any Master.
When it is addressed, TWINT bit get set. So need to monitor TWINT bit.
I2C_Slave_Listen function

Input argument : - it has no any input argument.

Return                 : - it returns event status.
*/

int8_t I2C_Slave_Listen()
{
	while(1)
	{
		uint8_t status;			/* Declare variable */
		while(!(TWCR&(1<<TWINT)));	/* Wait to be addressed */
		status=TWSR&0xF8;		/* Read TWI status register */
		if(status==0x60||status==0x68)	/* Own SLA+W received &ack returned */
		return 0;			/* Return 0 to indicate ack returned */
		if(status==0xA8||status==0xB0)	/* Own SLA+R received &ack returned */
		return 1;			/* Return 0 to indicate ack returned */
		if(status==0x70||status==0x78)	/* General call received &ack returned */
		return 2;			/* Return 1 to indicate ack returned */
		else
		continue;			/* Else continue */
	}
}

/*
Transmit data  Slave Mode 

After getting addressed by the master with SLA+R address, then slave must send the requested data.
Data to be send need to write in TWDR register.
After data write, enable TWI with acknowledgement and clear interrupt flag.
If acknowledgement not received from master,then slave device will clear TWINT flag and again listen to bus.
Also if REPEATED START/STOP received,then slave device will clear TWINT flag and again listen to bus.

I2C_Slave_Transmit function

Input argument : - it has input argument of character data to be send.

Return                 : - it returns event status.
*/



int8_t I2C_Slave_Transmit(uint8_t data)
{
	uint8_t status;
	TWDR=data;			/* Write data to TWDR to be transmitted */
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);/* Enable TWI & clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0xA0)		/* Check for STOP/REPEATED START received */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}
	if(status==0xB8)		/* Check for data transmitted &ack received */
	return 0;			/* If yes then return 0 */
	if(status==0xC0)		/* Check for data transmitted &nack received */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -2 */
		return -2;
	}
	if(status==0xC8)		/* Last byte transmitted with ack received */
	return -3;			/* If yes then return -3 */
	else			/* else return -4 */
	return -4;
}

/*
Receive data

After getting addressed by the master with SLA+W address,then slave need to receive data sent by the master.
After each byte received, slave need to return acknowledge about it to master.
If REPEATED START/STOP received,then slave device will clear TWINT flag and again listen to bus.
I2C_Slave_Recieve function

Input argument : - it has no input argument.

Return         : - it returns received data or event status.
*/

char I2C_Slave_Receive()
{
	uint8_t status;		/* Declare variable */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);/* Enable TWI & generation of ack */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;		/* Read TWI status register */
	if(status==0x80||status==0x90)/* Check for data received &ack returned */
	return TWDR;		/* If yes then return received data */

	/* Check for data received, nack returned & switched to not addressed slave mode */
	if(status==0x88||status==0x98)
	return TWDR;		/* If yes then return received data */
	if(status==0xA0)		/* Check wether STOP/REPEATED START */
	{
		TWCR|=(1<<TWINT);	/* Clear interrupt flag & return -1 */
		return -1;
	}
	else
	return -2;			/* Else return -2 */
}


