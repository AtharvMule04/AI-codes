#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int M;
    int C;
    int boat;
    int parent;
} Node;

Node Q[1000];
int front = 0, rear = 0;

bool is_safe(int M, int C) {
    int Mr = 3 - M;
    int Cr = 3 - C;
    if (M > 0 && C > M) return false;
    if (Mr > 0 && Cr > Mr) return false;
    return true;
}

bool same(Node a, Node b) {
    return a.M == b.M && a.C == b.C && a.boat == b.boat;
}

bool is_visited(Node s) {
    for (int i = 0; i < rear; i++) {
        if (same(Q[i], s)) return true;
    }
    return false;
}

void add_state(int M, int C, int boat, int parent) {
    if (!is_safe(M, C)) return;
    Node s = {M, C, boat, parent};
    if (!is_visited(s)) {
        Q[rear++] = s;
    }
}

void print_path(int idx) {
    if (idx == -1) return;
    print_path(Q[idx].parent);
    printf("(%dM, %dC, Boat: %s)\n",
           Q[idx].M, Q[idx].C,
           Q[idx].boat == 0 ? "Left" : "Right");
}

void bfs() {
    Q[rear++] = (Node){3,3,0,-1};

    while (front < rear) {
        Node cur = Q[front];
        int p = front;
        front++;

        if (cur.M == 0 && cur.C == 0 && cur.boat == 1) {
            printf("Solution:\n");
            print_path(p);
            return;
        }

        int M = cur.M, C = cur.C;

        if (cur.boat == 0) {
            if (M >= 1) add_state(M-1, C, 1, p);
            if (M >= 2) add_state(M-2, C, 1, p);
            if (C >= 1) add_state(M, C-1, 1, p);
            if (C >= 2) add_state(M, C-2, 1, p);
            if (M >= 1 && C >= 1) add_state(M-1, C-1, 1, p);
        } else {
            if (M <= 2) add_state(M+1, C, 0, p);
            if (M <= 1) add_state(M+2, C, 0, p);
            if (C <= 2) add_state(M, C+1, 0, p);
            if (C <= 1) add_state(M, C+2, 0, p);
            if (M <= 2 && C <= 2) add_state(M+1, C+1, 0, p);
        }
    }

    printf("No solution.\n");
}

int main() {
    bfs();
    return 0;
}
