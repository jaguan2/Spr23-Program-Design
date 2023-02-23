#include <stdio.h>
#define N 10

void find_two_largest(int arr[], int n, int *largest, int *second_largest);

//find the largest and the second largest value in an array

int main()
{
	int i, max, second_max;
	int a[N];

	printf("Enter %d elements for the arary: ", N);


	for(i=0;i<N;i++)
		scanf("%d", &a[i]);

	find_two_largest(a, N, &max, &second_max);


	printf("the largest value is: %d and the second largest is: %d\n", max, second_max);

	return 0;

}

void find_two_largest(int a[], int n, int *largest, int *second_largest)
{
    int i, max, max2;

    if (a[0] > a[1]) {
            max = a[0];
            max2 = a[1];
        }
        else{
            max = a[1];
            max2 = a[0];
        }


    for(i=2;i<N;i++){
        if (a[i] > max) {
            max2 = max;
            max = a[i];
	}
        else if (a[i] > max2){
            max2= a[i];

    }
    }
    *largest = max;
    *second_largest = max2;
}

