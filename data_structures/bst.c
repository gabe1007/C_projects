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
Node *search(Node **bst, int search_val);
Node *find_min(Node **bst);
Node *find_max(Node **bst);
void del_node(Node **bst, int val, bool *flag);
int height(Node **bst) ;

int main() {
    srand(time(NULL));
    int *array = calloc(30, sizeof(int));

    for (int i = 0; i < 30; i++) {
        array[i] = rand() % 100;
    }

    Node *bst = NULL;
    for (int i = 0; i < 30; i++) {
        insert(&bst, array[i]);
        printf("array[%d] = %d\n", i, array[i]);
    }
    
    print(bst);    
    
    int search_val = array[6];
    Node *result = search(&bst, search_val);
    if (result) {
        printf("Nó encontrado: %d\n", result->value);
    } else {
        printf("Nó não encontrado\n");
    }

    // Find the min value of a tree
    Node *min = find_min(&bst);
    Node *current = min;
    while (current != NULL) {
        printf("Min value is: %d\n", current->value);
        current = current->menor;
    }

    // Find the max value
    Node *max = find_max(&bst);
    Node *cur = max;
    while (cur != NULL) {
        printf("Max value is: %d\n", cur->value);
        cur = cur->maior;
    }

    // Delete node from tree
    int val = 120;
    bool flag = false;
    del_node(&bst, val, &flag);
    if (flag) {
        print(bst);
    } else {
        printf("Value %d not found\n", val);
    }

    int height_tree = height(&bst); 
    printf("The tree heigh is: %d\n", height_tree);
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

Node *search (Node **bst, int search_val) {
    Node *current = *bst;
    
    while (current != NULL) {
        if (search_val > current->value){
            if (current->value == search_val){
                return current;
            }
            current = current->maior;
        } else {
            if (current->value == search_val){
                return current;
            }
            current = current->menor;
        }
    }
    return NULL;
}

Node *find_min(Node **bst) {
    Node *current = *bst;
    while (current->menor != NULL) {
        current = current->menor;
    }
    return current;
}

Node *find_max(Node **bst) {
    Node *current = *bst;
    while(current->maior != NULL) {
        current = current->maior;
    }
    return current;
}

// the inorder successor
Node *get_successor(Node *curr) {
    curr = curr->maior;
    while (curr->menor != NULL)
        curr = curr->menor;
    return curr;
}

void del_node(Node **bst, int val, bool *flag) {
    if (*bst == NULL) return;

    if ((*bst)->value > val){
        del_node(&(*bst)->menor, val, flag);
    } else if ((*bst)->value < val) {
        del_node(&(*bst)->maior, val, flag);
    } else {
        *flag = true;

        // Node with 0 or 1 child
        if ((*bst)->menor == NULL) {
            Node *temp = (*bst)->maior;
            free(*bst);
            *bst = temp;
            return;
        }

        if ((*bst)->maior == NULL) {
            Node *temp = (*bst)->menor;
            free(*bst);
            *bst = temp;
            return;
        }

        // Node with 2 children
        Node *succ = get_successor(*bst);
        (*bst)->value = succ->value;
        del_node(&(*bst)->maior, succ->value, flag);
    }
}

int height(Node **bst) {
    if(*bst == NULL) {
        return 0;
    }

    int rightheight = height(&((*bst)->maior));
    int leftheight  = height(&((*bst)->menor));
    
    if (leftheight > rightheight) {
        return (leftheight + 1);
    } else {
        return (rightheight + 1);
    }
}
