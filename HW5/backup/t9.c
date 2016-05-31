// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Source file for t9, which emulates the basic functionality of the t9
// system found in older cell phone systems and the like.

#include "t9.h"

int main(int argc, char** argv) {

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
	
	// Run through user interaction
	user_interface(root);
	
	// Free the trie
	free_trie(root);
	
	// Close file to prevent any related memory leaks
	fclose(my_dict);
	
	return 0;
}

// Accepts a character and returns the corresponding keypad value 2-9.
int char_code(char in) {
	int codes[] = {2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9};
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
