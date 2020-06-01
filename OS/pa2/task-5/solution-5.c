/* Your code goes here */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<assert.h>
#include <sys/stat.h> 

#include"sort.h" 

void usage(char *prog);
int comp (const void * a, const void * b);


int main(int argc, char *argv[]) 
{
	char *inFile, *outFile;

	if (argc != 3)   // Args Err Check
		usage(argv[0]);
	else {
		inFile = strdup(argv[1]);
		outFile = strdup(argv[2]);
	}

	// Open and read file
	int fr = open(inFile, O_RDONLY);

	if (fr < 0) {
		printf("Error: Cannot open file %s\n", inFile);
		exit(1);
	}
	
	// program assumes a 4-byte key in a 100-byte record
    	assert(sizeof(rec_t) == 100);
	
	// READ FILE SIZE (BYTES)
	struct stat finfo;
	fstat(fr, &finfo);
	size_t file_size = finfo.st_size;

	int count = file_size/sizeof(rec_t); // number of objects 

	rec_t r;
	int index = 0;
	rec_t *data = (rec_t*)malloc(count * sizeof(rec_t));

	while (1) { 
		int rc;
		rc = read(fr, &r, sizeof(rec_t));

		if (rc == 0) // 0 indicates EOF
			break;

		if (rc < 0) {
			printf("An error has occured\n");
    		exit(1);
		}

		// Allocate original objects to Dynamic Memory "Orderly" 
		data[index].key = r.key;
		for (int i = 0; i < NUMRECS; i++) 
			data[index].record[i] = r.record[i];

		index++;
	}

	(void) close(fr);	// Close read file

	qsort(data, count, sizeof(rec_t), comp);	// Implement qsort() to sort keys
	
	int fw = open(outFile, O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU);
	if (fw < 0) {
    	printf("Error: Cannot open file %s\n", outFile);
		exit(1);
	}

	//Write sorted data into file
	for (int i = 0; i < count; i++) {
		  		int rc = write(fw, &data[i], sizeof(rec_t));

		  		if (rc != sizeof(rec_t)) {
            		printf("An error has occured\n");
            		exit(1);
	        	}		
	}

	(void) close(fw);	// Close write file
	free(data);		// Free DM

	return 0;
}


void usage(char *prog)
{
    printf("Usage: %s <InputFile> <OutputFile>\n", prog);
    exit(1);
}


int comp (const void * a, const void * b) {
	return (unsigned int)(((rec_t*)a)->key) - (unsigned int)(((rec_t*)b)->key);
}	

