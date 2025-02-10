#include <stdio.h>
#include <stdlib.h>
#include "Node.h"

int main() {
    int n, capacity, utility, weight;

    printf("Enter the capacity of your knapsack: ");
    scanf("%d", &capacity);

    printf("Enter the number of elements you want to input: ");
    scanf("%d", &n);

    //Nanana on t'avait dit utilise pas des listes Blabla, cassez pas les couilles
    Object objects[n];

    for (int i = 0; i < n; i++) {
        printf("Enter utility and weight for pair %d: ", i + 1);
        scanf("%d %d", &utility, &weight);
        objects[i].utility = utility;
        objects[i].weight = weight;
    }

    int max_utility_greedy = greedy(objects, n, capacity);
    printf("Maximum utility using greedy algorithm: %d\n", max_utility_greedy);

    float max_utility_fayard = FayardPlateau(objects, n, capacity);
    printf("Maximum utility using Fayard algorithm: %.2f\n", max_utility_fayard);
    
    int max_utility = knapsackBranchAndBound(capacity, objects, n, max_utility_greedy);
    printf("Maximum integer utility using B&B algorithm: %d\n", v);

    return 0;
}
