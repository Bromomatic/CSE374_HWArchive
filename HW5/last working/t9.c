// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Source file for t9, which emulates the basic functionality of the t9
// system found in older cell phone systems and the like.

#include <ctype.h>
#include "t9.h"

// Translation table for converting a character to it's T9 code. 
// Made global to prevent having to declare it every time we decode a letter.
int codes[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};

int main(int argc, char** argv) {
	// ----------------------------
	// Initialize
	// ----------------------------
	
	// Open file, print errors if appropriate.
	FILE* my_dict = fopen(argv[1], "r");
	if(my_dict == NULL) {
		fputs("Invalid file. Terminating.\n",stderr);
		return 1;
	}
	
	// Initialize the root
	struct Node* root = make_node();
	
	// Build the trie
	root = make_trie(root, my_dict);
	
	// ----------------------------
	// User interaction
	// ----------------------------
	
	// Make a node and buffers to go through the tree
	struct Node* tracker = root;
	char input[MAX_WORD_LENGTH];
	char output[MAX_WORD_LENGTH];
	
	// Get user input, print results
	printf("Enter \"exit\" to quit.\n");
	while(1) {		
		// Prompt		
		printf("Enter Key Sequence (or \"#\" for next word):\n");

		fgets(input, MAX_WORD_LENGTH, stdin);

		// If user just hit enter, skip the rest of this loop
		if (input[0] == '\n') {
			printf("\tUser did not enter anything.\n");
			continue;
		}
		
		// Break if given exit command
		if (strstr(input,"exit") != NULL) {
			break;
		}

		// If user enters one or more #'s, keep old tracker so we can
		// iterate further. Otherwise, restart our tracker from the root.
		if (input[0] != '#') {
			tracker = root;
		}
		
		// Process the input to remove \n
		input[strlen(input)-1] = '\0'; 
		
		// search for the input and save our progress in tracker in case the user wants more #'s
		tracker = search_trie(input, tracker, output);
		
		printf("\t%s\n",output);
	}
	
	// ----------------------------
	// Clean up
	// ----------------------------
	
	// Free the trie
	free_node(root);
	
	// Close file to prevent any related memory leaks
	fclose(my_dict);
	
	return 0;
}

// Accepts a character and returns the corresponding keypad value 2-9.
int char_code(char in) {
	//int codes[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
	int index = in - 'a';
	
	return codes[index];
}

// Converts the given line to all lower case characters
void make_lower_case(char* line) {
	int i;
	
	for (i = 0; line[i]; i++) {
		line[i] = tolower(line[i]);
	}
}
