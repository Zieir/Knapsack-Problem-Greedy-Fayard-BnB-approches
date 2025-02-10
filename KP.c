#include <stdlib.h>
#include <stdio.h>
#include "Node.h"

#define MAX capacity
#define MAXIter 2*n //Il se peut que j'ai besoin de changer ça : peut théoriquement aller jusqu'à 2^n -1  mais avec une 


//Pour qsort
int compareGreedy(const void *a, const void *b) {
    Object *objA = (Object *)a;
    Object *objB = (Object *)b;
    return (objB->utility - objA->utility);
}

int compareFayard(const void *a, const void *b) {
    const Object *objA = (const Object *)a;
    const Object *objB = (const Object *)b;
    
    float ratioA = objA->utility / objA->weight;
    float ratioB = objB->utility / objB->weight;

    return (ratioA > ratioB) ? -1 : (ratioA < ratioB) ? 1 : 0;
}


int greedy(Object objects[], int n, int capacity) {
    //Object knapsack[MAX];
    int knapsack_weight = 0;
    int knapsack_utility = 0;
    //int knapsack_count = 0;

    // Trier les objets par utilité
    qsort(objects, n, sizeof(Object), compareGreedy); //Tester en le mettant en commentaire

    for (int i = 0; i < n; i++) {
        if (knapsack_weight + objects[i].weight <= capacity) {
            //knapsack[knapsack_count++] = objects[i];
            knapsack_weight += objects[i].weight;
            knapsack_utility += objects[i].utility;
        }
    }
    return knapsack_utility;
}



float FayardPlateau(Object objects[], int n, int capacity) {
    int knapsack_weight = 0;
    float knapsack_utility = 0.0;

    // Trier les objets par utilité/poids décroissant
    qsort(objects, n, sizeof(Object), compareFayard);

    for (int i = 0; i < n; i++) {
        // Si l'objet peut être ajouté en entier
        if (knapsack_weight + objects[i].weight <= capacity) {
            knapsack_weight += objects[i].weight;
            knapsack_utility += objects[i].utility;
        } 
        // Sinon, ajouter une fraction de l'objet
        else {
            int remaining_capacity = capacity - knapsack_weight;
            knapsack_utility += objects[i].utility * ((float)remaining_capacity / objects[i].weight);
            break; // Le sac est plein
        }
    }

    return knapsack_utility;
}


// Fonction pour calculer la borne supérieure (upper bound)
float bound(Node u, int n, int capacity, const Object objects[]) {
    // Si le poids du sac dépasse la capacité, la solution est invalide
    if (u.weight > capacity) {
        return 0;
    }

    float result = u.utility;
    int j = u.level + 1;
    int totalWeight = u.weight;

    // Ajouter les objets complets
    while (j < n && totalWeight + objects[j].weight <= capacity) {
        totalWeight += objects[j].weight;
        result += objects[j].utility;
        j++;
    }

    // Ajouter une fraction de l'objet suivant (approche gloutonne)
    if (j < n) {
        result += (capacity - totalWeight) * ((float)objects[j].utility / objects[j].weight);
    }

    return result;
}

// Fonction pour résoudre le Knapsack Problem via Branch and Bound
int knapsackBranchAndBound(int capacity, Object objects[], int n, int lowerBound) {
    // Trier les objets par utilité/poids décroissant
    //qsort(objects, n, sizeof(Object), (int (*)(const void *, const void *))compareFayard);

    Node queue[MAXIter]; // File pour stocker les nœuds
    int front = 0, rear = 0;

    // Initialisation du nœud initial
    Node u, v;
    v.level = -1;
    v.utility = 0;
    v.weight = 0;
    v.bound = bound(v, n, capacity, objects);
    queue[rear++] = v; // Ajouter à la file

    int maxUtility = lowerBound; // Utilité maximale trouvée

    // Exploration de l'arbre des solutions
    while (front < rear) {
        v = queue[front++]; // Extraire un nœud

        // Si la borne supérieure est meilleure que la meilleure solution trouvée
        if (v.bound > maxUtility) {
            // Explorer le nœud en incluant l'objet v.level + 1
            u.level = v.level + 1;
            u.weight = v.weight + objects[u.level].weight;
            u.utility = v.utility + objects[u.level].utility;
            u.bound = bound(u, n, capacity, objects);

            // Si la solution est valide et meilleure que la meilleure trouvée
            if (u.weight <= capacity && u.utility > maxUtility) {
                maxUtility = u.utility;
            }

            // Si la borne est prometteuse, on ajoute à la file
            if (u.bound > maxUtility) {
                queue[rear++] = u;
            }

            // Explorer le nœud sans inclure l'objet v.level + 1
            u.weight = v.weight;
            u.utility = v.utility;
            u.bound = bound(u, n, capacity, objects);

            // Si la borne est prometteuse, on ajoute à la file
            if (u.bound > maxUtility) {
                queue[rear++] = u;
            }
        }
    }

    return maxUtility; // La meilleure utilité trouvée
}
