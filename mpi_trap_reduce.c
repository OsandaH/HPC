#include <stdio.h>
#include <mpi.h>

// Function to be integrated (declare before use)
double f(double x);

// Function to compute the integral using the trapezoidal rule
double trapezoidal_rule(double a, double b, int n) {
    double h = (b - a) / n;
    double sum = (f(a) + f(b)) / 2.0;
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    return sum * h;
}

// Function to be integrated
double f(double x) {
    return 4.0 / (1.0 + x * x);  // Example: Computes π using integral of 4/(1 + x²) from 0 to 1
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double a = 0.0;    // Lower limit of integration
    double b = 1.0;    // Upper limit of integration
    int n = 1000000;   // Number of trapezoids
    double h = (b - a) / n; // Width of each trapezoid

    // Calculate local partial integral
    double local_a = a + rank * (b - a) / size;
    double local_b = a + (rank + 1) * (b - a) / size;
    double local_integral = trapezoidal_rule(local_a, local_b, n / size);

    // Use MPI_Reduce to combine local integrals into a global result
    double global_integral;
    MPI_Reduce(&local_integral, &global_integral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Print the result in process 0
    if (rank == 0) {
        printf("Result of integration: %.12f\n", global_integral);
    }

    MPI_Finalize();
    return 0;
}
