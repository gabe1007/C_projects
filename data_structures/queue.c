#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void print(Node **front);
void enqueue(Node **front, Node **rear, int value);

int main() {
    Node *front = NULL;
    Node *rear = NULL;
    
    for (int i=0; i<10; i++) {
        enqueue(&front, &rear, i);
    }

    print(&front);
    enqueue(&front, &rear, 15);
    print(&front);

}

void print(Node **front) {
    Node *current = *front;
    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void enqueue(Node **front, Node **rear, int value) {
    Node *novo = malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Failed to alocate memory");
        exit(0);
    }

    novo->value = value;
    novo->next = NULL;

    if (*front == NULL) {
        *front = novo;
        *rear = novo;
    } else {
        (*rear)->next = novo;
        *rear = novo;
    }
}
