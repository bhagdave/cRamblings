#include<stdio.h>

/*
 * So just a nore on this binary search thing and why it spassing the mumber of elemnts to the function
 *
 * Simple because the array sent as a parameter gets changed to a pointer which has a length of int *
 * So do the sizeof in the calling function 
 *
*/ 


int binary_search(int list[], int n, int elements){
    int low = 0;
    int mid, guess;
    size_t high = elements;

    while (low <= high){
        mid = (low + high) / 2;
        guess = list[mid];
        if (guess == n){
            return mid;
        }
        if (guess > n){
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void main(){
    int line[] = {0,12,13,23,45,51,65,78,81,82};
    int answer;
    int elements;

    elements = sizeof(line) / sizeof(line[0]);
    answer = binary_search(line, 51, elements);
    printf("51 is in %d\n", answer);


}
