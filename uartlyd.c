#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include "uartlyd.h"

#define F_CPU 16000000

void initUART(unsigned long BaudRate, unsigned char DataBit, char Parity)
{
  if ((BaudRate >= 300) && (BaudRate <= 115200) && (DataBit >=5) && (DataBit <= 8))
  { 
    UCSR2A = 0b00100000;
    UCSR2B = 0b00011000;	
    UCSR2C = (DataBit-5)<<1;
	if (Parity == 'E')
      UCSR2C |= 0b00100000;
    else if (Parity == 'O')	  
      UCSR2C |= 0b00110000;	
    UBRR2 = (F_CPU+(8*BaudRate))/(16*BaudRate) - 1;
  }  
}

unsigned char charReady()
{
   return UCSR2A & (1<<7);	//0, hvis IKKE der er modtaget noget
}

char readChar()
{
  while ( (UCSR2A & (1<<7)) == 0 )
  {}                        
  return UDR2;
}

void sendChar(char code)
{
  while ( (UCSR2A & (1<<5)) == 0 )
  {}
  UDR2 = code;
}

void sendString(char* Streng)
{
  while (*Streng != 0)
  {
    sendChar(*Streng);
    Streng++;
  }
}

void sendInteger(int Tal)
{
char array[7];
  itoa(Tal, array, 10);
  sendString(array);
}

void sendCommand(char cmd, char feedback, char para1, char para2, char checksum1, char checksum2)
{
	sendChar(0x7E);
	sendChar(cmd);
	sendChar(feedback);
	sendChar(para1);
	sendChar(para2);
	sendChar(checksum1);
	sendChar(checksum2);
	sendChar(0xEF);
}

void lydStart()
{
	sendChar(0x7E);
	sendChar(0x03);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x01);
	sendChar(0xFF);
	sendChar(0xFC);
	sendChar(0xEF);
}

void lydRefleks()
{
	sendChar(0x7E);
	sendChar(0x03);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x02);
	sendChar(0xFF);
	sendChar(0xFB);
	sendChar(0xEF);
}

void lydSlut()
{
	sendChar(0x7E);
	sendChar(0x03);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x03);
	sendChar(0xFF);
	sendChar(0xFA);
	sendChar(0xEF);
}

void lydKoer()
{
	sendChar(0x7E);
	sendChar(0x03);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x04);
	sendChar(0xFF);
	sendChar(0xF9);
	sendChar(0xEF);
}

void stopLyd()
{
	sendChar(0x7E);
	sendChar(0x16);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xEA);
	sendChar(0xEF);
}

void pauseLyd()
{
	sendChar(0x7E);
	sendChar(0x0E);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xF2);
	sendChar(0xEF);
}

void playLyd()
{
	sendChar(0x7E);
	sendChar(0x0D);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xF3);
	sendChar(0xEF);
}
void volumeUp()
{
	sendChar(0x7E);
	sendChar(0x04);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xFC);
	sendChar(0xEF);
}

void volumeDown()
{
	sendChar(0x7E);
	sendChar(0x05);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xFB);
	sendChar(0xEF);
}

void singlePlay()
{
	sendChar(0x7E);
	sendChar(0x19);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x01);
	sendChar(0xFF);
	sendChar(0xE6);
	sendChar(0xEF);
}

void randomTrack()
{
	sendChar(0x7E);
	sendChar(0x18);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xE8);
	sendChar(0xEF);
}

void continuous()
{
	sendChar(0x7E);
	sendChar(0x11);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x01);
	sendChar(0xFF);
	sendChar(0xEE);
	sendChar(0xEF);
}

void repeatCurrent()
{
	sendChar(0x7E);
	sendChar(0x19);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(0xFF);
	sendChar(0xE7);
	sendChar(0xEF);
}

void specifyEQ(char EQ)
{
	sendChar(0x7E);
	sendChar(0x07);
	sendChar(0x00);
	sendChar(0x00);
	sendChar(EQ);
	sendChar(0xFF);
	sendChar(0xF9-EQ);
	sendChar(0xEF);
}

void readCommand()
{
	readChar();
	readChar();
	readChar();
	readChar();
	readChar();
	readChar();
	readChar();
	readChar();
	
}