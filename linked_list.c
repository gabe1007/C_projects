#include <stdlib.h>
#include <stdio.h>

typedef struct Node{
    int value;
    struct Node *next;
} Node;

void print_list(Node *head);
void free_list(Node *head);
void insert(Node *head, int *insert_number, int *target);
void sub_number_func(Node *head, int *sub_number, int *sub_target);
void delete(Node *head, int *node_delete);

int main() {
    
    Node *head = malloc(sizeof(Node));
    head->value = 1;
    head->next  = NULL;

    Node *current = head;

    for (int i = 2; i < 15; i++) {
        current->next = malloc(sizeof(Node));
        current = current->next;
        current->value = i;
        current->next = NULL;
    }

    int insert_number = 100;
    int target = 5;
    insert(head, &insert_number, &target);

    int sub_number = 200;
    int sub_target = 7;
    sub_number_func(head, &sub_number, &sub_target);

    int node_delete = 12;
    delete(head, &node_delete);

    print_list(head);

    free_list(head);

}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d\n", current->value);
        current = current->next;
    }
}

void free_list(Node *head) {
    Node *current = head;
    Node *tmp;

    while (current != NULL) {
        tmp = current->next;
        free(current);
        current = tmp;
    }    
}

void insert(Node *head, int *insert_number, int *target) {
    Node *current = head;
    
    while (current != NULL) {
        if (current->value == *target) {
            Node *tmp = current->next;
            current->next = malloc(sizeof(Node));
            current = current->next;
            current->value = *insert_number;
            current->next = tmp;
            continue;
        }
        current = current->next;
    }
}

void sub_number_func(Node *head, int *sub_number, int *sub_target) {
    Node *current = head;

    while (current != NULL) {
        if (current->value == *sub_target) {
            current->value = *sub_number;
            current = current->next;
            continue;
        }
        current = current->next;
    }
}

void delete(Node *head, int *node_delete) {
    Node *current = head;
    Node *prev = NULL;
    while (current != NULL) {
        if (current->value == *node_delete) {
            Node *tmp = current->next;
            free(current);
            prev->next = tmp;
            current = tmp;
            continue;
        }
        prev = current;
        current = current->next;
    }
}