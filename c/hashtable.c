#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 50000

unsigned long getHashIndex(char* str) {
    unsigned long i = 0; 
    for (int j = 0; str[j]; j++) {
        i += str[j];
    }

    return i % CAPACITY;
}

typedef struct Item {
    char* key;
    char* value;
} Item;


typedef struct LinkedList {
    Item* item;
    struct LinkedList* next;
} LinkedList;

typedef struct HashTable {
    Item** items;
    LinkedList** overflowBuckets;
    int size;
    int count;
} HashTable;

LinkedList* allocateList() {
    LinkedList* list = (LinkedList*) malloc(sizeof(LinkedList));
    return list;
}

LinkedList* addToLinkedList(LinkedList* list, Item* item) {
    if (!list) {
        LinkedList* head = allocateList();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } else if (list->next == NULL) {
        LinkedList* node = allocateList();
        node->item = item;
        node->next = NULL;
        list->next =  node;
        return list;
    }

    LinkedList* temp = list;

    while (temp->next->next) {
        temp = temp->next;
    }

    LinkedList* node = allocateList();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    return list;
}

Item* removeFromLinkedList(LinkedList* list) {
    if (!list || !list->next) {
        return NULL;
    }

    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node; 
    Item* it = NULL;
    memcpy(temp->item, it, sizeof(Item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}

void freeLinkedList(LinkedList* list) {
    LinkedList* temp = list;

    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

Item* createHashItem(char* key, char* value) {
    Item* item = (Item*) malloc(sizeof(Item));
    item->key = (char*) malloc(strlen(key) + 1);
    item->value = (char*) malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);
    return item;
}

LinkedList** createOverflowBuckets(HashTable* table) {
    LinkedList** buckets = (LinkedList**) calloc(table->size, sizeof(LinkedList*));

    for (int i = 0; i < table->size; i++) {
        buckets[i] = NULL;
    }

    return buckets;
}

void freeOverflowBuckets(HashTable* table) {
    LinkedList** buckets = table->overflowBuckets;

    for (int i = 0; i < table->size; i++) {
        freeLinkedList(buckets[i]);
    }

    free(buckets);
}

HashTable* createHashTable(int size) {
    HashTable* table = (HashTable*) malloc(sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Item**) calloc(table->size, sizeof(Item));

    for (int i = 0; i < table->size; i++) {
        table->items[i] = NULL;
    }

    table->overflowBuckets = createOverflowBuckets(table);

    return table;
}

void freeItem(Item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void freeTable(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        Item* item = table->items[i];
        if (item != NULL) {
            freeItem(item);
        }
    }

    freeOverflowBuckets(table);
    free(table->items);
    free(table);
}

void printTable(HashTable* table) {
    printf("\nHash Table\n---------------\n");

    for (int i = 0; i < table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s\n", i, table->items[i]->key, table->items[i]->value);
        }
    }
    
    printf("--------------\n\n");
}

char* searchHashTable(HashTable* table, char* key) {
    int index = getHashIndex(key);
    Item* item = table->items[index];
    LinkedList* head = table->overflowBuckets[index];

    if (item != NULL) {
        if (strcmp(item->key, key) == 0) {
            return item->value;
        }

        if (head == NULL) {
            return NULL;
        }

        item = head->item;
        head = head->next;
    }

    return NULL;
}

void handleCollision(HashTable* table, unsigned long index, Item* item) {
    LinkedList* head = table->overflowBuckets[index];

    if (head == NULL) {
        head = allocateList();
        head->item = item;
        table->overflowBuckets[index] = head;
    } else {
        table->overflowBuckets[index] = addToLinkedList(head, item);
    }
}

void set(HashTable* table, char* key, char* value) {
    Item* item = createHashItem(key, value);
    int index = getHashIndex(key);

    Item* currentItem = table->items[index];

    if (currentItem == NULL) {
        if (table->count == table->size) {
            printf("Hash table is full!!!\n");
            freeItem(item);
            return;
        }

        table->items[index] = item;
        table->count++;
    } else if (strcmp(currentItem->key, key) == 0) {
        strcpy(table->items[index]->value, value);
        return;
    } else {
        handleCollision(table, index, item);
    }
}

void search(HashTable* table, char* key) {
    char* val;

    if ((val = searchHashTable(table, key)) == NULL) {
        printf("Key: %s does not exist\n", key);
        return;
    } else {
        printf("Key: %s, Value: %s\n", key, val);
    }
}

void delete(HashTable* table, char* key) {
    int index = getHashIndex(key);
    Item* item = table->items[index];
    LinkedList* head = table->overflowBuckets[index];

    if (item == NULL) {
        return;
    } else if (head == NULL && strcmp(item->key, key) == 0) {
        table->items[index] = NULL;
        freeItem(item);
        table->count--;
    } else if (head != NULL) {
        if (strcmp(item->key, key) == 0) {
            freeItem(item);
            LinkedList* node = head;
            head = head->next;
            node->next = NULL;
            table->items[index] = createHashItem(node->item->key, node->item->value);
            freeLinkedList(node);
            table->overflowBuckets[index] = head;
            return;
        }

        LinkedList* curr = head;
        LinkedList* prev = NULL;

        while (curr) {
            if (strcmp(curr->item->key, key) == 0) {
                if (prev == NULL) {
                    freeLinkedList(head);
                    table->overflowBuckets[index] = NULL;
                    return; 
                } else {
                    prev->next = curr->next;
                    curr->next =  NULL;
                    freeLinkedList(curr);
                    table->overflowBuckets[index] = head;
                    return;
                }
            }

            curr = curr->next;
            prev = curr;
        }
    }
}

int main() {
    HashTable* table = createHashTable(CAPACITY);
    
    printf("Adding testone: 1, testtwo: 2, testthree: 3\n");
    set(table, "testone", "1");
    set(table, "testtwo", "2");
    set(table, "testthree", "3");

    printTable(table);

    printf("Searching for: testone\n");
    search(table, "testone");

    printf("Searching for: notpresent\n");
    search(table, "notpresent");

    printf("deleting: testone\n");
    delete(table, "testone");

    printTable(table);

    printf("deleting: notpresent\n");
    delete(table, "notpresent");
    
    printTable(table);

    printf("Cleaning up...");
    freeTable(table);
}
