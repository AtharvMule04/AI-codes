#include <stdio.h>
#include <stdbool.h>

#define MAX_DEPTH 3

typedef struct {
    int M;
    int C;
    int boat;
    int parent;
} Node;

Node S[1000];
int state_count = 0;
bool goal_found = false;
int goal_index = -1;

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
    for (int i = 0; i < state_count; i++) {
        if (same(S[i], s)) return true;
    }
    return false;
}

int add_state(int M, int C, int boat, int parent) {
    if (!is_safe(M, C)) return -1;
    Node s = {M, C, boat, parent};
    if (!is_visited(s)) {
        if (state_count >= 1000) return -1;
        S[state_count] = s;
        return state_count++;
    }
    return -1;
}

void print_path(int idx) {
    if (idx == -1) return;
    print_path(S[idx].parent);
    printf("(%dM, %dC, Boat: %s)\n", S[idx].M, S[idx].C,
           S[idx].boat == 0 ? "Left" : "Right");
}

void dls(int idx, int depth) {
    if (goal_found) return;

    Node cur = S[idx];

    if (cur.M == 0 && cur.C == 0 && cur.boat == 1) {
        goal_found = true;
        goal_index = idx;
        return;
    }

    if (depth == MAX_DEPTH)
        return;

    int M = cur.M, C = cur.C;

    if (cur.boat == 0) {
        int child;
        if (M >= 1) {
            child = add_state(M-1, C, 1, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (M >= 2) {
            child = add_state(M-2, C, 1, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (C >= 1) {
            child = add_state(M, C-1, 1, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (C >= 2) {
            child = add_state(M, C-2, 1, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (M >= 1 && C >= 1) {
            child = add_state(M-1, C-1, 1, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
    } else {
        int child;
        if (M <= 2) {
            child = add_state(M+1, C, 0, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (M <= 1) {
            child = add_state(M+2, C, 0, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (C <= 2) {
            child = add_state(M, C+1, 0, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (C <= 1) {
            child = add_state(M, C+2, 0, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
        if (M <= 2 && C <= 2) {
            child = add_state(M+1, C+1, 0, idx);
            if (child != -1) dls(child, depth + 1);
            if (goal_found) return;
        }
    }
}

int main() {
    int root_index = add_state(3, 3, 0, -1);

    if (root_index == -1) {
        printf("Failed to create initial state.\n");
        return 1;
    }

    printf("Missionaries and Cannibals using Depth Limited Search (depth = %d)\n\n", MAX_DEPTH);

    dls(root_index, 0);

    if (goal_found) {
        printf("Solution (DLS):\n");
        print_path(goal_index);
    } else {
        printf("No solution within depth limit %d (DLS).\n", MAX_DEPTH);
    }

    return 0;
}
