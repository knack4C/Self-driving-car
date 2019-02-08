#include "motorstyring.h"
#include "uartlyd.h"
#include "lys.h"
#include<stdio.h>
#include<avr/interrupt.h> // bibliotek til interrupts
#include<time.h>
#include<stdlib.h>
#define F_CPU 16000000
#include <util/delay.h>


void initTimer1()
{
	// Set OC1A on match down counting / Clear OC1A on match up counting
	// Clock prescaler = 256
	TCCR1A = 0b10000010; //sætter fast PWM mode 9-bit
	TCCR1B = 0b00001100; //prescale sat til 256
	//
	OCR1A = 0; // dutycycle 0%
}

void initInterupt()
{
	// INT4 & INT5:sat til falling edge,
	EICRA = 0b00000000;
	EICRB = 0b00001000;
	// Enable extern interrupts INT 4 & 5
	EIMSK = 0b00100000;
	EIFR = 255;
}

void setTimer(int limit)
{
	OCR1A = limit;
}

void setSpeed(int brickcount)
{
	if (brickcount  == 2)
	{
		for (size_t i=511; i > 330; i-=2)
		{
			setTimer(i);
		}
		_delay_ms(400);
		for (size_t i = 330; i < 511; i+=2)
		{
			setTimer(i);
		}	
	}
	else if(brickcount == 3)
	{
		setTimer(260);
		_delay_ms(2500);
		for (size_t i = 200; i <511; i+=1)
		{
			setTimer(i);
		}
	}
	else if(brickcount == 4)
	{
		for (size_t i=220; i < 511; i+=2)
		{
			setTimer(i);
		}
	}
	else if (brickcount == 6) //Brems ned og bak
	{
		SetDutyCycleTimer4(1023);
		startbrems();
		_delay_ms(500);
		SetDutyCycleTimer4(338);
		
		PORTB ^=0b00010000;
		setTimer(511);
		startbrems();
		_delay_ms(200);
		lydRefleks();
		_delay_ms(950);
		lydRefleks();
		EIFR = 255;
	}
	
	else if (brickcount == 7)
	{
	}
	
	else if (brickcount == 8) //Brems ned og kør frem
	{
		SetDutyCycleTimer4(1023);
		startfart();
		_delay_ms(500);
		SetDutyCycleTimer4(338);
		_delay_ms(600);
		setTimer(0);
		PORTB ^=0b00010000;
		startfart();
		EIFR = 255;	
	}
	else //Fuld smadder
	{
		setTimer(511);
	}
}

void startfart()
{
	for (size_t i = 20; i < 511; i+=3)
	{
		setTimer(i);
		_delay_ms(2.5);
	}	
}

void startbrems()
{
	for (size_t i = 511; i > 20; i-=2)
	{
		setTimer(i);
		_delay_ms(3);
	}	
}