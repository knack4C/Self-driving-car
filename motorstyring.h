#pragma once
#include<stdio.h>



void initTimer1();
void initInterupt();
void setTimer(int timerLimit);               // set dutycykle til moteren efter timerens position.
void setSpeed(int brickCount);
void startfart();
void startbrems();

