#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define N 8
#define MAX_STATES 100000

typedef struct {
    int col[N];
    int parent;
    int g;
    int h;
    int f;
    bool expanded;
} Node;

Node nodes[MAX_STATES];
int node_count = 0;

void print_board(const int col[]) {
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

bool same_state(const int a[], const int b[]) {
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}

int heuristic_attacking_pairs(const int col[]) {
    int h = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (col[i] == col[j]) {
                h++;
            } else {
                int dr = j - i;
                int dc = col[j] - col[i];
                if (dc < 0) dc = -dc;
                if (dr == dc) {
                    h++;
                }
            }
        }
    }
    return h;
}

bool is_visited(const int col[]) {
    for (int i = 0; i < node_count; i++) {
        if (same_state(nodes[i].col, col))
            return true;
    }
    return false;
}

int add_state(const int col[], int parent_index) {
    if (node_count >= MAX_STATES) {
        printf("Error: Too many states generated!\n");
        exit(1);
    }

    if (is_visited(col))
        return -1;

    for (int i = 0; i < N; i++)
        nodes[node_count].col[i] = col[i];

    nodes[node_count].parent = parent_index;

    if (parent_index == -1)
        nodes[node_count].g = 0;
    else
        nodes[node_count].g = nodes[parent_index].g + 1;

    nodes[node_count].h = heuristic_attacking_pairs(col);
    nodes[node_count].f = nodes[node_count].g + nodes[node_count].h;
    nodes[node_count].expanded = false;

    return node_count++;
}

int get_best_node_index() {
    int best_idx = -1;
    int best_f = 1000000000;

    for (int i = 0; i < node_count; i++) {
        if (!nodes[i].expanded && nodes[i].f < best_f) {
            best_f = nodes[i].f;
            best_idx = i;
        }
    }
    return best_idx;
}

void print_solution_path(int goal_idx) {
    int path_indices[MAX_STATES];
    int length = 0;

    int index = goal_idx;
    while (index != -1) {
        path_indices[length++] = index;
        index = nodes[index].parent;
    }

    printf("\nSolution found in %d steps (A* Search):\n", length - 1);

    for (int i = length - 1; i >= 0; i--) {
        int step = length - 1 - i;
        printf("\nStep %d (h = %d, g = %d, f = %d):\n",
               step,
               nodes[path_indices[i]].h,
               nodes[path_indices[i]].g,
               nodes[path_indices[i]].f);
        print_board(nodes[path_indices[i]].col);
    }
}

void astar_8queens() {
    int goal_index = -1;

    while (1) {
        int idx = get_best_node_index();
        if (idx == -1) break;

        Node current = nodes[idx];
        nodes[idx].expanded = true;

        if (current.h == 0) {
            goal_index = idx;
            break;
        }

        for (int r = 0; r < N; r++) {
            for (int c = 0; c < N; c++) {
                if (c == current.col[r]) continue;

                int new_col[N];
                for (int i = 0; i < N; i++)
                    new_col[i] = current.col[i];

                new_col[r] = c;

                add_state(new_col, idx);
            }
        }
    }

    if (goal_index == -1) {
        printf("No solution found using A* Search.\n");
    } else {
        print_solution_path(goal_index);
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

    printf("8-Queens using A* Search\n");
    astar_8queens();

    return 0;
}
