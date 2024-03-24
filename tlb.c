#include <stdio.h>
#include <stdbool.h>
#include "tlb.h"

#define TLB_SIZE 4 // Maximum size of the TLB
// Function prototypes
void initializeTLB(int tlb[][2], int size);
bool translateAddress(int, int*, int[][2], int[], int, int);
void updateTLB(int tlb[][2], int, int, int);
int getPageNumber(int, int);
int getOffset(int, int);

int method() {
    int pageSize, numberOfPages, logicalAddress, pageNumber, offset, physicalAddress;
    int frameNumber = 0; // Simple frame number assignment
    char choice;
    int tlb[TLB_SIZE][2]; // TLB array: [][0] for pageNumber, [][1] for frameNumber

    // User input for the number of pages
    printf("Enter the number of pages (should be less than or equal to the TLB size=4 ): ");
    scanf("%d", &numberOfPages);

    // Check if the number of pages exceeds the TLB size
    if (numberOfPages > TLB_SIZE) {
        printf("Error: Number of pages cannot be greater than the TLB size.\n");
        return 1; // Exit program with error
    }

    // User input for the page size
    printf("Enter the page size (in bytes): ");
    scanf("%d", &pageSize);

    // Page table initialization (simplified: one-to-one mapping of page to frame)
    int pageTable[numberOfPages];
    for (int i = 0; i < numberOfPages; i++) {
        pageTable[i] = i; // Simplified: page number equals frame number
    }

    // Initialize TLB entries to -1
    initializeTLB(tlb, TLB_SIZE);

    // Counters for TLB hits, TLB misses, and total references
    int hits = 0, misses = 0, totalReferences = 0;

    // Main loop for processing user inputs
    do {
        // User input for logical address
        printf("\nEnter a logical address (integer): ");
        scanf("%d", &logicalAddress);

        // Calculate page number and offset from logical address
        pageNumber = getPageNumber(logicalAddress, pageSize);
        offset = getOffset(logicalAddress, pageSize);

        // Translate logical address to physical address using TLB and page table
        if (translateAddress(pageNumber, &frameNumber, tlb, pageTable, numberOfPages, TLB_SIZE)) {
            hits++;
            printf("TLB Hit.\n");
        } else {
            misses++;
            printf("TLB Miss. ");
            // Update TLB if page is found in page table
            if (pageNumber < numberOfPages) {
                updateTLB(tlb, pageNumber, frameNumber, TLB_SIZE);
                printf("Page found in page table.\n");
            } else {
                printf("Page not found.\n");
            }
        }

        // Calculate and print physical address
        if (pageNumber < numberOfPages) {
            physicalAddress = (frameNumber * pageSize) + offset;
            printf("Physical Address: %d (Frame Number: %d, Offset: %d)\n", physicalAddress, frameNumber, offset);
        }

        totalReferences++; // Increment total references counter

        // Prompt user to continue or exit
        printf("Continue? (Y/N): ");
        scanf(" %c", &choice); // Note the space before %c to catch any newline character left in the input buffer
    } while (choice == 'Y' || choice == 'y');

    // Calculate and print TLB hit rate and miss rate
    double hitRate = (double)hits / totalReferences;
    double missRate = (double)misses / totalReferences;
    printf("\nTLB Hit Rate: %.2f%%\n", hitRate * 100);
    printf("TLB Miss Rate: %.2f%%\n", missRate * 100);

    return 0;
}

// Initialize TLB entries to -1
void initializeTLB(int tlb[][2], int size) {
    for (int i = 0; i < size; i++) {
        tlb[i][0] = -1; // Indicates an unused entry
        tlb[i][1] = -1; // Indicates an unused entry
    }
}

// Translate logical address to physical address using TLB and page table
bool translateAddress(int pageNumber, int *frameNumber, int tlb[][2], int pageTable[], int numberOfPages, int size) {
    for (int i = 0; i < size; i++) {
        if (tlb[i][0] == pageNumber) {
            *frameNumber = tlb[i][1];
            return true; // TLB Hit
        }
    }

    if (pageNumber < numberOfPages) {
        *frameNumber = pageTable[pageNumber]; // Simplified: Direct mapping
        return false; // TLB Miss but page found in page table
    }

    return false; // TLB Miss and page not found
}

// Update TLB with new page number and frame number
void updateTLB(int tlb[][2], int pageNumber, int frameNumber, int size) {
    static int nextIndex = 0;
    tlb[nextIndex][0] = pageNumber;
    tlb[nextIndex][1] = frameNumber;
    nextIndex = (nextIndex + 1) % size; // FIFO replacement
}

// Calculate page number from logical address
int getPageNumber(int logicalAddress, int pageSize) {
    return logicalAddress / pageSize;
}

// Calculate offset from logical address
int getOffset(int logicalAddress, int pageSize) {
    return logicalAddress % pageSize;
}
