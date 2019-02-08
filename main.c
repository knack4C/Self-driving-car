//***********************   DEFINITIONER OG BIBLIOTEKER   ****************************************
#include <stdio.h>
#include "motorstyring.h"
#include "uartlyd.h"
#include "lys.h"
#include <avr/interrupt.h> // bibliotek til interrupts 
#define F_CPU 16000000
#include <util/delay.h>

//________________________________________________________________________________________________
//*********************************     VARIABLE   ***********************************************

long int brickcount = 1;

//________________________________________________________________________________________________
//**********************************   INTERUPT   ************************************************
//lav timerfunktion som initialisere den timer som styrer moteren, den skal opdatere duty cycle. 
//lav interrupt 
//setspeed.

ISR(INT5_vect)   //interrupt VENSTRE
{
	if ((brickcount < 11) && (brickcount >= 0))//Kører på banen
	{
		lydRefleks();
		setSpeed(brickcount);
		brickcount++;
	}
	else if(brickcount >= 11)//MÅL
	{
		lydRefleks();
		_delay_ms(400);
		lydSlut();
		SetDutyCycleTimer4(1023);
		startbrems();
		_delay_ms(800);
		
		FrontLightOff();
		SetDutyCycleTimer4(0);
	}
	_delay_ms(50);
	EIFR = 255;
}
/*
ISR(INT4_vect) //interrupt HØJRE
{
	if (brickcount <11) //Kører på banen
	{
		lydRefleks();
		setSpeed(brickcount);
		brickcount++;
	}
	else if(brickcount >= 11) //MÅL
	{
		lydRefleks();
		_delay_ms(400);
		SetDutyCycleTimer4(1023);
		_delay_ms(300);
		setTimer(0);
		_delay_ms(800);
		FrontLightOff();
		lydSlut();
		SetDutyCycleTimer4(0);	
	}
	_delay_ms(50);
	EIFR = 255;
}*/


//________________________________________________________________________________________________
//*********************************************  MAIN  *******************************************

int main(void)
{
	DDRE = 0x00;
	DDRB = 0xFF;
	PORTB = 0b00000000;
	sei();
	
	initInterupt();
	initTimer1();
	InitTimer4();
	initUART(9600,8,'N');
	_delay_ms(500);
	FrontLightOn();
	SetDutyCycleTimer4(1023);
	_delay_ms(2000);
	
	SetDutyCycleTimer4(388);
	lydStart();
	startfart();

	while(1)
	{	}

	return 0;
}

//****************************************************************************************