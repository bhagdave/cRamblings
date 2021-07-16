#include <stdio.h>

void swap(int *x, int *y){
    printf("-- SWAPPING -- ");
    int temp = *x;
    *x = *y;
    *y = temp;
}

void print_array(int arr[], int size){
    printf("\n---------------\n");
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n---------------\n");
}

int partition(int arr[], int low, int high){
    printf("Partition with low of %d and high of %d\n", low, high);
    int pivot = arr[high]; // start at the last element as the pivot
    int i = (low - 1); // comparison

    for (int j = low; j <= high - 1; j++){ // llop from beginning of arrau
        if (arr[j] <= pivot){ // if current element lower than pivot value
            i++; // increase i to point to element to swap with
            if (i != j){ // only swop if the indexes do not match
                printf("Calling swop with %d and  %d\n", i, j);
                swap(&arr[i], &arr[j]); // swop the elements - Bubbles higher value up for final swap
                print_array(arr,10);
            }
        }
    }
    if ((i + 1) != high){
        printf("**** Final swop with %d and  %d\n", i + 1, high);
        swap(&arr[i + 1], &arr[high]);
        print_array(arr,10);
    }
    return ( i + 1);
}

int * quick_sort(int arr[], int low, int high){
    printf("------------------------------------------\n");
    printf("quick_sort low=%d, high=%d\n", low, high);
    printf("------------------------------------------\n");
    if (low < high){
        int p1 = partition(arr, low, high);
        printf("Calling qsort with low of %d and high of %d\n", low, p1-1);
        quick_sort(arr, low, p1 -1);
        print_array(arr, 10);
        printf("Calling qsort with low of %d and high of %d\n", p1 + 1, high);
        quick_sort(arr, p1 + 1, high);
        printf(">>>>>>>");
        print_array(arr, 10);
    }
}

void main(){
    int array[] = {11,13,25,7,8,3,4,15,6,20};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Unsorted\n");
    print_array(array, n);
    quick_sort(array, 0, n-1);
    printf("sorted\n");
    print_array(array, n);
}
