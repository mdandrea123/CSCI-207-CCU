#ifndef UTILITIES_H
#define UTILITIES_H

#define dtype int

typedef struct {
    int row;
    int col;
    int bit;
} Index;
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
void parseAdd(int argc, char *argv[], char **afile, char **bfile, char **outfile, int *pFlag);
void parseCols(int argc, char **argv, char **infile, char **outfile, int *pflag);
void parseData(int argc, char **argv, char **infile, char **outfile, int *pFlag);
void parseRows(int argc, char **argv, char **infile, char **outfile, int *pFlag);
void parseMake(int argc, char *argv[], int *rows, int *cols, int *min, int *max, char **fname, int *printFlag);
void parseMult(int argc, char *argv[], char **afile, char **bfile, char **outfile, int *pFlag);
void parseRead(int argc, char *argv[], char **fname);
void parseCorrupt(int argc, char **argv, char **infile, char **outfile, int *pflag, int *crow, int *ccol, int *cbit);
void parseDetect(int argc, char **argv, char **infile, int *pflag);
void parseCorrect(int argc, char **argv, char **infile, char **outfile, int *pflag);
void parseMBE(int argc, char **argv, long long *trials, int *pFlag);
void parseMultFaulty(int argc, char *argv[], char **afile, char **bfile, char **outfile, int *pFlag, int *rowIndex, int *colIndex, int *bit, int *term);
void corrupt(dtype **A, dtype **B, int rows, int cols, int crow, int ccol, int cbit);
Index detect(dtype **A, int rows, int cols);
void correct(dtype **A, dtype **B, int rows, int cols);
void mbeTest(long long trials, int pflag);
void mul_matrixFaulty(dtype **A, dtype **B, dtype **C, int rows, int bcols, int acols, int rowIndex, int colIndex, int bit, int term);
int mul_ints(int Aik, int Bkj, int bit);
#endif
