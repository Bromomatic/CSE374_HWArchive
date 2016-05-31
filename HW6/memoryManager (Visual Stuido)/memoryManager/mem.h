/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Declarations of external functions that may be used by a user.

*/

#include "mem_impl.h"

#ifndef Memory_Management_mem_h
#define Memory_Management_mem_h

void* getmem(size_t size);
void acquire_new_Block(int size);
int checkDivide(int size1, int size2);

void freemem(void *p);

void get_mem_stats(uintptr_t* total_size, uintptr_t* total_free, uintptr_t* n_free_blocks);

void print_heap(FILE *f);

#endif
