#include <stdio.h>
#include <omp.h>

int main() {
    int n;
    printf("Enter the number of integers to sum: ");
    scanf("%d", &n);
	
    int factorial = 1;
	
    #pragma omp parallel
    {
        int thread_facorial = 1;
        #pragma omp for
        for (int i = 1; i <= n; i++) {
            thread_facorial *= i;
        }
        #pragma omp critical
        factorial *= thread_facorial;
    }
    printf("The factorial of %d! is %d\n", n, factorial);
    return 0;
}
