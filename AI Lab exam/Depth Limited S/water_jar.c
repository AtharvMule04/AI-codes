#include <stdio.h>
#include <stdbool.h>

#define MAX_CAP_A 4
#define MAX_CAP_B 3
#define MAX_DEPTH 3

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

void DLS(int a, int b, int depth) {
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

    if (depth == MAX_DEPTH) {
        stepCount--;
        return;
    }

    if (!visited[MAX_CAP_A][b])
        DLS(MAX_CAP_A, b, depth + 1);

    if (!goalReached && !visited[a][MAX_CAP_B])
        DLS(a, MAX_CAP_B, depth + 1);

    if (!goalReached && !visited[0][b])
        DLS(0, b, depth + 1);

    if (!goalReached && !visited[a][0])
        DLS(a, 0, depth + 1);

    int pourAB = (MAX_CAP_B - b < a) ? (MAX_CAP_B - b) : a;
    if (!goalReached && !visited[a - pourAB][b + pourAB])
        DLS(a - pourAB, b + pourAB, depth + 1);

    int pourBA = (MAX_CAP_A - a < b) ? (MAX_CAP_A - a) : b;
    if (!goalReached && !visited[a + pourBA][b - pourBA])
        DLS(a + pourBA, b - pourBA, depth + 1);

    stepCount--;
}

int main() {
    printf("Water Jug Problem using Depth Limited Search\n");
    printf("Goal: 2L in Jug A (4L capacity)\n");
    printf("Depth Limit = %d\n\n", MAX_DEPTH);

    DLS(0, 0, 0);

    if (!goalReached)
        printf("\nNo solution found within depth limit.\n");
    else
        printf("\nGoal Reached Successfully within depth limit!\n");

    return 0;
}
