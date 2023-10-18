// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/2/2023
// Updated: 10/16/2023
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "timer.h"

// Function to check if a file pointer is valid (not NULL).
// If it's not valid, it prints an error message and exits the program.
void fcheck(FILE *fp)
{
    if (!fp)
    {
        perror("Error opening file: ");
        exit(1);
    }
}

// Function to allocate a 2D integer array dynamically.
// It takes a pointer to a pointer to int, the number of rows, and the number of columns as input and allocates memory for the 2D array.
void allocate2d(int ***A, int rows, int cols)
{
    int header = rows * sizeof(int *);
    int data = rows * cols * sizeof(int);
    *A = (int **)malloc(header + data);
    if (!*A)
    {
        perror("Error allocating memory: ");
    }
    int *array_data = (int *)((*A) + rows);
    for (int i = 0; i < rows; i++)
    {
        (*A)[i] = array_data + i * cols;
    }
}

// Function to free the memory allocated for a 2D integer array.
// It takes a pointer to a pointer to int as input and sets it to NULL after freeing the memory.
void free2d(int ***A)
{
    free(*A);
    *A = NULL;
}

// Function to initialize a 2D array with random values between 'min' and 'max'.
// It takes a pointer to a 2D array, the number of rows, columns, 'min', and 'max' as input.
void initialize(dtype **A, int rows, int cols, int min, int max)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            A[i][j] = min + rand() % (max - min + 1);
        }
    }
}

// Function to write a 2D array to a binary file.
// It takes a pointer to a 2D array, the number of rows, columns, and a file name as input.
void write_to_file(dtype **A, int rows, int cols, char *fname)
{
    FILE *f = fopen(fname, "w");
    fcheck(f);

    int num_items;

    num_items = fwrite(&rows, sizeof(int), 1, f);
    if (num_items != 1)
    {
        perror("Error writing to file: ");
        fclose(f);
        exit(1);
    }

    num_items = fwrite(&cols, sizeof(int), 1, f);
    if (num_items != 1)
    {
        perror("Error writing ti file: ");
        fclose(f);
        exit(1);
    }

    num_items = fwrite(A[0], sizeof(dtype), rows * cols, f);
    if (num_items != rows * cols)
    {
        perror("Error writing to file: ");
        fclose(f);
        exit(1);
    }

    if (fclose(f) != 0)
    {
        perror("Error closing file: ");
        exit(1);
    }
}

// Function to initialize a 2D array from a binary file.
// It takes a pointer to a pointer to a 2D array, pointers to the number of rows and columns, and a file name as input.
void initialize_from_file(dtype ***A, int *rows, int *cols, char *fname)
{
    FILE *f = fopen(fname, "r");
    fcheck(f);

    if (fread(rows, sizeof(int), 1, f) != 1)
    {
        perror("Error reading number of rows: ");
        fclose(f);
        exit(1);
    }
    if (fread(cols, sizeof(int), 1, f) != 1)
    {
        perror("Error reading number of columns: ");
        fclose(f);
        exit(1);
    }

    // Allocate memory for the 2D array and read the data from the file into it.
    allocate2d(A, *rows, *cols);
    size_t read = fread((*A)[0], sizeof(dtype), (*rows) * (*cols), f);
    if (read != (size_t)((*rows) * (*cols)))
    {
        perror("Error reading data from file: ");
        fclose(f);
        exit(1);
    }

    if (fclose(f) != 0)
    {
        perror("Error closing file: ");
        exit(1);
    }
}

// Function to print a 2D array.
// It takes a pointer to a 2D array, the number of rows, and columns as input and prints the elements.
void print(dtype **A, int rows, int cols)
{
    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < cols; j++)
    //     {
    //     //     if(A[i][j] < 10)
    //     //     {
    //             printf("%d ", A[i][j]);
    //         // }else{
    //         //     printf("%d%d ", A[i][j] / 10, A[i][j] % 10);
    //         // }
    //     }
    //     printf("\n");
    // }

    int maxDigits[cols]; // Array to store the maximum width for each column
    
    // Initialize maxDigits with 0 for each column
    for (int j = 0; j < cols; j++)
    {
        maxDigits[j] = 0;
    }

    // Calculate the maximum width required for each column
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int numDigits = snprintf(NULL, 0, "%d", A[i][j]);
            if (numDigits > maxDigits[j])
            {
                maxDigits[j] = numDigits;
            }
        }
    }

    // Print the matrix with aligned numbers
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%*d ", maxDigits[j], A[i][j]);
        }
        printf("\n");
    }
}

