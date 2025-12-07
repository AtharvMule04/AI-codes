#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 8

int x[30];
int solutionCount = 0;
int printed = 0;

int place(int k, int i) {
    for (int j = 1; j <= k - 1; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return 0;
    }
    return 1;
}

void printSolution() {
    solutionCount++;
    if (!printed) {
        printed = 1;
        printf("\nFirst Solution:\n");
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (x[i] == j)
                    printf("Q ");
                else
                    printf(". ");
            }
            printf("\n");
        }
    }
}

void NQueens(int k) {
    for (int i = 1; i <= N; i++) {
        if (place(k, i)) {
            x[k] = i;
            if (k == N)
                printSolution();
            else
                NQueens(k + 1);
        }
    }
}

int main() {
    printf("8-Queens Problem:\n");
    NQueens(1);
    printf("\nTotal number of solutions possible = %d\n", solutionCount);
    return 0;
}
