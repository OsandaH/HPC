#include <stdio.h> 
 
int main() { 
    // Define matrix A and vector v 
    int A[3][3] = { 
        {1, 2, 2}, 
        {0, 2, 0}, 
        {0, 0, 0} 
    }; 
    int v[3] = {4, 0, 1}; 
    int u[3] = {0, 0, 0}; 
 
    // Compute u = A * v 
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) { 
            u[i] += A[i][j] * v[j]; 
        } 
    } 
    // Output matrix A 
    printf("Matrix A:\n"); 
    for (int i = 0; i < 3; i++) { 
        for (int j = 0; j < 3; j++) { 
            printf("%d ", A[i][j]); 
        } 
        printf("\n"); 
    } 
    // Output vector v 
    printf("Vector v:\n"); 
    for (int i = 0; i < 3; i++) { 
        printf("%d ", v[i]); 
    } 
    printf("\n"); 
 
    // Output result vector u 
    printf("Result vector u = Av:\n"); 
    for (int i = 0; i < 3; i++) { 
        printf("%d ", u[i]); 
    } 
    printf("\n"); 
 
    return 0; 
}
