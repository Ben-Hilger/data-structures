#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedList {
    int value;
    struct LinkedList* next;
} LinkedList;

LinkedList* allocateList() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList* addToLinkedList(LinkedList* list, int item) {
    if (!list) {
        LinkedList* head = allocateList();
        head->value = item;
        head->next = NULL;
        list = head;
        return list;
    } else if (list->next == NULL) {
        LinkedList* node = allocateList();
        node->value = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;

    while (temp->next->next) {
        temp = temp->next;
    }

    LinkedList* node = allocateList();
    node->value = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

int removeFromLinkedList(LinkedList* list) {
    if (!list || !list->next) {
        return -1;
    }

    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node; 
    int it = temp->value;
    free(temp);
    return it;
}

void freeLinkedList(LinkedList* list) {
    LinkedList* temp = list;

    while (list) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

LinkedList* createLinkedList(int size) {
    LinkedList* buckets = (LinkedList*) calloc(size, sizeof(LinkedList));
    return buckets;
}

void printLinkedList(LinkedList* list) {
    LinkedList* curr = list;
    while (curr) {
        printf("%d", curr->value);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    LinkedList* list = NULL;

    addToLinkedList(list, 1);

    printLinkedList(list);

    freeLinkedList(list);
}
