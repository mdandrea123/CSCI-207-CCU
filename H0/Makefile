CC = gcc
CFLAGS = -std=gnu99 -g -Wall -Wpedantic

# List of source files
SRCS = make_data_2d.c read_data_2d.c add_data_2d.c utilities.c cs_rows_data_2d.c cs_cols_data_2d.c cs_data_2d.c mul_data_2d.c corrupt_data_2d.c detect_data_2d.c correct_data_2d.c simple_mbe_test.c mul_data_2d_faulty.c ham-encode-4.c

# List of object files (automatically generated from source files)
OBJS = $(SRCS:.c=.o)

# Executable names
PROGS = make_data_2d read_data_2d add_data_2d cs_rows_data_2d cs_cols_data_2d cs_data_2d mul_data_2d corrupt_data_2d detect_data_2d correct_data_2d simple_mbe_test mul_data_2d_faulty ham-encode-4

# Default target
all: $(PROGS)

# Compile rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile rule for utilities.o
utilities.o: utilities.c
	$(CC) $(CFLAGS) -c $< -o $@

# Compile rule for each program
make_data_2d: make_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

read_data_2d: read_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

add_data_2d: add_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

cs_rows_data_2d: cs_rows_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

cs_cols_data_2d: cs_cols_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

cs_data_2d: cs_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

mul_data_2d: mul_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

corrupt_data_2d: corrupt_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm	

detect_data_2d: detect_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

correct_data_2d: correct_data_2d.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

simple_mbe_test: simple_mbe_test.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

mul_data_2d_faulty: mul_data_2d_faulty.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

ham-encode-4: ham-encode-4.o utilities.o
	$(CC) $(CFLAGS) -o $@ $^ -lm
# Clean up object files and executables
clean:
	rm -f $(OBJS) $(PROGS) *.dat *.out A B C *.csv
