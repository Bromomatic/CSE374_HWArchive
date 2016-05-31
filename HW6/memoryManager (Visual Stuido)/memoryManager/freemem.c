/*
Author(s): 	Tianshu Bao, Shawn Stern
Date:		2/17/2013
Project: 	CSE 374, HW6 Memory Manager
Function: 	Return a block of storage to the free list at location p.

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
	free_list* newer = (free_list*)((uintptr_t)p);
	
	// Special case where the list is empty to start with
	if (curr == NULL) {
		curr = newer;
	}
	
	// Compare address of node to be inserted with the current node and next node
	// to see if it goes to the front of the list, can be fit in between, can be 
	// merged with an existing node, needs to go further, or needs to just go to 
	// the end of the list.
	while (curr != NULL) {
		if ((address < (uintptr_t)curr)) {
			// Node belongs at the beginning of the freelist
			newer->next = curr;
			curr = newer;
			
			return;		
		} else if ((address > (uintptr_t)curr) && (curr->next == NULL)) {
			// Add new node to end of freelist
			curr->next = newer;
			newer->next = NULL;
			
			return;
		} else if (((uintptr_t)curr + curr->size == address) || (address + newer->size == (uintptr_t)curr->next)) {
			// If the new node collides with either the preceeding or following node...
			
			// Merge with previous node
			if ((uintptr_t)curr + curr->size == address) {
				// Merge nodes by increasing size of current node and
				// removing data from the merged node's header
				newer->next = NULL;
				curr->size += newer->size;				
				
				newer->size = NULL;
			}
			
			// Check if new node also manages to touch the following node's header,
			// merge with following node as well
			if (address + newer->size == (uintptr_t)curr->next) {
				curr->size += curr->next->size;
				curr->next = curr->next->next;
				curr->next->size = NULL;
			}
			
			return;
		} else if ((address > (uintptr_t)curr) && ((address < (uintptr_t)curr->next))) {
			// Insert normally
			newer->next = curr->next;
			curr->next = newer;
			
			return;
		}
		
		// If no insertion conditions are met, iterate forward
		curr = curr->next;
	}
}

/*
	int address;
	free_list* curr;
	free_list* newer;

	// If p is NULL, do nothing.
    if (p == NULL) {
		return;
	}
	
	// If p is not from getmem or has been previously released, do whatever.
	
	// Take the pointer and calculate the actual address at the start of the block
	// by stepping back 16 bytes
	 
	address = (uintptr_t)p;
	
	// Compare address of node to be inserted with the current node and next node
	// to see if it can be fit in between, can be merged with an existing node, 
	// needs to go further, or needs to just go to the end of the list.
	
	curr = list;
	newer = (free_list*)((uintptr_t)p);
	
	while (curr != NULL) {
		if ((address > (uintptr_t)curr) && (curr->next == NULL)) {
			// Add newer node to end of freelist
			curr->next = newer;
			newer->next = NULL;
			
			return;
		} else if ((uintptr_t)curr + curr->size == address) {
			// Merge nodes by increasing size of current node and
			// removing data from the merged node's header
			newer->next = NULL;
			curr->size += newer->size;
			newer->size = NULL;
			
			return;
		} else if ((address > (uintptr_t)curr) && ((address < (uintptr_t)curr->next))) {
			// Insert normally
			newer->next = curr->next;
			curr->next = newer;
			
			return;
		}
		
		// If no insertion conditions are met, iterate forward
		curr = curr->next;
	}	
}

*/

/*
// Search the list for a suitable address at which to insert the current free node
int insert_location(void* p) {
	int result;
	
	
	
	return result;
}
*/
