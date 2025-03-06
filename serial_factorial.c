#include <iostream>

int main(){
	int tot = 1;
	int n;
    printf("Enter the number of integers to calculate the factorial: ");
    scanf("%d", &n);
	
	int i;
	
	for(i=1;i<=n;i++){
		tot *= i ;
	}
	printf("Factorial of the 1st %d  elements %d\n",n,tot);

	return 0;

}
