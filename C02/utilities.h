#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Grid and domain configuration
//#define NX 50             // Number of grid points in the x direction
//#define NY 50             // Number of grid points in the y direction
#define L_X 30.0           // Length of the domain in the x direction
#define L_Y 30.0           // Length of the domain in the y direction
#define GRAVITY 9.81       // Gravitational acceleration
//#define FILENAME "simulation_data.txt"  // Name of the file where data will be written
extern int NX;
extern int NY;
extern int timesteps;
extern char* FILENAME;

// function prototypes 
void initialize(double h[NX][NY], double u[NX][NY], double v[NX][NY]);
void write_to_file(const char *filename, double h[NX][NY], double u[NX][NY], double v[NX][NY], double dt, int total_timesteps, int current_timestep);
void simulate(double h[NX][NY], double u[NX][NY], double v[NX][NY], double dt);
