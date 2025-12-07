#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 8
#define MAX_STATES 100000

typedef struct {
    int col[N];
    int h;
    int parent;
    bool expanded;
} Node;

Node nodes[MAX_STATES];
int node_count = 0;

void print_board(int col[]) {
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

bool same_state(int a[], int b[]) {
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int heuristic(int col[]) {
    int h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            int c1 = col[i];
            int c2 = col[j];

            if (c1 == c2)
                h++;
            else if (i + c1 == j + c2)
                h++;
            else if (i - c1 == j - c2)
                h++;
        }
    }
    return h;
}

bool is_visited(int col[]) {
    for (int i = 0; i < node_count; i++) {
        if (same_state(nodes[i].col, col)) return true;
    }
    return false;
}

int add_state(int col[], int parent) {
    if (node_count >= MAX_STATES)
        return -1;

    if (is_visited(col)) return -1;

    for (int i = 0; i < N; i++)
        nodes[node_count].col[i] = col[i];

    nodes[node_count].h = heuristic(col);
    nodes[node_count].parent = parent;
    nodes[node_count].expanded = false;

    return node_count++;
}

int get_best_node_index() {
    int best = -1;
    int best_h = INT_MAX;

    for (int i = 0; i < node_count; i++) {
        if (!nodes[i].expanded && nodes[i].h < best_h) {
            best_h = nodes[i].h;
            best = i;
        }
    }
    return best;
}

void print_solution_path(int idx) {
    int path[MAX_STATES];
    int len = 0;

    int cur = idx;
    while (cur != -1) {
        path[len++] = cur;
        cur = nodes[cur].parent;
    }

    printf("Solution found in %d steps (Best First Search):\n\n", len - 1);
    for (int i = len - 1; i >= 0; i--) {
        printf("Step %d (h = %d):\n", len - 1 - i, nodes[path[i]].h);
        print_board(nodes[path[i]].col);
        printf("\n");
    }
}

void best_first_search() {
    while (1) {
        int idx = get_best_node_index();
        if (idx == -1) {
            printf("No solution found using Best First Search.\n");
            return;
        }

        Node cur = nodes[idx];
        nodes[idx].expanded = true;

        if (cur.h == 0) {
            print_solution_path(idx);
            return;
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (c == cur.col[r]) continue;

                int new_col[N];
                for (int i = 0; i < N; i++)
                    new_col[i] = cur.col[i];

                new_col[r] = c;

                add_state(new_col, idx);
            }
        }
    }
}

int main() {
    int initial[N];
    for (int i = 0; i < N; i++)
        initial[i] = i;

    int root_index = add_state(initial, -1);
    if (root_index == -1) {
        printf("Failed to create initial state.\n");
        return 1;
    }

    printf("8-Queens using Best First Search (heuristic = attacking pairs)\n\n");
    best_first_search();

    return 0;
}
