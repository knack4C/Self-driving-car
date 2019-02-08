/*
 * FunctionsLight.c
 *
 * Created: 11-12-2018 12:40:00
 *  Author: danie
 */ 
#include "lys.h"
#include <avr/io.h>

void FrontLightOn()
{
	PORTB |= 0b00000001;
}

void FrontLightOff()
{
	PORTB &= 0b11111110;
}

void InitTimer4()
{
	DDRH = 0xFF;
	
	TCCR4A = 0b10000011;		//Initialisering af timer 4
	TCCR4B = 0b00000001;
	
	//OCR4A = 512;				//Duty cycle initialisering 50%
	
}

void SetDutyCycleTimer4(unsigned int Duty)
{
	OCR4A = (Duty);
}