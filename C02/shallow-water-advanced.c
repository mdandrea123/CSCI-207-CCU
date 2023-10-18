#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"

// Grid and domain configuration
//#define NX 50             // Number of grid points in the x direction
//#define NY 50             // Number of grid points in the y direction
#define L_X 30.0           // Length of the domain in the x direction
#define L_Y 30.0           // Length of the domain in the y direction
#define GRAVITY 9.81       // Gravitational acceleration
//#define FILENAME "simulation_data.txt"  // Name of the file where data will be written
int NX;
int NY;
int timesteps;
char* FILENAME;

int main(int argc, char** argv) {
	if (argc != 5){
		printf("Error! Usage: %s <NX> <NY> <timesteps> <filename> \n", argv[0]);
		exit(1);
	}
	NX = atoi(argv[1]);
	NY = atoi(argv[2]);
    double h[NX][NY], u[NX][NY], v[NX][NY];  // Field variables: h (height), u (velocity in x), v (velocity in y)
    double dt = 0.001;  // Time step size
    timesteps = atoi(argv[3]);  // Number of time steps
    FILENAME = argv[4]; // Filename from cli

    // Initialize the state variables
    initialize(h, u, v);

    // Write the initial conditions to the file
	 write_to_file(FILENAME, h, u, v, dt, timesteps, 0); // timestep = 0

    // Main simulation loop
    for (int t = 1; t <= timesteps; t++) {
        // Evolve the system for one time step
        simulate(h, u, v, dt);

        // Write the current state to the file
	     write_to_file(FILENAME, h, u, v, dt, timesteps, t);
    }

    return 0;
}
