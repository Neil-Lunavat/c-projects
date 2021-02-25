#include <stdio.h>
#include <stdlib.h>

void initializeArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

int findSize(int size) {
    int n = 2;
    while (n < size) n *= 2;

    return n;
}

void printArray(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void append(int **arr, int value, int *size, int *actualSize) {
    if ((*size)+1 >= *actualSize) { // If we are running out of size, double it
        *actualSize *= 2;
        *arr = realloc(*arr, (*actualSize) * sizeof(int));
    }

    (*arr)[(*size)++] = value; // Assing the last element of array to value
    // And increment the size of the array
}

void removeAt(int **arr, int index, int *size, int *actualSize) {
    int *newarr = malloc((*actualSize) * sizeof(int));

    for (int i = 0, j = 0; i < *size; i++, j++) {
        if (i == index) j--;
        else newarr[j] = (*arr)[i];
    }

    *arr = newarr;
    (*size)--; // Decrement size so it doesn't access null values
}

int main() {

    // DETERMINE THE SIZE OF ARRAY
    int size;
    scanf("%i", &size);
    int actualSize = findSize(size);
    printf("Actual Size: %i bytes\n", actualSize);

    // INITIALIZE ARRAY
    int *arr = malloc(actualSize * sizeof(int));
    initializeArray(arr, size);

    // IDKY
    printf("Initial values: ");
    printArray(arr, size);

    // APPEND ELEMENT TO ARRAY
    printf("Value to be added to the array is: ");
    int value;
    scanf("%i", &value);

    append(&arr, value, &size, &actualSize);

    // REMOVE ELEMENT FROM ARRAY
    printf("Index of element to be removed from the array is: ");
    int index;
    scanf("%i", &index);

    removeAt(&arr, index, &size, &actualSize);
    printf("Final values: ");
    printArray(arr, size);


    // REMOVE ARRAY FROM MEMORY (we are done with it.)
    free(arr);
}