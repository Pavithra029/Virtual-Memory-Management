#ifndef demand_H
#define demand_H

#include <stdio.h>
int demand_paging();
void simulate_page_fault(int page_number);
void load_page_from_backing_store(int page_number);
void display_page_table();
int allocate_free_frame();

void initialize_free_frames();

void initialize_page_table();

#endif 
