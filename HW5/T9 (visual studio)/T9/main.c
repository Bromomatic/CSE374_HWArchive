/*
 * main.c
 *
 *  Created on: Feb 20, 2013
 *      Author: Shawn Stern
 */

#include "trie.h"

#define MAX_WORD_LENGTH 50

void make_lower_case(char* line);

int main(int argc, char** argv) {

	/*
	// Early testing work for sanity
	
	char c[] = {'a','b','c','d','e','f','s','t','u','z','m'};
	
	int i;
	int result;
	
	for (i = 0; i < 11; i++) {
		result = char_code(c[i]);
		printf("%d\n",result);
	}
	
	struct Node* p = make_node();
	struct Node* ohBoy = make_node();
	p->word = "here's a string";
	
	p->next[3] = ohBoy;
	p->next[3]->word = "here's a totally more awesome string";
	
	printf("Contents of p: %s\n",p->word);
	printf("Contents of p's 4th child: %s\n",p->next[3]->word);
	*/
	
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
		
		printf("%s, length: %d\n",curr_line,(int)strlen(curr_line));
		
		int i = 0;
		int code;
		while (curr_line[i] != '\0') {
			code = char_code(curr_line[i]);
			if (curr->next[code] == NULL) {
				curr->next[code] = make_node();
				curr = curr->next[code];
			}
			printf("char %d: %c, code: %d\n",i,curr_line[i],code);
			i++;
		}
		curr->word = curr_line;
		printf("Contents of last node: %s\n",curr->word);
		printf("Reached end of word: %s\n\n",curr_line);
	}
	
	printf("********************\n");
	
	printf("root contents: %s\n",root->word);
	printf("Contents of 227: %s\n",root->next[2]->next[2]->next[7]->word);
	printf("Contents of 87: %s\n",root->next[8]->next[7]->word);
	
	
	
	
	
	
	//FUCK YEAH, WHITESPACE!!!
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	return 0;
}

// Converts the given line to all lower case characters
void make_lower_case(char* line) {
	int i;
	
	for (i = 0; line[i]; i++) {
		line[i] = tolower(line[i]);
	}
}