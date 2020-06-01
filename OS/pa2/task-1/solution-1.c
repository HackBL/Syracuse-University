/* Your code goes here */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

#define MAX_NUMBER_STRING 1024

int main(int argc, char *argv[])
{
        if (argc != 2) {  // one command line argument
                printf("An error has occured\n");
                exit(1);
        }
	
        FILE *fp;
        int count = 0;
        char c;
        char const* const fileName = argv[1];

        size_t len = 0;;
        char *line = NULL;

        // Count line of file
        fp = fopen(fileName, "r");

        if (fp == NULL) {
                printf("An error has occured\n");
                exit(1);
        }

        for (c = getc(fp); c != EOF; c = getc(fp)) {
                if (c == '\n')
                        count = count + 1;
        }

        fclose(fp);

        // Pass file into array
        fp = fopen(fileName, "r");

        if (fp == NULL) {
                printf("An error has occured\n");
                exit(1);
        }

        char command[count][MAX_NUMBER_STRING]; // create array to store each command (<= 1024 characters)
        int index = 0;

        while (getline(&line, &len, fp) != -1) {
                strcpy(command[index], line);
                index++;
        }

        fclose(fp);

        // Store each token into arr
        char *arr[3*count];
        index = 0;
	
	   for (int i = 0; i < count; i++) {
                char *p = strtok(command[i], " ");

                while (p != NULL) {
                        arr[index] = p;

			int length = strlen(arr[index]);
			if (arr[index][length-1] == '\n')  // remove newline char
				arr[index][length-1] = '\0';
			
                        p = strtok(NULL, " \n");
			index++;
                }
        }

        index = 0;

        while(index < count) {
                // Create Child Processes
                int rc = fork();

                if (rc < 0) {
                        printf("An error has occured\n");
                        exit(1);
                } 
                else if (rc == 0) {
                        char *myargv[4];
                        myargv[0] = strdup(arr[3*index]);
                        myargv[1] = strdup(arr[3*index+1]);
                        myargv[2] = strdup(arr[3*index+2]);
                        myargv[3] = NULL;                                               
                        
                        execvp(myargv[0], myargv);
                } 
                else {  
                        wait(NULL);
                        index++;        // increase index in parent process    
                }
	   }       

    return 0;
}
