#include <stdio.h>
#include <stdlib.h>
#include "DemandPaging.h"
#define NUM_PAGES 10
#define MEMORY_SIZE 5
#define PAGE_SIZE 100 // Size of each page in bytes

// Simulate page table entries
typedef struct
{
    int frame_number; // -1 indicates not in memory
    int dirty;        // Flag to indicate if page is modified
} page_table_entry;

// Simulate memory frames
int memory[MEMORY_SIZE][PAGE_SIZE];
// Keep track of free frames
int free_frames[MEMORY_SIZE];

// Simulate page table
page_table_entry page_table[NUM_PAGES];

FILE *backing_store;

void initialize_page_table()
{
    for (int i = 0; i < NUM_PAGES; i++)
    {
        page_table[i].frame_number = -1;
        page_table[i].dirty = 0;
    }
}

void initialize_free_frames()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        free_frames[i] = 1; // 1 indicates frame is free
    }
}

int allocate_free_frame()
{
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        if (free_frames[i] == 1)
        {
            free_frames[i] = 0; // Mark frame as used
            return i;
        }
    }
    return -1; // No free frame available
}

void display_page_table()
{
    printf("Page Table:\n");
    printf(" Page | Frame | Dirty\n");
    printf("-------+-------+-------\n");
    for (int i = 0; i < NUM_PAGES; i++)
    {
        printf("  %d   |   %d    |   %d\n", i, page_table[i].frame_number, page_table[i].dirty);
    }
    printf("\n");
}

void load_page_from_backing_store(int page_number)
{
    if (backing_store == NULL)
    {
        printf("Backing store not opened!\n");
        return;
    }

    fseek(backing_store, page_number * PAGE_SIZE, SEEK_SET);
    fread(memory[page_table[page_number].frame_number], 1, PAGE_SIZE, backing_store);
    printf("Loaded page %d from backing store.\n", page_number);
}

void simulate_page_fault(int page_number)
{
    if (page_table[page_number].frame_number == -1)
    {
        printf("Page fault! Page %d not in memory.\n", page_number);

        int free_frame = allocate_free_frame();

        if (free_frame == -1)
        {
            printf("Memory full, page replacement needed!\n");
            // Implement page replacement algorithm here (e.g., FIFO, LRU)
        }
        else
        {
            page_table[page_number].frame_number = free_frame;
            load_page_from_backing_store(page_number);
        }
    }
    else
    {
        printf("Page %d already in memory (frame %d).\n", page_number, page_table[page_number].frame_number);
    }
}

int demand_paging()
{
    initialize_page_table();
    initialize_free_frames();

    char filename[50];
    printf("Enter backing store filename: ");
    scanf("%s", filename);

    backing_store = fopen(filename, "rb");

    if (backing_store == NULL)
    {
        printf("Error opening backing store file!\n");
        return 1;
    }

    int choice, page_number;

    while (1)
    {
        printf("1. Display page table\n");
        printf("2. Simulate page access\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_page_table();
            break;
        case 2:
            printf("Enter page number to access: ");
            scanf("%d", &page_number);
            simulate_page_fault(page_number);
            break;
        case 3:
            printf("Exiting...\n");
            fclose(backing_store);
           return 0;
        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}
