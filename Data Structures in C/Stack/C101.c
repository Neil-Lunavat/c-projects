#include <stdio.h>
#include <stdlib.h>

// IMPLEMENTING STACK USING DYNAMIC ARRAYS

struct Stack
{
    int *arr;
    int size;
    int actualSize;
    int *head;
};

typedef struct Stack Stack;

int findActualSize(int size) {
    int n = 2;
    while (n <= size) n *= 2;
    return n;
}

void initializeStack(Stack *stack) {
    stack->actualSize = findActualSize(stack->size);
    stack->arr = malloc((stack->actualSize) * sizeof(int));
    for (int i = 0; i < stack->size; i++) {
        stack->arr[i] = i;
    }
    stack->head = &((stack->arr)[(stack->size)-1]);

    printf("Size: %i, Actual Size: %i\n", stack->size, stack->actualSize);
}

void printStack(Stack *stack) {
    for (int i = 0; i < stack->size; i++) {
        printf("%i > ", stack->arr[i]);
    }
    printf("head\n");
    printf("Size: %i, Actual Size: %i\n", stack->size, stack->actualSize);
    printf("\n");
}

void push(Stack *stack, int value) {
    if ((stack->size)+1 >= (stack->actualSize)) { // If we are running out of size, double it
        (stack->actualSize) *= 2;
        (stack->arr) = realloc((stack->arr), ((stack->actualSize)) * sizeof(int));
    }
    (stack->arr)[(stack->size)++] = value;
}

void pop(Stack *stack) {
    if ((stack->size) < (stack->actualSize) / 2) {
        (stack->actualSize) /= 2;
        stack->arr = realloc((stack->arr), ((stack->actualSize)) * sizeof(int));
    }
    (stack->arr)[--(stack->size)] = 0;
}

int main() {
    Stack stack;
    stack.size = 10;
    initializeStack(&stack);

    printStack(&stack);
    push(&stack, 10);
    push(&stack, 11);
    push(&stack, 12);
    printStack(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    pop(&stack);
    push(&stack, 19);
    push(&stack, 29);
    printStack(&stack);
}