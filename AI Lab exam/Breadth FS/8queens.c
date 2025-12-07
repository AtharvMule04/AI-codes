#include <stdio.h>
#include <stdbool.h>

#define N 8
#define MAX_STATES 100000

typedef struct {
    int row;
    int col[N];
} Node;

Node queue_states[MAX_STATES];
int front = 0, rear = 0;

void enqueue(Node s) {
    if (rear >= MAX_STATES) {
        printf("Queue overflow!\n");
        return;
    }
    queue_states[rear++] = s;
}

Node dequeue() {
    return queue_states[front++];
}

bool is_empty() {
    return front >= rear;
}

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
    printf("One solution for 8-Queens:\n\n");
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

void bfs_8queens() {
    Node start;
    start.row = 0;
    for (int i = 0; i < N; i++)
        start.col[i] = -1;

    enqueue(start);

    while (!is_empty()) {
        Node curr = dequeue();

        if (curr.row == N) {
            print_board(curr.col);
            return;
        }

        int row = curr.row;

        for (int c = 0; c < N; c++) {
            if (is_safe(curr.col, row, c)) {
                Node next = curr;
                next.col[row] = c;
                next.row = row + 1;
                enqueue(next);
            }
        }
    }

    printf("No solution found.\n");
}

int main() {
    bfs_8queens();
    return 0;
}
