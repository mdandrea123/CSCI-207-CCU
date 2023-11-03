// Author: Michael Dandrea
// Class: CSCI 207
// Date: 10/2/2023
// Updated: 11/1/2023
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

void parseAdd(int argc, char *argv[], char **afile, char **bfile, char **outfile, int *pFlag)
{
    *afile = NULL;
    *bfile = NULL;
    *outfile = NULL;
    *pFlag = 0; // Initialize the print flag to 0 (off).

    int opt;
    while ((opt = getopt(argc, argv, "a:b:c:p")) != -1)
    {
        switch (opt)
        {
        case 'a':
            *afile = optarg;
            break;
        case 'b':
            *bfile = optarg;
            break;
        case 'c':
            *outfile = optarg;
            break;
        case 'p':
            *pFlag = 1; // Set the print flag to 1 if the '-p' option is provided.
            break;
        default:
            printf("Usage: %s-a <in file1> -b <in file2> -c <out filename> [-p]\n", argv[0]);
            exit(1);
        }
    }
}

void parseCols(int argc, char **argv, char **infile, char **outfile, int *pflag)
{
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:o:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            *pflag = 1;
            break;
        case 'i':
            *infile = optarg;
            break;
        case 'o':
            *outfile = optarg;
            break;
        default:
            printf("Usage: %s -i <in file> -o <out filename> [-p]", argv[0]);
            exit(1);
        }
    }
}

void parseData(int argc, char **argv, char **infile, char **outfile, int *pFlag)
{
    // Declare variables for command line arguments
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:o:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            *pFlag = 1;
            break;
        case 'i':
            *infile = optarg;
            break;
        case 'o':
            *outfile = optarg;
            break;
        default:
            printf("Usage: %s -i <in file> -o <out filename> [-p]\n", argv[0]);
            exit(1);
        }
    }
}

void parseRows(int argc, char **argv, char **infile, char **outfile, int *pFlag)
{
    // Declare variables for command line arguments
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:o:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            *pFlag = 1;
            break;
        case 'i':
            *infile = optarg;
            break;
        case 'o':
            *outfile = optarg;
            break;
        default:
            printf("Usage: %s -i <in file> -o <out filename> [-p]\n", argv[0]);
            exit(1);
        }
    }
}

void parseMake(int argc, char *argv[], int *rows, int *cols, int *min, int *max, char **fname, int *printFlag)
{
    *rows = 3; // Default value for rows.
    *cols = 4; // Default value for cols.
    *min = 0;  // Default value for min.
    *max = 9;  // Default value for max.

    int opt;
    while ((opt = getopt(argc, argv, "r:c:l:h:o:p")) != -1)
    {
        switch (opt)
        {
        case 'r':
            *rows = atoi(optarg);
            break;
        case 'c':
            *cols = atoi(optarg);
            break;
        case 'l':
            *min = atoi(optarg);
            break;
        case 'h':
            *max = atoi(optarg);
            break;
        case 'o':
            *fname = optarg;
            break;
        case 'p':
            *printFlag = 1;
            break;
        default:
            printf("Usage: %s -r <#rows> -c <#cols> -l <low> -h <high> -o <output filename> [-p]\n", argv[0]);
            exit(1);
        }
    }
}

void parseMult(int argc, char *argv[], char **afile, char **bfile, char **outfile, int *pFlag)
{
    *afile = NULL;
    *bfile = NULL;
    *outfile = NULL;
    *pFlag = 0; // Initialize the print flag to 0 (off).

    int opt;
    while ((opt = getopt(argc, argv, "a:b:c:p")) != -1)
    {
        switch (opt)
        {
        case 'a':
            *afile = optarg;
            break;
        case 'b':
            *bfile = optarg;
            break;
        case 'c':
            *outfile = optarg;
            break;
        case 'p':
            *pFlag = 1; // Set the print flag to 1 if the '-p' option is provided.
            break;
        default:
            printf("Usage: %s -a <in file1> -b <in file2> -c <out filename> [-p]\n", argv[0]);
            exit(1);
        }
    }
}

