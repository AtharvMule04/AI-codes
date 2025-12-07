#include <stdio.h>
#include <stdbool.h>

#define N 8
#define MAX_DEPTH 3

bool is_safe(int col[], int row, int c) {
    for (int r = 0; r < row; r++) {
        int c2 = col[r];
        if (c2 == c) return false;
        if ((r + c2) == (row + c)) return false;
        if ((r - c2) == (row - c)) return false;
    }
    return true;
}

void print_board(int col[]) {
    printf("One solution for 8-Queens (Depth Limited Search):\n\n");
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (col[r] == c)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

void dls_8queens(int row, int depth, int col[], bool *found) {
    if (*found) return;
    if (row == N) {
        print_board(col);
        *found = true;
        return;
    }
    if (depth == MAX_DEPTH) return;

    for (int c = 0; c < N; c++) {
        if (is_safe(col, row, c)) {
            col[row] = c;
            dls_8queens(row + 1, depth + 1, col, found);
            if (*found) return;
            col[row] = -1;
        }
    }
}

int main() {
    int col[N];
    bool found = false;

    for (int i = 0; i < N; i++)
        col[i] = -1;

    printf("8-Queens using Depth Limited Search (depth = %d)\n\n", MAX_DEPTH);

    dls_8queens(0, 0, col, &found);

    if (!found) {
        printf("No solution found within depth limit %d.\n", MAX_DEPTH);
    }

    return 0;
}
