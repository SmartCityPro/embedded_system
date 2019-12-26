/*
 * interrupt.h
 *
 * Created: 12/10/2019 1:03:28 AM
 *  Author: fathy
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "utils.h"

typedef enum{
	LOW_LEVEL_TYPE,
	ANY_CHANGE_TYPE,
	FALLING_EDGE_TYPE,
	RAISING_EDGE_TYPE,
	}Select_Edge_Type;


typedef enum{
	INT_NUM_0,
	INT_NUM_1,
	INT_NUM_2,
	}Select_Interrupt_Num;

void interrupt_init(Select_Interrupt_Num,Select_Edge_Type);
#endif /* INTERRUPT_H_ */