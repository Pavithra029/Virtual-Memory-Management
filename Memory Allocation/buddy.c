#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/mman.h>
#include "buddy.h"

#define MEMORY_SIZE (1 << 10) // Total memory size in bytes (2^10 = 1024)
#define MIN_BLOCK_SIZE (1 << 4) // Minimum block size in bytes (2^4 = 16)

// Structure to represent a memory block
typedef struct block {
    size_t size;        // Size of the block in bytes
    bool free;          // Flag to indicate if the block is free
    struct block* next; // Pointer to the next block in the free list
} Block;

static void* memory = NULL; // Pointer to the allocated memory region
static Block* freeList = NULL;   // Free list to keep track of free memory blocks

// Initialize the memory allocator
void initialize() {
    // Allocate memory using mmap system call
    memory = mmap(NULL, MEMORY_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (memory == MAP_FAILED) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    freeList = (Block*)memory;
    freeList->size = MEMORY_SIZE;
    freeList->free = true;
    freeList->next = NULL;
}

// Allocate memory using the buddy allocation strategy
void* allocate(size_t size) {
    if (size <= 0 || size > MEMORY_SIZE) return NULL;

    // Find a free block with suitable size using first-fit strategy
    Block* current = freeList;
    while (current) {
        if (current->free && current->size >= size) {
            // Split the block if its size is larger than requested size
            while (current->size >= size * 2 && current->size / 2 >= MIN_BLOCK_SIZE) {
                Block* newBlock = (Block*)((char*)current + current->size / 2);
                newBlock->size = current->size / 2;
                newBlock->free = true;
                newBlock->next = current->next;
                current->next = newBlock;
                current->size /= 2;
            }
            current->free = false;
            return (void*)current + sizeof(Block);
        }
        current = current->next;
    }

    // No suitable block found
    return NULL;
}

// Deallocate memory
void deallocate(void* ptr) {
    if (!ptr) return;

    // Find the block corresponding to the given pointer
    Block* block = (Block*)((char*)ptr - sizeof(Block));

    // Mark the block as free
    block->free = true;

    // Coalesce adjacent free blocks 
    while (block->next && block->next->free && block->size * 2 <= MEMORY_SIZE) {
        block->size *= 2;
        block->next = block->next->next;
    }
}




// Display the current state of memory
void displayMemory() {
    printf("Memory Layout:\n");
    Block* current = freeList;
    while (current) {
        printf("Address: %p, Size: %lu bytes, Free: %s\n", current, current->size, current->free ? "Yes" : "No");
        current = current->next;
    }
}


// Deallocate the allocated memory
void cleanup() {
    if (memory) {
        if (munmap(memory, MEMORY_SIZE) == -1) {
            perror("Error deallocating memory");
            exit(EXIT_FAILURE);
        }
        printf("\nDeallocated memory\n");
    }
}

int buddyall(){
initialize();

		    // Allocate some memory blocks
		  void* ptr1 = allocate(64);
		  void* ptr2 = allocate(128);
		  void* ptr3 = allocate(32);

		   // Display memory layout after allocation
		  printf("After allocation:\n");
		  displayMemory();

		  // Deallocate memory blocks
		   
	          deallocate(ptr1);
	          deallocate(ptr3);

		    // Display memory layout after deallocation
		  printf("\nAfter deallocation:\n");
		  displayMemory();

		  cleanup();
		 // printf("\nDisplaying memory after deallocation\n");
		  //displayMemory();
return 0;
}


