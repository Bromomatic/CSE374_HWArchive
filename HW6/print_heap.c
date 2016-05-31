/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Print a formatted listing to file f showing the blocks on the freelist

*/

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

void print_heap(FILE *f)
{
    free_list *current = list;
	while (current!=NULL) {
		fprintf(f, "%p, 0x%x\n", current, (int)current -> size);
		current = current -> next;
	}
}