void parseRead(int argc, char *argv[], char **fname)
{
    *fname = NULL; // Initialize the input file name to NULL.

    int opt;
    while ((opt = getopt(argc, argv, "i:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            *fname = optarg;
            break;
        default:
            printf("Usage: %s -i <input filename> [-p]\n", argv[0]);
            exit(1);
        }
    }
}

void parseCorrupt(int argc, char **argv, char **infile, char **outfile, int *pflag, int *crow, int *ccol, int *cbit)
{
    int opt;

    // Parse command line arguments using getopt
    while ((opt = getopt(argc, argv, "pi:o:x:y:z:")) != -1)
    {
        switch (opt)
        {
        case 'p':
            *pflag = 1;
            break;
        case 'i':
            *infile = optarg;
            break;
        case 'o':
            *outfile = optarg;
            break;
        case 'x':
            *crow = atoi(optarg);
            break;
        case 'y':
            *ccol = atoi(optarg);
            break;
        case 'z':
            *cbit = atoi(optarg);
            break;
        default:
            printf("Usage: [-p] -i <in file> [-x <row index>] [-y <col index>] [-z <bit position>] -o <output filename>\n");
            exit(1);
        }
    }
}

void parseDetect(int argc, char **argv, char **infile, int *pflag)
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
            printf("Usage: [-p] -i <in file>\n");
            exit(1);
        }
    }
}

void parseCorrect(int argc, char **argv, char **infile, char **outfile, int *pflag)
{
    int opt;

    while ((opt = getopt(argc, argv, "pi:o:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            *infile = optarg;
            break;
        case 'o':
            *outfile = optarg;
            break;
        case 'p':
            *pflag = 1;
            break;
        default:
            printf("Usage: [-p] -i <in file> -o <out file>\n");
            exit(1);
        }
    }
}

void parseMBE(int argc, char **argv, long long *trials, int *pFlag)
{
    int opt;

    while ((opt = getopt(argc, argv, "n:p")) != -1)
    {
        switch (opt)
        {
        case 'n':
            *trials = atoi(optarg);
            break;
        case 'p':
            *pFlag = 1;
            break;
        default:
            printf("Usage: [-p] -n <number of trials>\n");
            exit(1);
        }
    }
}

void parseMultFaulty(int argc, char **argv, char **afile, char **bfile, char **outfile, int *pFlag, int *rowIndex, int *colIndex, int *bit, int *term)
{
    int opt;
    while ((opt = getopt(argc, argv, "pa:b:c:x:y:z:k:")) != -1)
    {
        switch (opt)
        {
            case 'p':
                *pFlag = 1;
                break;
            case 'a':
                *afile = optarg;
                break;
            case 'b':
                *bfile = optarg;
                break;
            case 'c':
                *outfile = optarg;
                break;
            case 'x':
                *rowIndex = atoi(optarg);
                break;
            case 'y':
                *colIndex = atoi(optarg);
                break;
            case 'z':
                *bit = atoi(optarg);
                break;
            case 'k':
                *term = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] -a <in file1> -b <in file2> -c <out filename> -x <row index> -y <col index> -z <bit position> -k <which product term in the dot product should be corrupted>\n", argv[0]);
                exit(1);
        }
    }

    if (*afile == NULL || *bfile == NULL || *outfile == NULL)
    {
        fprintf(stderr, "Usage: %s [-p] -a <in file1> -b <in file2> -c <out filename> -x <row index> -y <col index> -z <bit position> -k <which product term in the dot product should be corrupted>\n", argv[0]);
        exit(1);
    }
}


void corrupt(dtype **A, dtype **B, int rows, int cols, int crow, int ccol, int cbit)
{
     if(crow > rows || ccol > cols){
        printf("Error: Row and column position cannot be greater than the number of rows or columns respectively.");
        exit(1);
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[i][j] = A[i][j];
        }
    }

    B[crow][ccol] = B[crow][ccol] ^ (1 << cbit);
}

