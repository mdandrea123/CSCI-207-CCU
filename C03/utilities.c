#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utilities.h"

/*
	In this assignment, you must finish implementing all
	of these functions.  And don't add any other additional functions
 	work within the framework here 
*/

/* Allocate space for num_elements and return
	by reference
*/
void allocate_memory(int **buffer, int len) {
	if(buffer==NULL || len == 0) {
		perror("Error: ");
		return;
	}
	
	*buffer = (int*)malloc(len * sizeof(int));
	if (*buffer == NULL){
		perror("Error: ");
		exit(1);
	}
}

/* Given the allocated space, initialize contents */
void initialize_memory(int *buffer, int len) {
	if(buffer==NULL || len == 0) {
		perror("Error: ");
		return;
	}
	srand(time(NULL));
	for (int i = 0; i < len; i++){
		buffer[i] = rand();
	}
}

/*Given initialized space, write contents to file, binary format*/
void write_memory_to_file(int *buffer, int len, char *fname) {
	if(buffer==NULL || len == 0) {
		perror("Error: ");
		return;
	}
	
	FILE *file = fopen(fname, "w");
	if (file == NULL){
		perror("Error: ");
		exit(1);
	}
	
	int bytes = fwrite(buffer, sizeof(int), len, file);
	if(bytes != len){
		perror("Error: ");
		exit(1);
	}
	
	fclose(file);
}

/* given the filename, determine size of file in units
	of number of integers.
*/
int determine_file_size(char *fn) {
	int num_elements = 0;

    if (fn == NULL) {
        perror("Error: ");
        return 0;
    }

    // Open the file for reading in binary mode
    FILE *file = fopen(fn, "rb");

    if (file == NULL) {
        perror("Error: ");
        exit(1); 
    }

    // Seek to the end of the file to determine its size
    if (fseek(file, 0, SEEK_END) != 0) {
        perror("Error: ");
        fclose(file);
        exit(1);
    }

    // Get the current file position, which is the size in bytes
    int file_size = ftell(file);

    if (file_size == -1) {
        perror("Error: ");
        fclose(file);
        exit(1);
    }

    // Calculate the number of integers based on the file size
    num_elements = (file_size / sizeof(int));

    // Close the file
    fclose(file);

    return num_elements;
}


/* given an unallocated buffer, and uninitialized length, and the
	filename to work with, allocate the buffer and place the contents
	from the file into the allocated memory space.
	When this functions returns, the buffer will be allocated
	initialized, and also the length will also be knownn and returned by
	reference via the argument list
*/
void initialize_memory_from_file(int **buffer, int *len, char *fn) {
	if (buffer == NULL || len == NULL || fn == NULL) {
        perror("Error: ");
        return;
    }

    // Determine the file size (number of integers)
    *len = determine_file_size(fn);

    if (*len == 0) {
        perror("Error: ");
        exit(1);
    }

    // Allocate memory for the buffer
    allocate_memory(buffer, *len);

    // Open the file for reading in binary mode
    FILE *file = fopen(fn, "rb");

    if (file == NULL) {
		perror("Error: ");
       	exit(1);
    }

    // Read the contents of the file into the allocated memory
    int bytes = fread(*buffer, sizeof(int), *len, file);

    if (bytes != *len) {
        perror("Error: ");
   		exit(1);
    }

    // Close the file
    fclose(file);
    
    return;
}

/* print the contents of memory to the screen
*/
void print_memory(int *buffer, int len) {
	if(!buffer || !len) {
		perror("Error: ");
	}
	// print the array
	for (int i = 0; i < len; i++){
		printf("%d ", buffer[i]);
	}
	printf("\n");
	
	return;
}

