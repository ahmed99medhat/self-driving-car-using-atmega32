/*
 * Ultrasonic.h
 *
 * Created: 2/17/2022 8:09:54 PM
 *  Author: User
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "Ultrasonic_Configuration.h"
#include "DIO.h"
#include "main.h"
void Ultrasonic_Init(void);
uint32_t Ultrasonic(void) ;


#endif /* ULTRASONIC_H_ */