// Function to check if two binary files have the same size (rows and columns).
// It takes the file names of two binary files as input.
void check_size(char *aname, char *bname)
{
    FILE *afile = fopen(aname, "r");
    FILE *bfile = fopen(bname, "r");

    fcheck(afile);
    fcheck(bfile);

    int arows, acols, brows, bcols;

    if (fread(&arows, sizeof(int), 1, afile) != 1)
    {
        perror("Error reading number of rows: ");
        fclose(afile);
        exit(1);
    }
    if (fread(&acols, sizeof(int), 1, afile) != 1)
    {
        perror("Error reading number of columns: ");
        fclose(afile);
        exit(1);
    }
    if (fread(&brows, sizeof(int), 1, bfile) != 1)
    {
        perror("Error reading number of rows: ");
        fclose(bfile);
        exit(1);
    }
    if (fread(&bcols, sizeof(int), 1, bfile) != 1)
    {
        perror("Error reading number of columns: ");
        fclose(bfile);
        exit(1);
    }
    if ((arows != brows) || (acols != bcols))
    {
        printf("Error: Matrices must be the same size.");
        exit(1);
    }

    if (fclose(afile) != 0)
    {
        perror("Error closing file: ");
        exit(1);
    }
    if (fclose(bfile) != 0)
    {
        perror("Error closing file: ");
        exit(1);
    }
}

// Function to add two matrices element-wise and write the result to a binary file.
// It takes two input matrices, an output matrix, the number of rows, columns, and a file name.
void add_matrices(dtype **A, dtype **B, dtype **C, int rows, int cols, char *fname)
{
    FILE *f = fopen(fname, "w");
    fcheck(f);
    int num_items;

    num_items = fwrite(&rows, sizeof(int), 1, f);
    if (num_items != 1)
    {
        perror("Error writing to file: ");
        fclose(f);
        exit(1);
    }
    num_items = fwrite(&cols, sizeof(int), 1, f);
    if (num_items != 1)
    {
        perror("Error writing to file: ");
        fclose(f);
        exit(1);
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    num_items = fwrite(C[0], sizeof(dtype), rows * cols, f);
    if (num_items != rows * cols)
    {
        perror("Error writing to file: ");
        fclose(f);
        exit(1);
    }

    if (fclose(f) != 0)
    {
        perror("Error closing file: ");
        exit(1);
    }
}

// Function to calculate row checksums for a matrix.
// It takes an input matrix, an output matrix, the number of rows, and columns as input.
void row_checksum(dtype **A, dtype **B, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < rows; i++)
    {
        int rowsum = 0;
        for (int j = 0; j < cols; j++)
        {
            rowsum += A[i][j];
        }
        B[i][cols] = rowsum;
    }
}

// Function to calculate column checksums for a matrix.
// It takes an input matrix, an output matrix, the number of rows, and columns as input.
void col_checksum(dtype **A, dtype **B, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < cols; i++)
    {
        int colsum = 0;
        for (int j = 0; j < rows; j++)
        {
            colsum += A[j][i];
        }
        B[rows][i] = colsum;
    }
}

// Function to calculate matrix checksums for a matrix.
// It takes two input matrices, an output matrix, the number of rows, and columns as input.
void matrix_checksum(dtype **A, dtype **B, dtype **C, int rows, int cols)
{
    row_checksum(A, B, rows, cols);
    col_checksum(B, C, rows, cols + 1);
}

// Function to perform matrix multiplication and store the result in C.
// It takes two input matrices, an output matrix, and the number of rows and columns as input.
// The driver program checks to see if the martices are the correct size before continuing.
void mul_matrix(dtype **A, dtype **B, dtype **C, int rows, int bcols, int acols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < bcols; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < acols; k++)
            {
                C[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
}