Index detect(dtype **A, int rows, int cols)
{
    Index index;
    int rowchecksum = 0;
    int colchecksum = 0;
    int rowsum = 0;
    int colsum = 0;
    int rowindex = -1;
    int colindex = -1;
    int bit = -1;

    for (int i = 0; i < rows; i++)
    {
        rowchecksum = A[i][cols - 1];
        rowsum = 0;
        for (int j = 0; j < cols - 1; j++)
        {
            rowsum += A[i][j];
        }
        if (rowsum != rowchecksum)
        {
            rowindex = i;
            break;
        }
    }

    for (int i = 0; i < cols; i++)
    {
        colchecksum = A[rows - 1][i];
        colsum = 0;
        for (int j = 0; j < rows - 1; j++)
        {
            colsum += A[j][i];
        }
        if (colsum != colchecksum)
        {
            colindex = i;
            break;
        }
    }

    if (rowindex != -1 && colindex != -1)
    {
        int newRowSum = rowsum - A[rowindex][colindex];
        int correctNumber = A[rowindex][cols - 1] - newRowSum;

        for (int i = 0; i < 32; i++)
        {
            if((correctNumber ^ (1 << i)) == A[rowindex][colindex]){
                bit = i;
                break;
            }
        }
        printf("Error detected at row %d, column %d and bit position %d\n", rowindex, colindex, bit);
    }
    else
    {
        printf("No error detected.\n");
    }

    index.row = rowindex;
    index.col = colindex;
    index.bit = bit;

    return index;
}

void correct(dtype **A, dtype **B, int rows, int cols)
{
    Index index = detect(A, rows, cols);
    int correctRow = index.row;
    int correctCol = index.col;
    int correctBit = index.bit;

    if (correctRow == -1 && correctCol == -1)
    {
        return;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            B[i][j] = A[i][j];
        }
    }

    B[correctRow][correctCol] = B[correctRow][correctCol] ^ (1 << correctBit);
}

void mbeTest(long long trials, int pflag) {
    if (trials < 1) {
        printf("Error: Number of trials must be greater than 0.\n");
        printf("Usage: [-p] -n <number of trials>\n");
        exit(0);
    }
    srand(time(0));
    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int c = 0;
    unsigned int bprime = 0;
    unsigned int cprime = 0;
    double masked = 0.0;
    unsigned int bit_position = 0;
    double p = 0.0;

    FILE *f = fopen("results.csv", "a+"); // Open the file in "append" mode
    fcheck(f);

    // Print the header only if the file is empty
    if (ftell(f) == 0) {
        fprintf(f, "Trials,Probability\n");
    }

    for (int i = 0; i < trials; i++) {
        a = rand() % (1LL << 32);
        b = rand() % (1LL << 32);
        c = a * b;
        bit_position = rand() % 32;
        bprime = b ^ (1 << bit_position);
        cprime = a * bprime;
        if (c == cprime) {
            masked++;
            if (pflag) {
                printf("BP = %d, A = 0x%x, B = 0x%x, C = 0x%x, B' = 0x%x, C' = 0x%x\n", bit_position, a, b, c, bprime, cprime);
            }
        }
    }
    p = masked / trials * 100;
    printf("Probability of a masked benign error: %.2f%%\n", p);

    fprintf(f, "%lld,%.2f\n", trials, p);

    if (fclose(f) != 0) {
        perror("Error closing file: ");
        exit(1);
    }
}

void mul_matrixFaulty(dtype **A, dtype **B, dtype **C, int rows, int bcols, int acols, int rowIndex, int colIndex, int bit, int term)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < bcols; j++)
        {
            C[i][j] = 0;
            for (int k = 0; k < acols; k++)
            {
                //C[i][j] += (A[i][k] * B[k][j]);
                if(i == rowIndex && j ==colIndex && k == term){
                    C[i][j] += mul_ints(A[i][k], B[k][j], bit);
                }else{
                    C[i][j] += (A[i][k] * B[k][j]);
                }
            }
        }
    }
}

int mul_ints(int Aik, int Bkj, int bit){
    int num = Aik * (Bkj ^ (1 << bit));
    return num;
}
