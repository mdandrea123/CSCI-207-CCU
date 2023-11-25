//Author: Michael Dandrea
//Class: CSCI 207
//Date: 11/10/2023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utilities.h"

 // Main function that encodes a hex number using Hamming code (7,4).
int main(int argc, char **argv)
{
    // Check the command line input
    check_input(argc, argv);

    // Define the generator matrix G for Hamming code (7,4).
    dtype G[7][4] = {
        {1, 1, 0, 1},
        {1, 0, 1, 1},
        {1, 0, 0, 0},
        {0, 1, 1, 1},
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1}};

    // Allocate memory for a dynamically allocated 2D array G2 and copy the values of G into it.
    dtype **G2 = NULL;
    allocate2d(&G2, 7, 4);
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            G2[i][j] = G[i][j];
        }
    }

    // Convert the input hexadecimal number to decimal.
    char *hex = argv[1];
    int decimal = strtol(hex, NULL, 16);

    // Convert the decimal number to binary and store it in a 2D array binary2.
    int binary[4][1];
    for (int i = 3; i >= 0; i--)
    {
        binary[i][0] = decimal % 2;
        decimal /= 2;
    }
    int **binary2 = NULL;
    allocate2d(&binary2, 4, 1);
    for (int i = 0; i < 4; i++)
    {
        binary2[i][0] = binary[i][0];
    }

    // Multiply the binary number by the generator matrix G2 to obtain the codeword.
    int **result = NULL;
    allocate2d(&result, 7, 1);
    mul_matrix(G2, binary2, result, 7, 1, 4);

    // Take the modulo-2 of each element in the codeword.
    for (int i = 0; i < 7; i++)
    {
        result[i][0] = result[i][0] % 2;
    }

    // Convert the codeword from binary to decimal.
    int res = result_to_int(result, 7);

    // Print the codeword in hexadecimal and binary formats.
    printf("CODEWORD = 0x%02X = 0b", res);
    for (int i = 0; i < 7; i++)
    {
        printf("%d", result[i][0]);
    }
    printf("\n");
    
    // Free the dynamically allocated memory.
    free2d(&G2);
    free2d(&binary2);
    free2d(&result);
    
    return 0;
}
