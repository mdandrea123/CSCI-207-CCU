#ifndef UTILITIES_H
#define UTILITIES_H

#define dtype int
// Function prototypes
void fcheck(FILE *fp);
void allocate2d(int ***A, int rows, int cols);
void free2d(int ***A);
void initialize(dtype **A, int rows, int cols, int min, int max);
void write_to_file(dtype **A, int rows, int cols, char *fname);
void initialize_from_file(dtype ***A, int *rows, int *cols, char *fname);
void print(dtype **A, int rows, int cols);
void check_size(char *aname, char *bname);
void add_matrices(dtype **A, dtype **B, dtype **C, int rows, int cols, char *fname);
void row_checksum(dtype **A, dtype **B, int rows, int cols);
void col_checksum(dtype **A, dtype **B, int rows, int cols);
void matrix_checksum(dtype **A, dtype **B, dtype **C, int rows, int cols);
void mul_matrix(dtype **A, dtype **B, dtype **C, int rows, int bcols, int acols);
#endif
