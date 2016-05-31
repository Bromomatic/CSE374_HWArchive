// Shawn Stern, 0921475
// CSE 374, Homework 4
// Program that accepts options, string to match, and files that are to be searched for
// that string. Similar functionality to grep.


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Define maximum limitations on strings
#define MAX_LINE_LENGTH 500
#define MAX_INPUT_LENGTH 100

// Declare functions
void find_match(FILE* my_file, char* f_name, char* string, int* optn, int* opti);
void make_lower_case(char* line);

// Check the input for options i and/or n, then search every file for the given string.
int main(int argc, char ** argv) {
  if(argc < 3) {
    printf("gasp error: program requires a string and at least one file.\n");
    return 0;
  }
  
  // Flags and their pointers for if i or n options have been passed to the program.
  int opti = 0;
  int optn = 0;
  int* opti_ptr = &opti;
  int* optn_ptr = &optn;
  // Int to track the index of argv we're reading.
  int i = 1;
  // Ints for booleans/counters.
  int n,p,j;
  
  // If only three arguments (program name, string, and file) there are no
  // options chosen. Set all flags false. Else, check for -i and -n matches.
  // Increment i so we pass options when we start actually reading files.
  if (3 < argc) {
    for(j = 1;j < 3;j++) {
      n = strcmp("-i",argv[j]);
      p = strcmp("-n",argv[j]);
      if (0==n) {
		opti = 1;
		i++;
      } else if (0==p) {
		optn = 1;
		i++;
      }
    }
  }

  // Allocate space for our target, and save it to 'string'. 
  // Max length globally defined.
  char string[MAX_INPUT_LENGTH];
  strncpy(string, argv[i], MAX_INPUT_LENGTH);
  i++;
  
  // Search each file for a search. Grab its name, then open and search!
  // Close the file afterwards.
  for (i = i; i < argc; i++) {
    char f_name[MAX_INPUT_LENGTH];
    strncpy(f_name, argv[i], MAX_INPUT_LENGTH);
    
    // Use "r" option to just do read.
    FILE* my_file = fopen(argv[i], "r");
    
    // Print error if failure to open, else grep it.
    if (NULL == my_file) {
      printf("Invalid file: %s\n\n", f_name);
    } else {
      find_match(my_file, f_name, string, optn_ptr, opti_ptr);
      fclose(my_file);
    }
  }

  return 0;
}

// Check each line of the given file for a match with the given string.
// If there is a match, prints the given file name and the string containing the match.
// If optn is enabled, also prints the line number for the match.
// If opti is enabled, search ignores case.
void find_match(FILE* my_file, char* f_name, char* string, int* optn, int* opti) {
  // Source keeps track of the original format of the line in case opti is enabled.
  char source[MAX_LINE_LENGTH];
  char curr_line[MAX_LINE_LENGTH];

  // Line counter
  int i = 1;
  
  // Copy the line from the file and do comparisons until we hit eof and get a NULL back.
  while (NULL != fgets(curr_line, MAX_LINE_LENGTH, my_file)) {
    strncpy(source, curr_line, MAX_LINE_LENGTH);
    
    if (*opti) {
      make_lower_case(string);
      make_lower_case(curr_line);
    }

    // If comparison finds a match, print output based on optn status.
    if (NULL != strstr(curr_line,string)) {
      if (*optn) {
		printf("%d %s %s\n", i, f_name, source);
      } else {
		printf("%s %s\n", f_name, source);
      }
    }
    
    i++;
  }
}

// Converts the given line to all lower case characters
void make_lower_case(char* line) {
  int i;

  for (i = 0; line[i]; i++) {
    line[i] = tolower(line[i]);
  }
}
