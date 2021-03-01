#include <stdio.h>
#include <stdlib.h>

// IMPLEMENTING QUEUES WITH DYNAMIC ARRAYS

typedef struct {
    int *arr;
    int size;
    int actualSize;
} Queue;

int findSize(int size) {
    int n = 2;
    while (n < size) n *= 2;

    return n;
}

void initializeQueue(Queue q) {
    for (int i = 0; i < q.size; i++) {
        q.arr[i] = i;
    }
}

void printQueue(Queue q) {
    for (int i = 0; i < q.size; i++) {
        printf("%i ", q.arr[i]);
    }
    printf("\n");
}

void enqueue(Queue *q, int value) {
    if ((q->size)+1 >= q->actualSize) { // If we are running out of size, double it
        q->actualSize *= 2;
        q->arr = realloc(q->arr, (q->actualSize) * sizeof(int));
    }
    q->arr[(q->size)++] = value; // Assing the last element of array to value
    // And increment the size of the array
}

void dequeue(Queue *q) {
    // Not really updating the size of the array so...
    if ((q->size) < (q->actualSize) / 2) {
        (q->actualSize) /= 2;
        q->arr = realloc((q->arr), ((q->actualSize)) * sizeof(int));
    }
    // I need help. I can iterate over the entire array copying
    // everything into the new array but... thats O(n) complexity.
}

int main() {
    // COMBINE SIZE, ACTUAL SIZE and DATA TOGETHER
    Queue q;

    q.size = 0;
    q.actualSize = findSize(q.size);

    // INITIALIZE QUEUE
    q.arr = malloc(q.actualSize * sizeof(int));
    initializeQueue(q);

    printf("Initial values: ");
    printQueue(q);

    // ENQUEUE AND DEQUEUE
    enqueue(&q, 5);
    enqueue(&q, 4);
    enqueue(&q, 3);

    dequeue(&q);
    dequeue(&q);

    printf("Final values: ");
    printQueue(q);
}
