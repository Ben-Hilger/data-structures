#include <stdio.h>
#include <stdlib.h>

int SIZE = 4;
int top = -1;

int* np_array;

void push();
void pop();
void show();
void resizeArray();


int main() {
    np_array = (int*) malloc(4 * sizeof(int));
    int choice;

    if (np_array == NULL) {
        printf("There was an issue allocating memory");
        exit(1);
    }

    while (1) {
        printf("\nPerform operations on the stack:");
        printf("\n1. Push the element.\n2. Pop the element.\n3. Show.\n4. End");
        printf("\n\nEnter the choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                push();
                break;
            case 2:
                pop();
                break;
            case 3:
                show();
                break;
            case 4:
                free(np_array);
                np_array = NULL;
                exit(0);
            default:
                printf("\nInvalid choice");
        }
    }
    return 0;
}

void resizeArray() {
    np_array = realloc(np_array, 2 * sizeof(&np_array));
    SIZE *= 2;
    if (np_array == NULL) {
        printf("There was an issue with reallocating the array");
        exit(1);
    }
}

void push() {
    int x;
    if (top == SIZE - 1) {
        resizeArray();
        return;
    }
    printf("\nEnter the element to be added onto the stack: ");
    scanf("%d", &x);
    top += 1;
    np_array[top] = x;
}


void pop() {
    if (top == -1) {
        printf("\nNothing to pop");
        return;
    }

    printf("\nPopped element: %d", np_array[top]);
    top -= 1;
}

void show() {
    if (top == -1) {
        printf("\nNothing to show");
        return;
    }

    printf("\nElements present in the stack: \n");
    for (int i = top; i >=- 0; i--) {
        printf("%d\n", np_array[i]);
    }
}
