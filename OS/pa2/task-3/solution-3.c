#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_NUMBER_STRING 1024

char* conversion(char* h);

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

    	char binary[count][MAX_NUMBER_STRING]; // character <= 1024

	while (getline(&line, &len, inFile) != -1) {
        	strcpy(binary[index], line);
        	index++;
    	}

    	fclose(inFile);

    	// Convert binary to hex
	for (int i = 0; i < count; i++) {
		int j = 0, k = 1;
		while (j < strlen(binary[i])) {
			if (binary[i][j] == '\n') {
				fprintf(outFile, "\n");
				j++;
			}
			else {
				int ind = 0;
				char *str2 = malloc(4*sizeof(char)+1);	// 4*1 (binary with 4 digit) + 1 ('\0')

				if (str2 == NULL) {
					printf("An error has occured\n");
					exit(1);
				}				
	
				while (j < k*4) {	// Binary code has 4 digits
					str2[ind] = binary[i][j];
					
     					ind++;
					j++;
				}
				str2[4] = '\0';
				fprintf(outFile,"%s",conversion(str2)); // write hex to file
				free(str2);

				k++;
			}
		}
	}	

	fclose(outFile);

	return 0;
}

char* conversion(char* h) {
    char* res;

    if (strcmp(h, "0000") == 0) 
        res = "0";
    else if (strcmp(h, "0001") == 0)
        res = "1";
    else if (strcmp(h, "0010") == 0)
        res = "2";
    else if (strcmp(h, "0011") == 0)
        res = "3";
    else if (strcmp(h, "0100") == 0)
        res = "4";
    else if (strcmp(h, "0101") == 0)
        res = "5";
    else if (strcmp(h, "0110") == 0)
        res = "6";
    else if (strcmp(h, "0111") == 0)
        res = "7";
    else if (strcmp(h, "1000") == 0)
        res = "8";
    else if (strcmp(h, "1001") == 0)
        res = "9";
    else if (strcmp(h, "1010") == 0)
        res = "a";
    else if (strcmp(h, "1011") == 0)
        res = "b";
    else if (strcmp(h, "1100") == 0)
        res = "c";
    else if (strcmp(h, "1101") == 0)
        res = "d";
    else if (strcmp(h, "1110") == 0)
        res = "e";
    else if (strcmp(h, "1111") == 0)
        res = "f";
    else {
        printf("An error has occurred\n"); 
        exit(1);
    }
    return res;
}
