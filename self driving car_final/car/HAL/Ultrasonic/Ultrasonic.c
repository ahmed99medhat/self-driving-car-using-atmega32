/*
 * Ultrasonic.c
 *
 * Created: 2/17/2022 8:10:14 PM
 *  Author: User
 */ 
#include "Ultrasonic.h"
       
uint16_t distance = 0; 
uint16_t echo_pin_value = 0;// rising edge
uint8_t sensor_working=0;
uint32_t timer_count=0;


void Ultrasonic_Init(void)
{
	TCCR0 =0;            // stop the timer
	CLR_BIT(TCCR0, WGM01);CLR_BIT(TCCR0, WGM00); //normal mode
	TCCR0 = 0x01;   /* Setting pre-scaler */
	SET_BIT(TIMSK, TOIE0);  //open OVF interrupt
	sei();                      //Enable global interrupt
	
	DIO_SetPinDirection(TRIG_PORT, TRIG_PIN,DIO_OUTPUT);
	DIO_SetPinDirection(ECHO_PORT, ECHO_PIN,DIO_INPUT);
	GICR  |= 1<<INT0 ; //	Enable Peripheral interrupt
	MCUCR |= 1<<ISC00; // any logical interrupt
}
	
uint32_t Ultrasonic(void)
     {
		DIO_SetPinValue(TRIG_PORT,TRIG_PIN,DIO_HIGH);//set trigger pin high
		_delay_us(15);
		DIO_SetPinValue(TRIG_PORT,TRIG_PIN,DIO_LOW);//set trigger pin low
		sensor_working=1;  
		 
		 	return distance;
	 }
ISR(INT0_vect)
{
	if(sensor_working==1)
	{	
	if (echo_pin_value==1)
	{
		distance=(timer_count*256+TCNT0)/466;
		 timer_count=0;
		 echo_pin_value=0;
	     timer_count=0;
	}
	else
	{
		TCNT0=0;
		echo_pin_value=1;
		timer_count=0;
	}
	}
}
ISR(TIMER0_OVF_vect)
 {
	 timer_count++;
	
 }
 

