#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void createArrayFromInput(int length);
void createArrayWithRandomNumbers(int length);
void printArray(int arr[], int length);

int main() {
    createArrayFromInput(10);
    createArrayWithRandomNumbers(10);
}

void createArrayWithRandomNumbers(int length) {
    int  arr[length];

    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        arr[i] = rand();
    }
    
    printf("Array with Random Numbers:\n");
    printArray(arr, length);
}

void  createArrayFromInput(int length) {
    int arr[length];
    
    for (int i = 0; i < length; i++) {
        printf("Enter a number: ");
        scanf("%d", &arr[i]);
    }

    printf("Array with Input Numbers:\n");
    printArray(arr, length);
}

void printArray(int arr[], int length) { 
    for (int i = 0; i < length; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

