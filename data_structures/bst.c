#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

typedef struct Node {
    int value;
    struct Node *menor;
    struct Node *maior;    
} Node;

void print(Node *bst);
void insert(Node **bst, int value);
void search(Node **bst, int search_val);

int main() {
    srand(time(NULL));
    int *array = calloc(10, sizeof(int));

    for (int i = 0; i < 10; i++) {
        array[i] = rand() % 100;
    }

    Node *bst = NULL;
    for (int i = 0; i < 10; i++) {
        insert(&bst, array[i]);
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    print(bst);    
    
    int search_val = 120;
    search(&bst, search_val);

}

void print(Node *bst) {
    if (bst == NULL) return;

    print(bst->menor);
    printf("%d\n", bst->value);
    print(bst->maior);
}

void insert(Node **bst, int value) {
    if (*bst == NULL) {
        *bst = malloc(sizeof(Node));
        (*bst)->value = value;
        (*bst)->maior = NULL;
        (*bst)->menor = NULL;
    }
    Node *current = *bst;
    while (current != NULL) {
        if (value > current->value) {
            if (current->maior != NULL) {
                current = current->maior;
            } else {
                Node *new = malloc(sizeof(Node));
                new->value = value;
                new->maior = NULL;
                new->menor = NULL;
                current->maior = new;
                break;
            }
        } else {
            if (current->menor != NULL) {
                current = current->menor;
            } else {
                Node *new = malloc(sizeof(Node));
                new->value = value;
                new->maior = NULL;
                new->menor = NULL;
                current->menor = new;
                break;
            }
        }
    }
}

void search (Node **bst, int search_val) {
    Node *current = *bst;
    bool found = false;
    
    while (current != NULL) {
        if (search_val > current->value){
            if (current->value != search_val){
                current = current->maior;
            } else {
                printf("Valor encontrado: %d\n", current->value);
                found = true;
                break;
            }
        } else {
            if (current->value != search_val){
                current = current->menor;
            } else {
                printf("Valor encontrado: %d\n", current->value);
                found = true;
                break;
            }
        }
    }
    if (!found) {
        printf("Valor não encontrado\n");
    }
}
