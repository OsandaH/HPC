// insertion sort 
#include <stdio.h>
#include <time.h>

void insertionSort(int arr[], int n){
    for (int i=1; i< n; i++){
        int key = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j]> key){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}
int main() {
    int arr[] = {262,485,618,753,584,477,697,465,908,846,489,
        324,659,324,552,604,775,498,393,758,424,44,12,866,891,675,
        434,360,711,240,18,49,38,761,962,3,381,839,553,768,926,774,
        545,46,541,231,670,660,218,536,945,134,804,552,747,964,922,614,
        378,805,132,214,689,12};

    int size = sizeof(arr)/sizeof(arr[0]);
    clock_t start, end;
    start = clock();
    insertionSort(arr,size);
    for (int i = 0; i < size; i++) { 
        printf("%d ", arr[i]); 
    } 
    end = clock(); 
     
    double time_serial = ((double)(end - start)) / CLOCKS_PER_SEC; 
    printf("\nExecution time(serial): %f seconds\n", time_serial); 
 
    return 0; 
}
