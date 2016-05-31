/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Return a pointer to a new block of storage with at least the
			specified size

*/

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

#define NEW_BLOCK_SIZE 10000
#define THRESHOLD 32

free_list *list;
uintptr_t totalsize = 0;

void* getmem(uintptr_t size)
{
    if (size <= 0) {
        return NULL;
    }
    
    //Create new size slightly larger then specified size
    int new_size = (size/16.0 + 1)*16;
    
    //If the list is empty, acquire new memory block
    if (list == NULL && new_size < NEW_BLOCK_SIZE) {
        acquire_new_Block(NEW_BLOCK_SIZE);
    } else if (list == NULL && new_size >= NEW_BLOCK_SIZE) {
        acquire_new_Block(new_size);
    }
    
    free_list *current = list;
    
    //Check if the first free_list block is large enough
    if ((current -> size) >= new_size) {
        if (checkDivide((int)(current -> size), new_size)) {
            free_list *newlist = (free_list*)((uintptr_t)current + (current->size) - new_size);
            newlist -> size = new_size;
            newlist -> next = NULL;
            current -> size = (current -> size) - new_size;
            return newlist;
        } else {
            list = NULL;
            current -> next = NULL;
            return current;
        }
    }
    
    free_list *previous = current;
    
    //find the free_list block that is large enough
    while (((current -> next) != NULL) && ((current -> size) < new_size)) {
        previous = current;
        current = current -> next;
    }
    
    if ((current -> size) < new_size) {
        if (new_size < NEW_BLOCK_SIZE) {
            acquire_new_Block(NEW_BLOCK_SIZE);
        } else if (new_size >= NEW_BLOCK_SIZE) {
            acquire_new_Block(new_size);
        }
        current = current -> next;
    }
    
    if (checkDivide((int)(current -> size), new_size)) {
        free_list *newlist = (free_list*)((uintptr_t)current + (current->size) - new_size);
        newlist -> size = new_size;
        newlist -> next = NULL;
        current -> size = (current -> size) - new_size;
        return newlist;
    } else {
        previous -> next = current -> next;
        current -> next = NULL;
        return  current;
    }
}


// Insert a new block of memory into free_list based on specified size
// and sorted in order of increasing address
void acquire_new_Block(int size) {
    free_list *new = (free_list*)malloc(size);
    new -> size = size;
	totalsize += size;
    if (list == NULL) {
        list = new;
        new -> next = NULL;
    } else {
        if ((uintptr_t)list > (uintptr_t)new) {
            new -> next = list;
            list = new;
        } else {
            free_list *current = list;
            while (current -> next != NULL && ((uintptr_t)(current -> next) < (uintptr_t)new)) {
                current = current -> next;
            }
            if (current -> next == NULL) {
                new -> next = NULL;
                current -> next = new;
            } else {
                new -> next = current -> next;
                current -> next = new;
            }
        }
    }
    
}

//Check if it's nesessary to divide a block
boolean checkDivide(int size1, int size2)
{
    return (size1-size2)>THRESHOLD;
}


