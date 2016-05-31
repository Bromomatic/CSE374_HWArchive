// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Source file for t9, which emulates the basic functionality of the t9
// system found in older cell phone systems and the like.

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
	
	// Make a node to go through the tree
	struct Node* tracker = root;

	// Get user input, print results
	printf("Enter \"exit\" to quit.\n");
	while(1) {		
		// Prompt		
		printf("Enter Key Sequence (or \"#\" for next word):\n");

		// Make a buffer and capture user input.
		char input[MAX_WORD_LENGTH];
		char output[MAX_WORD_LENGTH];
		fgets(input, MAX_WORD_LENGTH, stdin);

		// Break if given exit command
		if (strstr(input,"exit") != NULL) {
			break;
		}

		// if (input[0] != '\n') {
			// printf;
		// }
		
		
		// Process the input to remove \n
		input[strlen(input)-1] = '\0'; 
		
		// If user enters one or more #'s, keep old tracker so we can
		// iterate further. Otherwise, restart our tracker from the root.
		if (input[0] != '#') {
			tracker = root;
		}

		//make_lower_case(input);
		
		// Make a flag for checking for out of bounds attemps (looking for too many #'s)
		//int oob_flag = 0;
		//int* oob_ptr = &oob_flag;
		
		// search for the input and print
		strcpy(output,search_trie(input,tracker));		
		printf("\t%s\n",output);
		
		/*
		// Print results
		// If we got a NULL back (went too far for a word that wasn't in the trie) or
		// the word is NULL (user didn't enter anything), word not found.
		// If we ran out of words while looking for '#', no more T9onyms.
		// Else, print the word. Have a cookie.
		if (tracker == NULL || tracker->word == NULL) {
			printf("\tNot found in current dictionary.\n");
		} else if (oob_flag) {
			printf("\tThere are no more T9onyms\n");
			oob_flag = 0;
		} else {
			printf("\t%s\n",tracker->word);
		}
		*/
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
