#include <stdio.h>
#include <stdbool.h>

#define MAX_CAP_A 4
#define MAX_CAP_B 3

typedef struct {
    int a, b;
} State;

typedef struct {
    State state;
    int parent;
} Node;

bool visited[5][4];

void printPath(Node queue[], int index) {
    if (queue[index].parent != -1)
        printPath(queue, queue[index].parent);
    printf("(%d, %d)\n", queue[index].state.a, queue[index].state.b);
}

void BFS() {
    Node queue[100];
    int front = 0, rear = 0;

    queue[rear++] = (Node){{0, 0}, -1};
    visited[0][0] = true;

    while (front < rear) {
        Node current = queue[front];
        int a = current.state.a;
        int b = current.state.b;

        if (a == 2) {
            printf("Solution using BFS:\n");
            printPath(queue, front);
            return;
        }

        int pourAB = (MAX_CAP_B - b < a) ? (MAX_CAP_B - b) : a;
        int pourBA = (MAX_CAP_A - a < b) ? (MAX_CAP_A - a) : b;

        State moves[] = {
            {MAX_CAP_A, b},
            {a, MAX_CAP_B},
            {0, b},
            {a, 0},
            {a - pourAB, b + pourAB},
            {a + pourBA, b - pourBA}
        };

        for (int i = 0; i < 6; i++) {
            int na = moves[i].a;
            int nb = moves[i].b;
            if (!visited[na][nb]) {
                visited[na][nb] = true;
                queue[rear++] = (Node){{na, nb}, front};
            }
        }

        front++;
    }

    printf("No solution found.\n");
}

int main() {
    BFS();
    return 0;
}
