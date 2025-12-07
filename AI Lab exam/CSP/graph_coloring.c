#include <stdio.h>

#define MAX_V 20

int G[MAX_V][MAX_V];
int color[MAX_V];
int V;
int M;
int solutionCount = 0;

int isSafe(int v, int c) {
    for (int i = 0; i < V; i++) {
        if (G[v][i] == 1 && color[i] == c) {
            return 0;
        }
    }
    return 1;
}

void printSolution() {
    solutionCount++;
    printf("\nSolution %d:\n", solutionCount);
    for (int v = 0; v < V; v++) {
        printf("Vertex %d -> Color %d\n", v, color[v]);
    }
}

void graphColoring(int v) {
    if (v == V) {
        printSolution();
        return;
    }

    for (int c = 1; c <= M; c++) {
        if (isSafe(v, c)) {
            color[v] = c;
            graphColoring(v + 1);
            color[v] = 0;
        }
    }
}

int main() {
    printf("Graph Colouring using Backtracking (Constraint Satisfaction Problem)\n");

    printf("Enter number of vertices (<= %d): ", MAX_V);
    scanf("%d", &V);

    if (V > MAX_V || V <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter number of colors: ");
    scanf("%d", &M);

    if (M <= 0) {
        printf("Number of colors must be positive.\n");
        return 1;
    }

    printf("Enter adjacency matrix (%d x %d) (0/1 values):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    for (int i = 0; i < V; i++) {
        color[i] = 0;
    }

    graphColoring(0);

    if (solutionCount == 0) {
        printf("\nNo valid colouring possible with %d colors.\n", M);
    } else {
        printf("\nTotal number of valid colourings: %d\n", solutionCount);
    }

    return 0;
}
