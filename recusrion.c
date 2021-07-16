#include <stdio.h>

void countdown(int i){
    printf("%d-", i);
    if ( i <= 1){
        printf ("\n");
        return;
    } else
        countdown(i-1);
}

int fact(int x){
    if (x == 1)
        return 1;
    else
        return x * fact(x-1);
}

int array_sum(int arr[], int n){
    if (n < 0){
        return 0;
    } else {
        return arr[n] + array_sum(arr, n - 1);
    }
}

int array_max(int arr[], int n, int max){
    if (n < 0){
        return max;
    } else {
        if (arr[n] >= max){
            max = arr[n];
        }
        return array_max(arr, n - 1, max);
    }
}

void main(){
    int array[] = {11,13,25,7,8,3,4,15,6,20};
    int count = 100;
    int factor = 7;
    int answer;

    countdown(count);
    answer = fact(factor);
    printf("Factor of %d is %d\n", factor, answer);
    answer = array_sum(array, 9);
    printf("Sum of array is %d\n",  answer);
    answer = array_max(array, 9, 0);
    printf("Max of array is %d\n",  answer);
}
