#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include "mm.h"

#define PAGE_SIZE 4096 // Page size in bytes

// Signal handler function for SIGSEGV
void segfault_handler(int signum) {
    printf("Segmentation fault: Attempted to access deallocated memory\n");
    exit(EXIT_FAILURE);
}

void* allocate_page() {
    // Allocate memory for a single page
    void* page = mmap(NULL, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page == MAP_FAILED) {
        perror("Error allocating page");
        exit(EXIT_FAILURE);
    }
    printf("Page allocated at virtual address: %p\n", page);
    return page;
}

void deallocate_page(void* page) {
    // Deallocate memory for the page
    if (munmap(page, PAGE_SIZE) == -1) {
        perror("Error deallocating page");
        exit(EXIT_FAILURE);
    }
    printf("Page deallocated at virtual address: %p\n", page);
}


int pageallocation() {
    // signal handler for SIGSEGV
   signal(SIGSEGV, segfault_handler);

   // Allocate a page
  void* page1 = allocate_page();
  void* page2 = allocate_page();
  void* page3= allocate_page();
  void* page4 = allocate_page();
  
  *(int*)page1 = 10; 
  *(int*)page2 = 20; 
  *(int*)page3 = 30; 
  *(int*)page4 = 40; 
  
  printf("Value pointed to by page: %d\n", *(int*)page1);
  printf("Value pointed to by page: %d\n", *(int*)page2);
  printf("Value pointed to by page: %d\n", *(int*)page3);
  printf("Value pointed to by page: %d\n", *(int*)page4);

   // Deallocate the page
  deallocate_page(page1);


  printf("Value pointed to by page: %d\n", *(int*)page2);
  printf("Value pointed to by page: %d\n", *(int*)page3);
  printf("Value pointed to by page: %d\n", *(int*)page4);
 // printf("Value pointed to by page: %d\n", *(int*)page1);
  return 0;
}

