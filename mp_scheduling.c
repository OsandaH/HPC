// without scheduling 
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100000000

int main() {
    double x = 0.0;
	double start_time, end_time;
	
    int num_threads = 12;       
    int inside = 0;
	
	start_time = omp_get_wtime();
	
    #pragma omp parallel for num_threads(num_threads) reduction(+:inside)
    for (int i = 0; i < N; i++) {
        double x = (double) rand() / RAND_MAX;
        double y = (double) rand() / RAND_MAX;
		
		
        if (x * x + y * y <= 1.0) {
			#pragma omp atomic
            inside++;
        }
		
    }
	end_time = omp_get_wtime();

    double pi_val = 4.0 * inside / N;
    printf("Estimated value of Pi (without scheduling): %.6f \n", pi_val);
	printf("Time taken %f seconds \n ",end_time - start_time);

    return 0;
}


// // statc scheduling 
// #include <omp.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define N 100000000

// int main() {
//     double x = 0.0;
// 	double start_time, end_time;
	
//     int num_threads = 12;       
//     int inside = 0;
	
// 	start_time = omp_get_wtime();
	
//     #pragma omp parallel for schedule(static,100) num_threads(num_threads) reduction(+:inside)
//     for (int i = 0; i < N; i++) {
//         double x = (double) rand() / RAND_MAX;
//         double y = (double) rand() / RAND_MAX;
		
		
//         if (x * x + y * y <= 1.0) {
// 			#pragma omp atomic
//             inside++;
//         }
		
//     }
// 	end_time = omp_get_wtime();

//     double pi_val = 4.0 * inside / N;
//     printf("Estimated value of Pi (static scheduling): %.6f \n", pi_val);
// 	printf("Time taken %f seconds \n ",end_time - start_time);

//     return 0;
// }

//// guided scheduling 
// #include <omp.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define N 100000000

// int main() {
//     double x = 0.0;
// 	double start_time, end_time;
	
//     int num_threads = 12;       
//     int inside = 0;
	
// 	start_time = omp_get_wtime();
	
//     #pragma omp parallel for schedule(guided,10000) num_threads(num_threads) reduction(+:inside)
//     for (int i = 0; i < N; i++) {
//         double x = (double) rand() / RAND_MAX;
//         double y = (double) rand() / RAND_MAX;
		
		
//         if (x * x + y * y <= 1.0) {
// 			#pragma omp atomic
//             inside++;
//         }
		
//     }
// 	end_time = omp_get_wtime();

//     double pi_val = 4.0 * inside / N;
//     printf("Estimated value of Pi (guided scheduling): %.6f \n", pi_val);
// 	printf("Time taken %f seconds \n ",end_time - start_time);

//     return 0;
// }

//// Dynamic scheduling 
// #include <omp.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <math.h>

// #define N 100000000

// int main() {
//     double x = 0.0;
// 	double start_time, end_time;
	
//     int num_threads = 12;       
//     int inside = 0;
	
// 	start_time = omp_get_wtime();
	
//     #pragma omp parallel for schedule(dynamic,10000) num_threads(num_threads) reduction(+:inside)
//     for (int i = 0; i < N; i++) {
//         double x = (double) rand() / RAND_MAX;
//         double y = (double) rand() / RAND_MAX;
		
		
//         if (x * x + y * y <= 1.0) {
// 			#pragma omp atomic
//             inside++;
//         }
		
//     }
// 	end_time = omp_get_wtime();

//     double pi_val = 4.0 * inside / N;
//     printf("Estimated value of Pi (dynamic scheduling): %.6f \n", pi_val);
// 	printf("Time taken %f seconds \n ",end_time - start_time);

//     return 0;
// }


