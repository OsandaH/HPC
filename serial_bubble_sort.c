#include <stdio.h>

//bubble sort function
void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
//print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {23, 45, 67, 12, 89, 34, 56, 78, 90, 11, 45, 67, 89, 12, 34, 56, 78, 90, 11, 23, 67, 89, 12, 34, 
                56, 78, 90, 11, 23, 45, 89, 12, 34, 56, 78, 90, 11, 23, 45, 67, 12, 34, 56, 78, 90, 11, 23, 45, 
                67, 89, 34, 56, 78, 90, 11, 23, 45, 67, 89, 12, 56, 78, 90, 11, 23, 45, 67, 89, 12, 34, 78, 90, 
                11, 23, 45, 67, 89, 12, 34, 56, 90, 11, 23, 45, 67, 89, 12, 34, 56, 78, 11, 23, 45, 67, 89, 12, 
                34, 56, 78, 90} ;
                
    int n = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, n);
    
    printf("Sorted array: \n");
    printArray(arr, n);
    
    return 0;
}
