/*
 * dht11.h
 *
 * Created: 12/10/2019 11:58:34 PM
 *  Author: fathy
 */ 
#define DHT11_PIN PD6

#ifndef DHT11_H_
#define DHT11_H_

#include "utils.h"

void Request();
void Response();
uint8_t Receive_data();
void dht11_process(uint8_t *I_RH,uint8_t *D_RH,uint8_t *I_Temp,uint8_t *D_Temp,uint8_t *CheckSum);


#endif /* DHT11_H_ */