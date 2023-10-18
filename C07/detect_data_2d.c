// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/18/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

// Function to display usage information for the program
void usage(char **argv)
{
    printf("Usage: %s -i <in file>", argv[0]);
}

void parse(int argc, char **argv, char **infile, int *pflag)
{
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:")) != -1)
    {
        switch (opt)
        {
            case 'i':
                *infile = optarg;
                break;
            case 'p':
                *pflag = 1;
                break;
            default:
                usage(argv);
                exit(1);
        }
    }
}

int main(int argc, char **argv){
    char *infile = NULL;
    int pflag = 0;
    parse(argc, argv, &infile, &pflag);

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
