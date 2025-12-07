#include <stdio.h>
#include <stdbool.h>

#define MAX_CAP_A 4
#define MAX_CAP_B 3

bool visited[5][4];
bool goalReached = false;

int pathA[100], pathB[100];
int stepCount = 0;

void printSolutionPath() {
    printf("\nSolution Path (Steps):\n");
    for (int i = 0; i < stepCount; i++) {
        printf("Step %d: (%d, %d)\n", i, pathA[i], pathB[i]);
    }
}

void DFS(int a, int b) {
    if (goalReached)
        return;

    visited[a][b] = true;

    pathA[stepCount] = a;
    pathB[stepCount] = b;
    stepCount++;

    if (a == 2) {
        goalReached = true;
        printSolutionPath();
        return;
    }

    if (!visited[MAX_CAP_A][b])
        DFS(MAX_CAP_A, b);

    if (!visited[a][MAX_CAP_B])
        DFS(a, MAX_CAP_B);

    if (!visited[0][b])
        DFS(0, b);

    if (!visited[a][0])
        DFS(a, 0);

    int pourAB = (MAX_CAP_B - b < a) ? (MAX_CAP_B - b) : a;
    if (!visited[a - pourAB][b + pourAB])
        DFS(a - pourAB, b + pourAB);

    int pourBA = (MAX_CAP_A - a < b) ? (MAX_CAP_A - a) : b;
    if (!visited[a + pourBA][b - pourBA])
        DFS(a + pourBA, b - pourBA);

    stepCount--;
}

int main() {
    printf("Water Jug Problem using DFS\n");
    printf("Goal: 2L in Jug A (4L capacity)\n\n");

    DFS(0, 0);

    if (!goalReached)
        printf("\nNo solution found.\n");
    else
        printf("\nGoal Reached Successfully!\n");

    return 0;
}
