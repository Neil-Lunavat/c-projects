#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
};

typedef struct Node Node;


void printList(Node *head) {
    Node *temp = head;
    while (temp != NULL) {
        printf("%i-> ", temp->value);
        temp = temp->next;
    }
    free(temp);
    printf("\n");
}

Node *createNode(int value, Node *prev) {
    Node *temp = malloc(sizeof(Node));
    temp->value = value;
    if (prev != NULL) prev->next = temp;
    temp->next = NULL;
    return temp;
}

void addHead(Node *newhead, Node **head) {
    newhead->next = *head;
    *head = newhead;
}

void addTail(Node *newtail, Node **tail) {
    (*tail)->next = newtail;
    *tail = newtail;
}

void removeHead(Node **head) {
    Node *temp = (*head);
    (*head) = (*head)->next;
    free(temp);
}

int main() {
    Node *head = createNode(16, NULL);
    Node *tail = createNode(25, head);
    addHead(createNode(9, NULL), &head);
    addHead(createNode(4, NULL), &head);
    addHead(createNode(1, NULL), &head);
    addTail(createNode(36, tail), &tail);
    addTail(createNode(49, tail), &tail);
    addTail(createNode(64, tail), &tail);

    removeHead(&head);

    printList(head);
}