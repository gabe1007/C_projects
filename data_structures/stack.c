#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

void push(Node **top, int number);
void pop(Node **top);
void peek(Node **top);
void print(Node *top);

int main() {
        Node *top = NULL;
        
        for (int i = 0; i < 14; i+=2) {
            push(&top, i);
        }
        
        print(top);
        
        printf("Now we apply the pop() function\n");
        pop(&top);

        printf("Showing the top node value\n");
        peek(&top);

        printf("Final print\n");
        print(top);
}

void print(Node *top) {
    Node *current = top;

    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void push(Node **top, int number) {
    Node *novo = malloc(sizeof(Node));
    if (novo == NULL) {
        printf("Memory allocation failed");
        exit(0);
    }
    novo->value = number;
    novo->next = *top;
    *top = novo;
}

void pop(Node **top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Node *tmp = *top;
    *top = (*top)->next;
    free(tmp);
}

void peek(Node **top) {
    if (*top == NULL) {
        printf("Stack is empty\n");
        return;
    }
    printf("The value in the top is: %d\n", (*top)->value);
}

