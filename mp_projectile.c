#include <cmath>
#include <omp.h>
#include <stdio.h>

int main() {

    const double k = 0.1;      
    const double m = 1.0;      
    const double g = 9.8;      
    const double x0 = 1.0;     
    const double y0 = 1.0;    
    const double v0x = 20.0;   
    const double v0y = 20.0;   
    const double t_steps = 0.001;    
    const int steps = 1000;    

    double x[steps], y[steps];
    x[0] = x0;
    y[0] = y0;

    #pragma omp parallel num_threads(4)
    {
        double private_x, private_y; 
        #pragma omp for
        for (int i = 1; i < steps; i++) {
            double t = i * t_steps;

            private_x = x0 + v0x * t - (k * v0x * v0x * t * t) / (2 * m);
            private_y = y0 + v0y * t - (k * v0y * v0y * t * t) / (2 * m) - (g * t * t) / 2;

            x[i] = private_x;
            y[i] = private_y;
        }
    }
	#pragma omp critical
	{
    for (int i = 0; i < steps; i += 100) {
        printf("X(t) = %.2f\tY(t) = %.2f\n",x[i], y[i]);
        
    }
	}
    return 0;
}
