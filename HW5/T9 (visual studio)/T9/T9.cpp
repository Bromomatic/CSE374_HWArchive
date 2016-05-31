// T9.cpp : Defines the entry point for the console application.
//

/*
 * main.c
 *
 *  Created on: Feb 20, 2013
 *      Author: Shawn Stern
 */
#define _CRT_SECURE_NO_DEPRECATE
#include "trie.h"

#define MAX_WORD_LENGTH 50


int main(int argc, char** argv) {

	// Open file, print errors if appropriate.
	FILE* my_dict = fopen(argv[1], "r");
	if(my_dict == NULL) {
		fputs("Invalid file. Terminating.\n",stderr);
		return 1;
	}
	
	struct Node* root = make_node();
	
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
				curr = curr->next[code];
			}  else {
				// else, we're just passing through this node
				curr = curr->next[code];
			}	

			if ((curr->word != NULL) && (curr_line[n+1] == '\0')) {
				// If a word is already there and we're out of word, go to the last node in the
				// 'linked list' and add a new # field (next[0])
				while (curr->next[0] != NULL) {
					curr = curr->next[0];
				}
				curr->next[0] = make_node();
				curr = curr->next[0];
			} 
			
			//printf("char %d: %c, code: %d\n",n,curr_line[n],code);
			n++;
		}
		// Allocate space and store current word in current node
		curr->word = (char*)malloc(sizeof(char) * strlen(curr_line));
		strcpy(curr->word,curr_line);
	}

	// Make a node to go over the tree
	struct Node* tracker = root;

	printf("Enter \"exit\" to quit.\n");
	// Get user input, print results
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
		while (input[m] != '\0') {
			int direction;

			if (input[m] == '#') {
				direction = 0;
			} else {
				direction = input[m] - '0';
			}

			if (tracker->next[direction] != NULL) {
				tracker = tracker->next[direction];
			} else {
				oob_flag = 1;
			}
			m++;
		}

		if (oob_flag) {
			printf("\tThere are no more T9onyms\n");
			oob_flag = 0;
		} else {
			printf("\t%s\n",tracker->word);
		}		
	}
	
	// stuff to undo the malloc
	
	return 0;
}

// Converts the given line to all lower case characters
void make_lower_case(char* line) {
	int i;
	
	for (i = 0; line[i]; i++) {
		line[i] = tolower(line[i]);
	}
}

