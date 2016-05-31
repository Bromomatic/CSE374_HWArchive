// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Source file for functions that directly interact with Nodes and/or the trie.

#include "t9.h"

// Declare a Node, containing the word at that node and an array of pointers
// for following nodes, if any.
struct Node{
	char* word;
	struct Node* next[10];
} ;

// Return a new node
// The node may potentially just be part of the trie structre
// with no word stored, so initialize all fields to NULL and let the
// trie code deal with populating them
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

// Returns a trie based on the contents of the passed dictionary file
struct Node* make_trie(struct Node* root, FILE* my_dict) {
	char curr_line[MAX_WORD_LENGTH];
	
	while (NULL != fgets(curr_line, MAX_WORD_LENGTH, my_dict)) {
		struct Node* curr = root;
		
		// Remove pesky newline character.
		curr_line[strlen(curr_line)-1] = '\0'; 
		make_lower_case(curr_line);
		
		int n = 0;
		int code;
		while (curr_line[n] != '\0') {
			// Get T9 code for this char
			code = char_code(curr_line[n]);
			
			// Make a new node at the proper location, if needed
			if (curr->next[code] == NULL) {
				curr->next[code] = make_node();
			}  
			
			// then go to the next node indicated by the T9 code
			curr = curr->next[code];	

			// If a word is already here and we're out of word, go to the 
			// last node in the 'linked list' and add a new # field (next[0])
			if ((curr->word != NULL) && (curr_line[n+1] == '\0')) {
				while (curr->next[0] != NULL) {
					curr = curr->next[0];
				}
				
				curr->next[0] = make_node();
				curr = curr->next[0];
			} 
			
			n++;
		}
		
		// Allocate space
		curr->word = (char*)malloc(sizeof(char) * (strlen(curr_line) + 1));
		
		// If heap fills up and malloc can't allocate space (returns NULL),
		// print error and exit
		if (curr->word == NULL) {
			printf("Heap full, unable to continue. Terminating.\n");
			exit(1);
		}
		
		// Store current word in current node
		strcpy(curr->word,curr_line);
	}

	return root;
}

// Search the trie for the word given by the input sequence, and return
// the node containing that word, if it exists
char* search_trie(char* input, struct Node* tracker) {
	// Traverse tree, digit by digit. Avoid falling off the trie. That's bad.
	int m = 0;
	while (input[m] != '\0') {
		int direction;
		
		// Look at next[0] for synonyms, otherwise the appropriate next[2-9]
		if (input[m] == '#') {
			direction = 0;
		} else {
			direction = input[m] - '0';
		}
		
		// If we went too far, stop short and return (thing doesn't exist)
		if (tracker == NULL) {
			return "Not found in current dictionary.";
		}
		
		// We're looking for a T9onym but there aren't any more, too bad :(
		if  ((input[m] == '#') && (tracker->next[direction] == NULL)) {
			return "There are no more T9onyms";
		} else {
			// We're good, keep looking for the word!
			tracker = tracker->next[direction];
		}
		
		m++;
	}
	
	/*
	if (tracker->word == NULL) {
		return "Not found in current dictionary.";
	} */
	
	return tracker->word;
}

// Recursively free all nodes beneath the current one, 
// then free the current node completely.
void free_node(struct Node* node) {
	if (node != NULL) {
		struct Node* curr = node;
		
		// Remove all children first
		int i;
		for (i = 0; i < 10; i++) {
			free_node(curr->next[i]);
		}
		
		// Free the word field and kill it
		if (curr->word != NULL) {
			free(curr->word);
			curr->word = NULL;
		}
		
		// Free the node and deal the finishing blow (always double tap)
		free(curr);
		curr = NULL;
	}
}
