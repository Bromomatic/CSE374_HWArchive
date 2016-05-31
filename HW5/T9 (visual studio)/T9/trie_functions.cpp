/*
 * trie_functions.c
 *
 *  Created on: Feb 20, 2013
 *      Author: Shawn Stern
 */

#include "trie.h"

// Accepts a character and returns the corresponding keypad value 2-9.
int char_code(char in) {
	int codes[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
	int index = in - 'a';
	
	return codes[index];
}

// Return a new node. The node may potentially just be part of the trie 
// with no word stored, so initialize all fields to NULL.
struct Node* make_node() {
	struct Node* new_node_ptr = (struct Node*)malloc(sizeof(struct Node));
	new_node_ptr->word = NULL;
	
	int i;
	// Initialize all next pointers to NULL.
	for (i = 0; i < 10; i++) {
		new_node_ptr->next[i] = NULL;
	}
	
	return new_node_ptr;
}

// Check if the current node contains a printable word.
int is_word (struct Node* input) {
	if (input->word == NULL) {
		return 0;
	} else {
		return 1;
	}
}
