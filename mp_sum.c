#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 10

int main() {
    int array[] = {23, 45, 67, 12, 89, 34, 56, 78, 90, 11, 45, 67, 89, 12, 34, 56, 78, 90, 11,
23, 67, 89, 12, 34, 56, 78, 90, 11, 23, 45, 89, 12, 34, 56, 78, 90, 11, 23, 45,
67, 12, 34, 56, 78, 90, 11, 23, 45, 67, 89, 34, 56, 78, 90, 11, 23, 45, 67, 89,
12, 56, 78, 90, 11, 23, 45, 67, 89, 12, 34, 78, 90, 11, 23, 45, 67, 89, 12, 34,
56, 90, 11, 23, 45, 67, 89, 12, 34, 56, 78, 11, 23, 45, 67, 89, 12, 34, 56, 78,
90};

    int n = sizeof(array) / sizeof(array[0]); 
    int sum = 0;

    #pragma omp parallel for num_threads(NUM_THREADS) reduction(+:sum)
	
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
	

    printf("The sum of the elements is: %d\n", sum);

    return 0;
}
