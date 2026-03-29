#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node {
    char key[256];
    int value;
    struct Node *next;
} Node;

typedef struct Table {
    int tamanho;
    Node **vetor;
} Table;

void print(int tamanho, Table *dicio);
void insert(Table *dicio, char *chave, int value);
unsigned long djb2_hash(unsigned char *str, int tamanho);
void search(char *search_key, Table *dicio);
void remover(char *search_key, Table *dicio);
void free_table(Table *dicio);

int main() {
    int tamanho          = 15;

    Table *dicio         = malloc(sizeof(Table));
    dicio->tamanho       = tamanho;
    dicio->vetor         = calloc(tamanho, sizeof(Node *));

    char chave[256] = "Idade";
    int idade = 35;
    insert(dicio, chave, idade);

    char chave_[256] = "Tamanho";
    int idade_ = 42;
    insert(dicio, chave_, idade_);

    char mulher[256] = "Sim";
    int size = 165;
    insert(dicio, mulher, size);

    print(tamanho, dicio);

    char search_key[256] = "Idade";
    search(search_key, dicio);
    remover(search_key, dicio);
    print(tamanho, dicio);
    free_table(dicio);

}

void free_table(Table *dicio) {
    for (int i = 0; i < dicio->tamanho; i++) {
        if (dicio->vetor[i] != NULL) {
            Node *current = dicio->vetor[i];
            while (current != NULL) {
                Node *tmp = current->next;
                free(current);
                current = tmp;
            }
        }
    }
    free(dicio->vetor);
    free(dicio);
}

void remover(char *search_key, Table *dicio) {
    unsigned long hash_value;
    Node *prev = NULL;

    hash_value = djb2_hash((unsigned char *)search_key, dicio->tamanho);
    Node *current = dicio->vetor[hash_value];
    if (current == NULL) {
        printf("A chave \"%s\" não existe na tabela\n", search_key);
    } else {
        while (current != NULL) {
            if (strcmp(current->key, search_key) == 0) {
                Node *tmp = current->next;
                free(current);
                if (prev == NULL) {
                    dicio->vetor[hash_value] = tmp;
                } else {
                    prev->next = tmp;
                }
                break;
            }
            prev    = current;
            current = current->next;
        }
    }
}

void search(char *search_key, Table *dicio) {
    unsigned long hash_value;

    hash_value = djb2_hash((unsigned char *)search_key, dicio->tamanho);
    Node *current = dicio->vetor[hash_value];
    if (current == NULL) {
        printf("A chave \"%s\" não existe na tabela\n", search_key);
    }
    while (current != NULL) {
        if (strcmp(current->key, search_key) == 0){
            printf("Valor encontrado %s: %d\n", current->key, current->value);
            break;
        }
        current = current->next;
    }    
}

void insert(Table *dicio, char *chave, int value) {
    unsigned long hash_value;

    hash_value = djb2_hash((unsigned char *)chave, dicio->tamanho);
    Node *new = malloc(sizeof(Node));
    strcpy(new->key, chave);
    new->value = value;
    new->next = dicio->vetor[hash_value];
    dicio->vetor[hash_value] = new;
}

unsigned long djb2_hash(unsigned char *str, int tamanho) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash % tamanho;
}

void print(int tamanho, Table *dicio) {
    for (int i = 0; i < tamanho; i++) {
        Node *current = dicio->vetor[i];
        while (current != NULL) {
            printf("%s: %d\n", current->key, current->value);
            current = current->next;
        }
    }
}
