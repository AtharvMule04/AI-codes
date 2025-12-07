#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9
#define MAX_STATES 400000
#define MAX_DEPTH 50

typedef struct {
    int tiles[N];
    int parent;
} Node;

Node nodes[MAX_STATES];
int node_count = 0;

int goal_state[N] = {1,2,3,4,5,6,7,8,0};

bool goal_found = false;
int goal_index = -1;

void input_initial(int *tiles) {
    for (int i = 0; i < N; i++)
        scanf("%d", &tiles[i]);
}

void print_state(const int *tiles) {
    for (int i = 0; i < N; i++) {
        if (tiles[i] == 0) printf("  ");
        else printf("%d ", tiles[i]);
        if ((i + 1) % 3 == 0) printf("\n");
    }
}

bool is_goal(const int *tiles) {
    for (int i = 0; i < N; i++)
        if (tiles[i] != goal_state[i]) return false;
    return true;
}

bool are_same(const int *a, const int *b) {
    for (int i = 0; i < N; i++)
        if (a[i] != b[i]) return false;
    return true;
}

int find_blank(const int *tiles) {
    for (int i = 0; i < N; i++)
        if (tiles[i] == 0) return i;
    return -1;
}

void copy_state(const int *src, int *dst) {
    for (int i = 0; i < N; i++)
        dst[i] = src[i];
}

bool is_visited(const int *tiles) {
    for (int i = 0; i < node_count; i++)
        if (are_same(nodes[i].tiles, tiles)) return true;
    return false;
}

int add_state(const int *tiles, int parent_index) {
    copy_state(tiles, nodes[node_count].tiles);
    nodes[node_count].parent = parent_index;
    return node_count++;
}

void print_solution_path(int goal_idx) {
    int path[MAX_STATES];
    int length = 0;
    int index = goal_idx;

    while (index != -1) {
        path[length++] = index;
        index = nodes[index].parent;
    }

    printf("\nSolution found in %d moves:\n", length - 1);
    for (int i = length - 1; i >= 0; i--) {
        printf("\nStep %d:\n", length - 1 - i);
        print_state(nodes[path[i]].tiles);
    }
}

void dfs(int index, int depth) {
    if (goal_found) return;
    if (depth > MAX_DEPTH) return;

    Node current = nodes[index];

    if (is_goal(current.tiles)) {
        goal_found = true;
        goal_index = index;
        return;
    }

    int blank_pos = find_blank(current.tiles);
    int row = blank_pos / 3;
    int col = blank_pos % 3;

    int drow[] = {-1, 1, 0, 0};
    int dcol[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int new_row = row + drow[i];
        int new_col = col + dcol[i];

        if (new_row >= 0 && new_row < 3 && new_col >= 0 && new_col < 3) {
            int new_pos = new_row * 3 + new_col;
            int new_tiles[N];
            copy_state(current.tiles, new_tiles);

            int temp = new_tiles[blank_pos];
            new_tiles[blank_pos] = new_tiles[new_pos];
            new_tiles[new_pos] = temp;

            if (!is_visited(new_tiles)) {
                int child_index = add_state(new_tiles, index);
                dfs(child_index, depth + 1);
                if (goal_found) return;
            }
        }
    }
}

int main() {
    int initial[N];

    input_initial(initial);

    int root_index = add_state(initial, -1);

    printf("\nStarting DFS (depth limit = %d)...\n", MAX_DEPTH);

    dfs(root_index, 0);

    if (!goal_found)
        printf("\nNo solution found within depth limit %d.\n", MAX_DEPTH);
    else {
        print_solution_path(goal_index);
        printf("\nGoal Reached Successfully (via DFS)!\n");
    }

    return 0;
}
