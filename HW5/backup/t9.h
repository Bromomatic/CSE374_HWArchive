// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Header for t9 program, performs necessary includes and defines
// for all t9 source files and states all function prototypes.

#ifndef T9_H_
#define T9_H_

// Necessary includes. Declared here since a number are used both in the main
// source file and in the trie functions source file.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Defines
#define MAX_WORD_LENGTH 100


// Declare a Node, containing the word at that node and an array of pointers
// for following nodes, if any.
struct Node{
	char* word;
	struct Node* next[10];
} ;


// Function prototypes
struct Node* make_node();
struct Node* make_trie(struct Node* root, FILE* my_dict);
void free_trie(struct Node* node);
int char_code(char in);
void make_lower_case(char* line);
void user_interface(struct Node* root);

#endif /* T9_H_ */
