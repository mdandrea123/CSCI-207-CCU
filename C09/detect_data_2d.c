// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/18/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char **argv){
    char *infile = NULL;
    int pflag = 0;
    parseDetect(argc, argv, &infile, &pflag);

    if(infile == NULL){
        printf("Usage: [-p] -i <in file>\n");
        exit(1);
    }

    double start, end, elapsed;
    dtype **m1 = NULL;
    int rows = 0;
    int cols = 0;

    GET_TIME(start);
    initialize_from_file(&m1, &rows, &cols, infile);
    // print(m1, rows, cols);
    detect(m1, rows, cols);
    if(pflag){
        print(m1, rows, cols);
    }
    free2d(&m1);
    GET_TIME(end);
    elapsed = end - start;
    printf("The program took %e seconds.\n", elapsed);
    return 0;
}
