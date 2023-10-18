#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"

void initialize(double h[NX][NY], double u[NX][NY], double v[NX][NY]) {
    // Center coordinates
    double x_center = L_X / 2.0;
    double y_center = L_Y / 2.0;

    // Radius of the circular bump
    double r_bump = 10.0;  // You can adjust this as needed

    // Constant height of the bump
    double h_bump = 3.0;  // You can adjust this as needed

    // Initialize velocities to zero and height to zero everywhere
	 double elsewhere = 1.0;
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            u[i][j] = elsewhere;
            v[i][j] = elsewhere;
            h[i][j] = elsewhere;
        }
    }

    // Set the heights inside the circle to h_bump
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            double x = i * L_X / (NX - 1);
            double y = j * L_Y / (NY - 1);

            // Calculate distance from the center
            double distance = sqrt((x - x_center) * (x - x_center) + (y - y_center) * (y - y_center));

            // If the point is inside the circular bump
            if (distance < r_bump) {
                h[i][j] = h_bump;
            }
        }
    }
}

void write_to_file(const char *filename, double h[NX][NY], double u[NX][NY], double v[NX][NY], double dt, int total_timesteps, int current_timestep) {
    FILE *file;
    
    if (current_timestep == 0) {
        // For the first timestep, open the file in write mode and write the metadata
        file = fopen(filename, "w");
        fprintf(file, "# NX: %d NY: %d L_X: %.2lf L_Y: %.2lf DT: %.2lf NT: %d\n", NX, NY, L_X, L_Y, dt, total_timesteps);
    } else {
        // For subsequent timesteps, append to the existing file
        file = fopen(filename, "a");
    }

    // Write the timestep comment and then the data
    fprintf(file, "# Timestep: %d\n", current_timestep);
    for (int i = 0; i < NX; i++) {
        for (int j = 0; j < NY; j++) {
            fprintf(file, "%d %d %.5lf %.5lf %.5lf\n", i, j, h[i][j], u[i][j], v[i][j]);
        }
    }
    fclose(file);
}


void simulate(double h[NX][NY], double u[NX][NY], double v[NX][NY], double dt) {
    // Function to evolve the system by one time step using the shallow water equations
    int i, j;
    double hx[NX][NY], ux[NX][NY], vx[NX][NY], hy[NX][NY], uy[NX][NY], vy[NX][NY];

    // 1. Compute fluxes in x-direction
    for (i = 0; i < NX - 1; i++) {
        for (j = 0; j < NY; j++) {
            double h_avg = 0.5 * (h[i][j] + h[i+1][j]);
            double u_avg = 0.5 * (u[i][j] + u[i+1][j]);
            double v_avg = 0.5 * (v[i][j] + v[i+1][j]);
            hx[i][j] = h_avg * u_avg;
            ux[i][j] = h_avg * u_avg * u_avg + 0.5 * GRAVITY * h_avg * h_avg;
            vx[i][j] = h_avg * u_avg * v_avg;
        }
    }

    // Compute fluxes in y-direction
    for (i = 0; i < NX; i++) {
        for (j = 0; j < NY - 1; j++) {
            double h_avg = 0.5 * (h[i][j] + h[i][j+1]);
            double u_avg = 0.5 * (u[i][j] + u[i][j+1]);
            double v_avg = 0.5 * (v[i][j] + v[i][j+1]);
            hy[i][j] = h_avg * v_avg;
            uy[i][j] = h_avg * u_avg * v_avg;
            vy[i][j] = h_avg * v_avg * v_avg + 0.5 * GRAVITY * h_avg * h_avg;
        }
    }

    // 2. Reflective boundary conditions
    for (i = 0; i < NX; i++) {
        // Top boundary
        h[i][0] = h[i][1];
        u[i][0] = u[i][1];
        v[i][0] = -v[i][1];  // Reflective for v-velocity
        
        // Bottom boundary
        h[i][NY-1] = h[i][NY-2];
        u[i][NY-1] = u[i][NY-2];
        v[i][NY-1] = -v[i][NY-2];  // Reflective for v-velocity
    }

    for (j = 0; j < NY; j++) {
        // Left boundary
        h[0][j] = h[1][j];
        u[0][j] = -u[1][j];  // Reflective for u-velocity
        v[0][j] = v[1][j];
        
        // Right boundary
        h[NX-1][j] = h[NX-2][j];
        u[NX-1][j] = -u[NX-2][j];  // Reflective for u-velocity
        v[NX-1][j] = v[NX-2][j];
    }

    // 3. Update values using fluxes
    for (i = 1; i < NX - 1; i++) {
        for (j = 1; j < NY - 1; j++) {
            h[i][j] = h[i][j] - dt * (hx[i][j] - hx[i-1][j] + hy[i][j] - hy[i][j-1]);
            u[i][j] = u[i][j] - dt * (ux[i][j] - ux[i-1][j] + uy[i][j] - uy[i][j-1]);
            v[i][j] = v[i][j] - dt * (vx[i][j] - vx[i-1][j] + vy[i][j] - vy[i][j-1]);
        }
    }
}
