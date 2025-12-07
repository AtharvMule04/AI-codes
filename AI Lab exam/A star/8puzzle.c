#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9
#define MAX_STATES 400000

typedef struct {
    int tiles[N];
    int parent;
    int g;
    int h;
    int f;
    bool expanded;
} Node;

Node nodes[MAX_STATES];
int node_count = 0;

int goal_state[N] = {
    1, 2, 3,
    4, 5, 6,
    7, 8, 0
};

void input_initial(int *tiles) {
    for (int i = 0; i < N; i++) {
        scanf("%d", &tiles[i]);
    }
}

void print_state(const int *tiles) {
    for (int i = 0; i < N; i++) {
        if (tiles[i] == 0)
            printf("  ");
        else
            printf("%d ", tiles[i]);

        if ((i + 1) % 3 == 0)
            printf("\n");
    }
}

bool are_same(const int *a, const int *b) {
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool is_goal(const int *tiles) {
    return are_same(tiles, goal_state);
}

int find_blank(const int *tiles) {
    for (int i = 0; i < N; i++) {
        if (tiles[i] == 0)
            return i;
    }
    return -1;
}

void copy_state(const int *src, int *dst) {
    for (int i = 0; i < N; i++)
        dst[i] = src[i];
}

int heuristic(const int *tiles) {
    int h = 0;
    for (int i = 0; i < N; i++) {
        int val = tiles[i];
        if (val != 0) {
            int goal_index = val - 1;
            int row = i / 3;
            int col = i % 3;
            int goal_row = goal_index / 3;
            int goal_col = goal_index % 3;
            int dr = row - goal_row;
            if (dr < 0) dr = -dr;
            int dc = col - goal_col;
            if (dc < 0) dc = -dc;
            h += dr + dc;
        }
    }
    return h;
}

bool is_visited(const int *tiles) {
    for (int i = 0; i < node_count; i++) {
        if (are_same(nodes[i].tiles, tiles))
            return true;
    }
    return false;
}

int add_state(const int *tiles, int parent_index) {
    if (node_count >= MAX_STATES) {
        printf("Error: Too many states generated!\n");
        exit(1);
    }

    if (is_visited(tiles))
        return -1;

    copy_state(tiles, nodes[node_count].tiles);
    nodes[node_count].parent = parent_index;

    if (parent_index == -1)
        nodes[node_count].g = 0;
    else
        nodes[node_count].g = nodes[parent_index].g + 1;

    nodes[node_count].h = heuristic(tiles);
    nodes[node_count].f = nodes[node_count].g + nodes[node_count].h;
    nodes[node_count].expanded = false;

    return node_count++;
}

void print_solution_path(int goal_idx) {
    int path_indices[MAX_STATES];
    int length = 0;

    int index = goal_idx;
    while (index != -1) {
        path_indices[length++] = index;
        index = nodes[index].parent;
    }

    printf("\nSolution found in %d moves:\n", length - 1);
    for (int i = length - 1; i >= 0; i--) {
        printf("\nStep %d:\n", length - 1 - i);
        print_state(nodes[path_indices[i]].tiles);
    }
    printf("\nTotal cost (g) = %d\n", nodes[goal_idx].g);
}

int get_best_node_index() {
    int best_idx = -1;
    int best_f = 1000000;

    for (int i = 0; i < node_count; i++) {
        if (!nodes[i].expanded && nodes[i].f < best_f) {
            best_f = nodes[i].f;
            best_idx = i;
        }
    }
    return best_idx;
}

void astar() {
    int goal_index = -1;

    while (1) {
        int idx = get_best_node_index();
        if (idx == -1) break;

        Node current = nodes[idx];
        nodes[idx].expanded = true;

        if (is_goal(current.tiles)) {
            goal_index = idx;
            break;
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

                add_state(new_tiles, idx);
            }
        }
    }

    if (goal_index == -1) {
        printf("\nNo solution found.\n");
    } else {
        print_solution_path(goal_index);
        printf("\nGoal Reached Successfully!\n");
    }
}

int main() {
    int initial[N];

    input_initial(initial);

    int root_index = add_state(initial, -1);

    if (root_index == -1) {
        printf("Initial state is duplicate or invalid.\n");
        return 1;
    }

    printf("\nStarting A* Search...\n");
    astar();

    return 0;
}
