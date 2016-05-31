/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Declarations of internal implementation details.

*/

#include <stdint.h>

#ifndef Memory_Management_mem_impl_h
#define Memory_Management_mem_impl_h

typedef struct free_list free_list;
typedef enum { false, true } boolean;

struct free_list {
    uintptr_t size;
    free_list *next;
};

extern free_list* list;
#endif
