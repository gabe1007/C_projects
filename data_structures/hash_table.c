#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char key[256];
    int value;
    struct Node *next;
}Node;

typedef struct Table {
    int tamanho;
    Node **vetor;
}Table;

unsigned long djb2_hash(unsigned char *str);

int main() {
    int tamanho  = 10;
    Table *new   = malloc(sizeof(Table));
    new->tamanho = tamanho;
    new->vetor   = calloc(tamanho, sizeof(Node *));

    char string[256] = "Nome";
    unsigned long hash = djb2_hash((unsigned char *)string);
    printf("Hash value for '%s': %lu\n", string, hash);
}

unsigned long djb2_hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
        printf("Current hash value: %lu\n", hash);
    }

    return hash;
}
