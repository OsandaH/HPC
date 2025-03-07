#include <stdio.h>
#include <omp.h>

int main() {
    int n = 1000;
    int sum = 0;
    #pragma omp parallel
    {
        int thread_sum = 0;
        #pragma omp for
        for (int i = 1; i <= n; i++) {
            thread_sum += i;
        }
        #pragma omp critical
        sum += thread_sum;
    }
    printf("The sum of the first %d integers is %d\n", n, sum);
    return 0;
}
