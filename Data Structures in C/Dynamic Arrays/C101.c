// DYNAMIC ARRAY

#include <stdio.h>
#include <stdlib.h>

void randomInit(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        array[i] = i;
    }
}

void printArray(int *array, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}

void addValue(int *array, int value, int *n)
{
    *n += 1;
    array = realloc(array, *n * sizeof(int));
    array[(*n) - 1] = value;
}

void removeValue(int **array, int index, int *n)
{
    int *newarray = malloc(((*n) - 1) * sizeof(int));
    for (int i = 0, j = 0; i < *n; i++, j++)
    {
        if (i == index)
            j--;
        else
            newarray[j] = (*array)[i];
    }

    *n -= 1;
    *array = newarray;
}

int main()
{
    int n;
    scanf("%i", &n);

    // INIT ARRAY
    int *array = malloc(n * sizeof(int));
    randomInit(array, n);

    // PRINT ARRAY
    printArray(array, n);

    // MODIFY ARRAY
    addValue(array, 123, &n);   // Appending 8 to new array
    removeValue(&array, 4, &n); // Removing position 4 from array

    // CHECK ARRAY
    printArray(array, n);

    free(array);

    return 0;
}