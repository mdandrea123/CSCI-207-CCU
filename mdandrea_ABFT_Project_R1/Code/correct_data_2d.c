// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/24/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char *argv[])
{
    char *infile = NULL;
    char *outfile = NULL;
    int pflag = 0;

    parseCorrect(argc, argv, &infile, &outfile, &pflag);

    if(infile == NULL || outfile == NULL){
        printf("Usage: [-p] -i <in file> -o <out file>\n");
        exit(1);
    }
    
    dtype **m1;
    dtype **m2;
    int rows;
    int cols;

    double start, end, elapsed;
    GET_TIME(start);
    initialize_from_file(&m1, &rows, &cols, infile);
    allocate2d(&m2, rows, cols);
    correct(m1, m2, rows, cols);
    write_to_file(m2, rows, cols, outfile);
    if(pflag){
        printf("Matrix 1:\n");
        print(m1, rows, cols);
        printf("Matrix 2:\n");
        print(m2, rows, cols);
    }

    free2d(&m1);
    free2d(&m2);

    GET_TIME(end);
    elapsed = end - start;
    printf("This program took %e seconds.\n", elapsed);

    return 0;
}
