#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void createArrayFromInput(int length);
void createArrayWithRandomNumbers(int* arr, int length);
void printArray(int arr[], int length);
void runTests();

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("You must pass -i (interactive)");
        exit(1);
    }

    if (strcmp("-i", argv[1]) == 0) {
        int length = 10;
        createArrayFromInput(length);

        int arr[length];
        createArrayWithRandomNumbers(arr, length);
        printf("Array with Random Numbers:\n");
        printArray(arr, length);
    } else {
        printf("You must pass -i to run the program");
    }
}

void createArrayWithRandomNumbers(int* arr, int length) {
    srand(time(NULL));

    for (int i = 0; i < length; i++) {
        arr[i] = rand();
    }
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

