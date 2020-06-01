/* Your code goes here */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NUMBER_STRING 1024

char* conversion(char h);

int main(int argc, char *argv[]) 
{
	if (argc != 3) {  // two command line arguments
                printf("An error has occured\n");
                exit(1);
        }
	
	char const* const inName = argv[1];
	char const* const outName = argv[2];

	FILE *inFile, *outFile;
	inFile = fopen(inName, "r");
	outFile = fopen(outName, "w");

	int count = 0;
        char c;

	if (inFile == NULL || outFile == NULL) {
                printf("An error has occured\n");
                exit(1);
        }

	// ------- Get number of Lines ------------
	for (c = getc(inFile); c != EOF; c = getc(inFile)) {
                if (c == '\n')
                        count = count + 1;
        }

	fclose(inFile);

	// ------- Read Text Line by Line -----------
	inFile = fopen(inName, "r");
	int index = 0;
        size_t len = 0;
        char *line = NULL;

	char hex[count][MAX_NUMBER_STRING]; // <= 1024 characters
	
	while (getline(&line, &len, inFile) != -1) {
                strcpy(hex[index], line);
                index++;
        }

	fclose(inFile);

	// Convert hex to binary
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < strlen(hex[i]); j++) {
			if (hex[i][j] == '\n')  // write newline to file
				fprintf(outFile, "\n");
			else  // write conversion to file
				fprintf(outFile,"%s",conversion(hex[i][j]));
		}		
	}
	
	fclose(outFile);

	return 0;
}


char* conversion(char h) {
	char* res;
    	switch (h) { 
            case '0': 
                res = "0000";
                break; 
            case '1': 
                res = "0001"; 
                break; 
            case '2': 
                res = "0010"; 
                break; 
            case '3': 
                res = "0011"; 
                break; 
            case '4': 
                res = "0100"; 
                break; 
            case '5': 
                res = "0101"; 
                break; 
            case '6': 
                res = "0110"; 
                break; 
            case '7': 
                res = "0111"; 
                break; 
            case '8': 
                res = "1000"; 
                break; 
            case '9': 
                res = "1001"; 
                break; 
            case 'a': 
                res = "1010"; 
                break; 
            case 'b': 
                res = "1011"; 
                break; 
            case 'c': 
                res = "1100"; 
                break; 
            case 'd': 
                res = "1101"; 
                break; 
            case 'e': 
                res = "1110"; 
                break; 
            case 'f': 
                res = "1111"; 
                break; 
            default: 
                printf("An error has occurred\n"); 
		exit(1);
            } 

            return res;
}


