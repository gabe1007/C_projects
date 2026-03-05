#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void push(Node **top, int number);

int main() {
        Node *top = NULL;
        int number = 10;
        push(&top, number);

        int number_ = 15;
        push(&top, number_);

        Node *current = top;
        while (current != NULL) {
            printf("%d\n", current->value);
            current = current->next;
        }
}

void push(Node **top, int number) {
    Node *novo = malloc(sizeof(Node));
    novo->value = number;
    novo->next = *top;
    *top = novo;
}

