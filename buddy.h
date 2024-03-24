#ifndef buddy_H
#define buddy_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

void initialize();
void* allocate(size_t size) ;
void deallocate(void* ptr);
void displayMemory();
void cleanup(); 
int buddyall();

#endif 
