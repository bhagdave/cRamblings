#include <stdio.h>

void swap(int *x, int *y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void print_array(int arr[], int size){
    for(int i=0; i<size; i++){
        printf("%d ", arr[i]);
    }
    printf("\n---------------\n");
}

int find_smallest(int arr[], int elements){
    int smallest = arr[0];
    int smallest_index = 0;

    for (int i=0; i < elements; i++){
        if (arr[i] < smallest){
            smallest = arr[i];
            smallest_index = i;
        }
    }
    return smallest_index;
}

void selection_sort(int arr[], int elements){
    int smallest;
    
    for (int i=0; i < elements - 1; i++){
        smallest = i;
        for (int j=i+1; j < elements; j++){
            if (arr[j] < arr[smallest])
                smallest = j;
        }
        swap(&arr[smallest], &arr[i]);
    }
}


void main(){
    int array[] = {11,13,25,7,8,3,4,15,6,20};
    int elements = 10;
    int smallest;

    smallest = find_smallest(array, elements);
    printf("The smallest index is %d\n", smallest);

    printf("Un-Sorted array\n");
    print_array(array, elements);
    selection_sort(array, elements);
    printf("Sorted array\n");
    print_array(array, elements);
}
