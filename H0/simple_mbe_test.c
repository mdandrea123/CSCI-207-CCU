// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/30/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utilities.h"
#include "timer.h"

int main(int argc, char **argv){
    long long trials = 0;
    int pFlag = 0;
    double start, end, elapsed;

    parseMBE(argc, argv, &trials, &pFlag);

    GET_TIME(start);

    mbeTest(trials, pFlag);

    GET_TIME(end);

    elapsed = end - start;
    printf("This program took: %e seconds.\n", elapsed);

    return 0;
}
