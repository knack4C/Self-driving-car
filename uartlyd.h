#pragma once

void initUART(unsigned long BaudRate, unsigned char DataBit, char Parity);
unsigned char CharReady();
char readChar();
void sendChar(char Tegn);
void sendString(char* Streng);
void sendInteger(int Tal);
void sendCommand(char cmd, char feedback, char Para1, char para2, char checksum1, char checksum2);
void lydStart();
void lydRefleks();
void lydSlut();
void lydKoer();
void stopLyd();
void pauseLyd();
void playLyd();
void volumeUp();
void volumeDown();
void singlePlay();
void randomTrack();
void continuous();
void repeatCurrent();
void specifyEQ(char EQ);
void readCommand();