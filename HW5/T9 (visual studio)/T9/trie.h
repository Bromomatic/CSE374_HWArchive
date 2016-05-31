/*
 * trie.h
 *
 *  Created on: Feb 20, 2013
 *      Author: Shawn Stern
 */

#ifndef TRIE_H_
#define TRIE_H_

// Necessary includes. Declared here since a number are used both in the main
// source file and in the trie functions source file.
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stdafx.h"

// Declare a Node, containing the word at that node and an array of pointers
// for following nodes, if any.
struct Node{
	char* word;
	struct Node* next[10];
} ;

// Function prototypes
struct Node* make_node();
int char_code(char in);
int is_word (struct Node* input);
void make_lower_case(char* line);

#endif /* TRIE_H_ */
