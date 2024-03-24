#ifndef pagere_H
#define pagere_H

#include <stdio.h>


void getData();
void initialize();

int getHitIndex(int data);
void dispPages();
void dispPgFaultCnt();
void optimal();
void lru();
int replacement();

#endif 
