#include <stdio.h>
#include <stdlib.h>

// IMPLEMENTING STACK USING SINGLY LINKED LIST

struct Node
{
    int value;
    struct Node *next;
};

typedef struct Node Node;


void printList(Node *head) {
    printf("head -> ");
    Node *temp = head;
    while (temp != NULL) {
        printf("%i -> ", temp->value);
        temp = temp->next;
    }
    free(temp);
    printf("null\n");
}

Node *createNode(int value, Node *prev) {
    Node *temp = malloc(sizeof(Node));
    temp->value = value;
    if (prev != NULL) prev->next = temp;
    temp->next = NULL;
    return temp;
}

void push(Node *newhead, Node **head) {
    newhead->next = *head;
    *head = newhead;
}

void pop(Node **head) {
    Node *temp = (*head);
    (*head) = (*head)->next;
    free(temp);
}

int main() {
    Node *head = createNode(16, NULL);
    Node *tail = createNode(25, head);
    push(createNode(9, NULL), &head);
    push(createNode(4, NULL), &head);
    push(createNode(1, NULL), &head);

    pop(&head);

    printList(head);
}