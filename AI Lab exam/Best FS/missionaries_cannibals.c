#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_STATES 1000

typedef struct {
    int M;
    int C;
    int boat;
    int parent;
    int h;
    bool expanded;
} Node;

Node S[MAX_STATES];
int state_count = 0;

bool is_safe(int M, int C) {
    int Mr = 3 - M;
    int Cr = 3 - C;

    if (M > 0 && C > M) return false;
    if (Mr > 0 && Cr > Mr) return false;

    return true;
}

bool same_state(Node a, Node b) {
    return a.M == b.M && a.C == b.C && a.boat == b.boat;
}

bool is_visited(Node s) {
    for (int i = 0; i < state_count; i++) {
        if (same_state(S[i], s)) return true;
    }
    return false;
}

int heuristic(int M, int C, int boat) {
    (void)boat;
    return M + C;
}

int add_state(int M, int C, int boat, int parent) {
    if (!is_safe(M, C)) return -1;

    Node s = {M, C, boat, parent, 0, false};

    if (is_visited(s)) return -1;
    if (state_count >= MAX_STATES) return -1;

    s.h = heuristic(M, C, boat);
    S[state_count] = s;
    return state_count++;
}

void print_path(int idx) {
    if (idx == -1) return;
    print_path(S[idx].parent);
    printf("(%dM, %dC, Boat: %s)\n",
           S[idx].M, S[idx].C,
           S[idx].boat == 0 ? "Left" : "Right");
}

int get_best_node_index() {
    int best = -1;
    int best_h = INT_MAX;

    for (int i = 0; i < state_count; i++) {
        if (!S[i].expanded && S[i].h < best_h) {
            best_h = S[i].h;
            best = i;
        }
    }
    return best;
}

void best_first_search() {
    int root_index = add_state(3, 3, 0, -1);
    if (root_index == -1) return;

    while (1) {
        int idx = get_best_node_index();
        if (idx == -1) {
            printf("No solution (Best First Search).\n");
            return;
        }

        Node cur = S[idx];
        S[idx].expanded = true;

        if (cur.M == 0 && cur.C == 0 && cur.boat == 1) {
            printf("Solution (Best First Search):\n");
            print_path(idx);
            return;
        }

        int M = cur.M, C = cur.C;
        int child;

        if (cur.boat == 0) {
            if (M >= 1) child = add_state(M-1, C, 1, idx);
            if (M >= 2) child = add_state(M-2, C, 1, idx);
            if (C >= 1) child = add_state(M, C-1, 1, idx);
            if (C >= 2) child = add_state(M, C-2, 1, idx);
            if (M >= 1 && C >= 1) child = add_state(M-1, C-1, 1, idx);
        } else {
            if (M <= 2) child = add_state(M+1, C, 0, idx);
            if (M <= 1) child = add_state(M+2, C, 0, idx);
            if (C <= 2) child = add_state(M, C+1, 0, idx);
            if (C <= 1) child = add_state(M, C+2, 0, idx);
            if (M <= 2 && C <= 2) child = add_state(M+1, C+1, 0, idx);
        }
    }
}

int main() {
    printf("Missionaries and Cannibals using Best First Search\n\n");
    best_first_search();
    return 0;
}
