// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Source file for functions that directly interact with Nodes and/or the trie.

#include "t9.h"


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
		
		// Allocate space and store current word in current node
		curr->word = (char*)malloc(sizeof(char) * (strlen(curr_line) + 1));
		strcpy(curr->word,curr_line);
	}

	return root;
}

// Recursively free all nodes beneath the current one, 
// then free the current node completely.
void free_trie(struct Node* node) {
	if (node != NULL) {
		struct Node* curr = node;
		
		int i;
		for (i = 0; i < 10; i++) {
			free_trie(curr->next[i]);
		}
		
		if (curr->word != NULL) {
			free(curr->word);
			curr->word = NULL;
		}
		
		free(curr);
		curr = NULL;
	}
}

// Prompt user for input, print the desired results. Repeat until told to exit.
void user_interface(struct Node* root) {
	// Make a node to go through the tree
	struct Node* tracker = root;

	// Get user input, print results
	printf("Enter \"exit\" to quit.\n");
	while(1) {		
		// Prompt		
		printf("Enter Key Sequence (or \"#\" for next word):\n");

		// Make a buffer and capture user input.
		char input[MAX_WORD_LENGTH];
		fgets(input, MAX_WORD_LENGTH, stdin);

		// Break if given exit command
		if (strstr(input,"exit") != NULL) {
			break;
		}

		// If user enters one or more #'s, keep old tracker so we can
		// iterate further. Otherwise, restart our tracker from the root.
		if (input[0] != '#') {
			tracker = root;
		}

		input[strlen(input)-1] = '\0'; 
		make_lower_case(input);
		
		int m = 0;
		int oob_flag = 0;
		int dne_flag = 0;
		
		// Traverse tree, digit by digit. Avoid falling off the trie. That's bad.
		while (input[m] != '\0') {
			int direction;
			
			if (input[m] == '#') {
				direction = 0;
			} else {
				direction = input[m] - '0';
			}

			// If a next node, go to it.
			// If there is no next node, input is either not in dictionary, or
			// we've run out of T9onyms. Assume we've run out if latest digit
			// is a pound, otherwise the word doesn't exist.
			if (tracker->next[direction] != NULL) {
				tracker = tracker->next[direction];
			} else if  ((tracker->next[direction] == NULL) && (input[m] == '#')){
				oob_flag = 1;
			} else {
				dne_flag = 1;
			}
			
			m++;
		}

		// Decide and print the output
		if (dne_flag | (tracker->word == NULL)) {
			printf("\tNot found in current dictionary.\n");
			dne_flag = 0;
		} else if (oob_flag) {
			printf("\tThere are no more T9onyms\n");
			oob_flag = 0;
		} else {
			printf("\t%s\n",tracker->word);
		}		
	}
}
