#ifndef tlb_H
#define tlb_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

void initializeTLB(int tlb[][2], int size);
bool translateAddress(int, int*, int[][2], int[], int, int);
void updateTLB(int tlb[][2], int, int, int);
int getPageNumber(int, int);
int getOffset(int, int);
int method() ;

#endif 
