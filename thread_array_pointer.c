#include <stdio.h> 
 
int main(){ 
    int numbers[] = {1, 2, 3, 4, 5}; 
    int *ptr = numbers; 
     
    int *p = &numbers[4]; 
     
    for(int i = 4; i>=0; i--){ 
        printf("Element of index %d: %d \n",i,*p); 
        p--; 
    } 
    return 0; 
} 
