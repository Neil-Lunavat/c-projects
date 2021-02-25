#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *arr;
    int size;
    int actualSize;
} DynamicArray;

void initializeArray(DynamicArray arr) {
    for (int i = 0; i < arr.size; i++) {
        arr.arr[i] = i;
    }
}

int findSize(int size) {
    int n = 2;
    while (n < size) n *= 2;

    return n;
}

void printArray(DynamicArray arr) {
    for (int i = 0; i < arr.size; i++) {
        printf("%i ", arr.arr[i]);
    }
    printf("\n");
}

void append(DynamicArray *arr, int value) {
    if (((*arr).size)+1 >= (*arr).actualSize) { // If we are running out of size, double it
        (*arr).actualSize *= 2;
        (*arr).arr = realloc((*arr).arr, ((*arr).actualSize) * sizeof(int));
    }
    (*arr).arr[((*arr).size)++] = value; // Assing the last element of array to value
    // And increment the size of the array
}

void removeAt(DynamicArray *arr, int index) {
    int *newarr = malloc(((*arr).actualSize) * sizeof(int));

    for (int i = 0, j = 0; i < (*arr).size; i++, j++) {
        if (i == index) j--;
        else newarr[j] = (*arr).arr[i];
    }

    (*arr).arr = newarr;
    ((*arr).size)--; // Decrement size so it doesn't access null values
}

int main() {
    // COMBINE SIZE, ACTUAL SIZE and DATA TOGETHER
    DynamicArray arr;

    // DETERMINE THE SIZE OF ARRAY
    printf("What is the size of the array? ");
    scanf("%i", &arr.size);
    arr.actualSize = findSize(arr.size);
    printf("Actual Size: %i bytes\n", arr.actualSize);

    // INITIALIZE ARRAY
    arr.arr = malloc(arr.actualSize * sizeof(int));
    initializeArray(arr);

    // INITIAL VALUES
    printf("Initial values: ");
    printArray(arr);

    // APPEND ELEMENT TO ARRAY
    printf("Value to be added to the array is: ");
    int value;
    scanf("%i", &value);
    // call append
    append(&arr, value);

    // REMOVE ELEMENT FROM ARRAY
    printf("Index of element to be removed from the array is: ");
    int index;
    scanf("%i", &index);
    // call removeAt
    removeAt(&arr, index);

    // FINAL VALUES
    printf("Final values: ");
    printArray(arr);
}