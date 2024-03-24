#include<stdio.h>
#include<stdbool.h>
#include "pagere.h"
#include "mm.h"
#include "buddy.h"
#include "tlb.h"
#include "firstfit.h"
#include "bestfit.h"
#include "worstfit.h"
#include "DemandPaging.h"

#define MEMORY_SIZE (1 << 10) // Total memory size in bytes (2^10 = 1024)
#define MIN_BLOCK_SIZE (1 << 4) // Minimum block size in bytes (2^4 = 16)
#define TLB_SIZE 4 // Maximum size of the TLB

 
 int main(){
 
  
  int ch1,ch2,ch3;
      int exitInnerLoop = 0;
  
 while(true){
 printf("\n1.Memory allocation 2.Paging with TLB 3.Demand paging 4.page replacement 5.Exit ");
 scanf("%d",&ch1);
 switch(ch1){
 case 1:while(true){
        printf("\n1.page allocation 2. buddy allocation 3.Best fit/worst fit/first fit 4.Exit ");
        scanf("%d",&ch2); 
        switch(ch2){
        case 1:  pageallocation();
                 break;
	case 2:  buddyall();
		 break;
	case 3:while(true){
		printf("\n1.firstfit 2. bestfit 3.worst fit  4.Exit ");
		scanf("%d",&ch3); 
		switch(ch3){
		case 1: firstfitm();
			break;
		case 2: bestfitm();
		  	break;
		case 3: worstfitm();
		        break;
		case 4:exitInnerLoop = 1;     
			} 
			   if (exitInnerLoop) {
		                exitInnerLoop = 0;  // Reset flag
		                break;  // Exit inner loop
		            }
			printf("\n");      
		    }
		    break;
	
	case 4: exitInnerLoop = 1;     
		} 
		   if (exitInnerLoop) {
                        exitInnerLoop = 0;  // Reset flag
                        break;  // Exit inner loop
                    }
		printf("\n");      
	    }
	    break;
    case 2: method(); 
    	break;
    case 3: demand_paging();
    break;
    case 4: replacement();
    	break;
    case 5:return 0;
   
}
 }
  
return 0;
}

