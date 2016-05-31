/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Store statistics about the current state of the memory manager to 
			the three given integers.

*/

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

extern uintptr_t totalsize;

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks)
{
    free_list *current = list;
    
    while (current != NULL) {
        *total_free += current -> size;
        *n_free_blocks += 1;
        current = current -> next;
    }
    *total_size = totalsize;
}
