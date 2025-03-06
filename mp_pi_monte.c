#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int num_points = 1000000;  
    int num_threads = 4;       
    int inside = 0;

    #pragma omp parallel for num_threads(num_threads) reduction(+:inside)
    for (int i = 0; i < num_points; i++) {
        double x = (double) rand() / RAND_MAX;
        double y = (double) rand() / RAND_MAX;
		
		#pragma omp critical
        if (x * x + y * y <= 1.0) {
            inside++;
        }
		
    }

    double pi_val = 4.0 * inside / num_points;
    printf("Estimated value of Pi: %.6f (Number of points = %d ) \n", pi_val,num_points);

    return 0;
}
