#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

void append(struct Node** head_ref, int new_utility, int new_weight) {
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    struct Node *last = *head_ref;
    new_node->utility = new_utility;
    new_node->weight = new_weight;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
}

void printList(struct Node* n) {
    while (n != NULL) {
        printf("(%d, %d) ", n->utility, n->weight);
        n = n->next;
    }
    printf("\n");
}