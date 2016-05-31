# Makefile for t9
# Shawn Stern, CSE 374 Homework 5
# February 20, 2013

# default target
t9: t9.o trie_functions.o
	gcc -Wall -g -o t9 t9.o trie_functions.o

# individual source files
trie_functions.o: trie_functions.c t9.h
	gcc -Wall -g -c trie_functions.c

t9.o: t9.c t9.h
	gcc -Wall -g -c t9.c