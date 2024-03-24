#ifndef mm_H
#define mm_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>

void segfault_handler(int signum);
void* allocate_page();
void deallocate_page(void* page);


#endif 
