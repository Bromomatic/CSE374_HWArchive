/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Return a block of storage p to the free list at the correct location.

*/

#include <stdio.h>
#include <stdlib.h>
#include "mem_impl.h"
#include "mem.h"

void freemem(void* p) {	
	// If p is NULL, do nothing.
    if (p == NULL) {
		return;
	}
	
	// If p is not from getmem or has been previously released, behavior is undefined
	
	// Take the pointer and calculate the actual address at the start of the block	 
	int address = (uintptr_t)p;
	
	free_list* curr = list;
	free_list* new = (free_list*)((uintptr_t)p);
	
	// Special case where the list is empty to start with
	if (curr == NULL) {
		curr = new;
		curr->next = NULL;
	}
	
	// Compare address of node to be inserted with the current node and next node
	// to see if it goes to the front of the list, can be fit in between, can be 
	// merged with an existing node, needs to go further, or needs to just go to 
	// the end of the list.
	while (curr != NULL) {
		if ((address < (uintptr_t)curr)) {
			// Node belongs at the beginning of the freelist
			new->next = curr;
			curr = new;
			
			return;		
		} else if ((address > (uintptr_t)curr) && (curr->next == NULL)) {
			// Add new node to end of freelist
			curr->next = new;
			new->next = NULL;
			
			return;
		} else if (((uintptr_t)curr + curr->size == address)) {
			// Merge nodes by increasing size of current node and
			// removing data from the merged node's header
			new->next = NULL;
			curr->size += new->size;				
			
			// Check if new node ALSO manages to touch the following node's header,
			// merge with following node as well
			if (address + new->size == (uintptr_t)curr->next) {
				curr->size += curr->next->size;
				curr->next = curr->next->next;
			}
			
			return;
		} else if ((uintptr_t)new + new->size == (uintptr_t)curr->next) {
			// If the node doesn't collide with the previous node, but DOES collide 
			// with the following node
			new->size += curr->next->size;
			new->next = curr->next->next;
			curr->next->next = NULL;			
			curr->next = new;
			
			return;		
		} else if ((address > (uintptr_t)curr) && ((address < (uintptr_t)curr->next))) {
			// Insert normally
			new->next = curr->next;
			curr->next = new;
			
			return;
		}
		
		// If no insertion conditions are met, iterate forward
		curr = curr->next;
	}
}
