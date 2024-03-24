# Virtual-Memory-Management
Virtual memory management is a cornerstone of modern operating systems, facilitating efficient memory utilization by abstracting physical memory through virtual addressing. This abstraction allows each process to have its own virtual address space, which appears contiguous and separate from other processes, enabling them to operate as though they have more memory than is physically available. Memory allocation techniques such as the Buddy algorithm, best fit, and worst fit dynamically assign memory blocks to processes, optimizing resource usage based on factors like fragmentation reduction and allocation speed. The Buddy algorithm, for instance, divides memory into blocks of sizes that are powers of two, allowing for efficient allocation and deallocation of contiguous memory segments. Best fit selects the smallest available memory block that is large enough to satisfy a process's request, minimizing wasted memory but potentially leading to fragmentation. Worst fit,
on the other hand, selects the largest available memory block, which can reduce fragmentation but may result in less efficient memory utilization.


Objectives:

To implement the following using Virtual Memory Management:

1.	Memory Allocation Using Buddy Algorithm, Best-Fit, Worst-Fit and First-Fit, Memory allocation and deallocation for a page
2.	Translation-Lookaside Buffer with page fault and page hit ratio
3.	Demand Paging
4.	Page Replacement that includes page allocation and deallocation from a frame, handling page faults and page replacement using FIFO(First In First Out), LRU(Least Recently Used), Optimal Paging Algorithms.



To compile: make ,
To run: ./vmm
