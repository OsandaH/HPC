#include <stdio.h> 
#include <omp.h> 
double simpsons_one_third_rule(double a, double b, int n, double (*f)(double)) { 
    if (n % 2 != 0) { 
        n += 1; 
    } 
    double h = (b - a) / n; 
    double sum = f(a) + f(b); 
 
    for (int i = 1; i < n; ++i) { 
        double x = a + i * h; 
        if (i % 2 == 0) { 
            sum += 2 * f(x);  
        } else { 
            sum += 4 * f(x); 
        } 
    } 
    return (h / 3.0) * sum; // Final integral value 
} 
 
double f(double x) { 
    return x * x * x + 10 * x + 1; 
} 
 
int main() { 
    double a = 0.0; 
    double b = 2.0; 
    int n = 1000; 
    double result = 0.0; 
     
    #pragma omp parallel 
    { 
        int id = omp_get_thread_num(); 
        int num_threads = omp_get_num_threads(); 
        double h = (b - a) / num_threads; 
         
        double a1 = a + id * h; 
        double b1 = a1 + h; 
         
        double local_result = simpsons_one_third_rule(a1, b1, n, f); 
         
        #pragma omp critical 
        result += local_result;  
         
    } 
    printf("The approximate value (when n = %d) of the integral is: %f \n",n, result); 
     
    return 0; 
} 
