#ifndef NODE_H
#define NODE_H

typedef struct {
    int level;          // Niveau dans l'arbre (objet courant)
    int weight;         // Poids total du sac à ce niveau
    int utility;        // Utilité totale du sac à ce niveau
    float bound;        // Estimation de la limite supérieure
} Node;

typedef struct {
    int weight;
    int utility;
} Object;

int greedy(Object objects[], int n, int capacity);
float FayardPlateau(Object objects[], int n, int capacity);
int knapsackBranchAndBound(int capacity, Object objects[], int n, int lowerBound);


//void printList(struct Node* n);
//void append(struct Node** head_ref, int new_key, int new_value);

#endif
