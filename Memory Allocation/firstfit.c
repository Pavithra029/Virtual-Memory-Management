#include<stdio.h>
#include "firstfit.h"
// Function to allocate memory to blocks as per First fit algorithm 

void firstFit(int blockSize[], int m, int processSize[], int n) 
{ 
    int i, j; 
    // Stores block id of the block allocated to a process 
    int allocation[n]; 

    // Initially no block is assigned to any process 
    for(i = 0; i < n; i++) 
    { 
        allocation[i] = -1; 
    } 

    // pick each process and find suitable blocks according to its size and assign to it 
    for (i = 0; i < n; i++) //here, n -> number of processes 
    { 
        for (j = 0; j < m; j++) //here, m -> number of blocks 
        { 
            if (blockSize[j] >= processSize[i]) 
            { 
                // allocating block j to the ith process
               allocation[i] = j; 

                // Reduce available memory in this block. 
                blockSize[j] -= processSize[i]; 

                break; //go to the next process in the queue 
            } 
        } 
    } 

  printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d", allocation[i] + 1);
        else
            printf("Not Allocated");
        printf("\n");
    }
} 


// Driver code 
int firstfitm() 
{ 
    int m; //number of blocks in the memory 
    int n; //number of processes in the input queue 

    printf("Enter the number of blocks: ");
    scanf("%d", &m);

    int blockSize[m]; // Array containing sizes of available blocks
    printf("Enter the sizes of the blocks:\n"); 
    for (int i = 0; i < m; i++)
    {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int processSize[n];  // Array containing sizes of processes
    printf("Enter the sizes of the processes:\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, m, processSize, n); 
    

    return 0 ; 
} 
