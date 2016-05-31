// Shawn Stern, CSE 374 Homework 5
// Feb 20 2013
//
// Header for t9 program. Performs necessary includes and defines
// for all t9 source files and states all function prototypes.

#ifndef T9_H_
#define T9_H_


// Necessary includes. Declared here since a number are used both in the main
// source file and in the trie functions source file.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Defines, used in both source files
#define MAX_WORD_LENGTH 200


// Function prototypes
// All functions are used in both source files (or declared in one and used in the other), 
// so it seems appropriate to have them all here.
struct Node* make_node();
struct Node* make_trie(struct Node* root, FILE* my_dict);
struct Node* search_trie(char* input, struct Node* tracker, char* output);
void free_node(struct Node* node);
int char_code(char in);
void make_lower_case(char* line);

#endif /* T9_H_ */
