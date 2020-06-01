/* Your code goes here */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING 1024

int main() 
{
	while (1) {	
		char command[MAX_STRING];
		fgets(command, MAX_STRING, stdin); 

		// Tokenization
		char* tok = strtok(command, " \n\t");

		while (tok != NULL) {		
			int length = strlen(tok);
			if (tok[length-1] == '\n')
				tok[length-1] = '\0';

			if (strcmp(tok, "exit") == 0) exit(0); // exit the program
			
			printf("%s\n", tok);

			tok = strtok(NULL, " \n\t");
		}
	}

	return 0;
}
