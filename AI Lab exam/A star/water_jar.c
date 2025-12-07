#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_CAP_A 4
#define MAX_CAP_B 3
#define MAX_STATES 100

typedef struct {
    int a, b;
    int parent;
    int g;
    int h;
    int f;
    bool expanded;
} Node;

Node nodes[MAX_STATES];
int node_count = 0;
bool visited[5][4];

int heuristic(int a, int b) {
    (void)b;
    return abs(a - 2);
}

void print_path(int idx) {
    if (idx == -1) return;
    print_path(nodes[idx].parent);
    printf("(%d, %d)\n", nodes[idx].a, nodes[idx].b);
}

void add_state(int a, int b, int parent) {
    if (a < 0 || a > MAX_CAP_A || b < 0 || b > MAX_CAP_B)
        return;

    if (visited[a][b])
        return;

    if (node_count >= MAX_STATES)
        return;

    visited[a][b] = true;

    nodes[node_count].a = a;
    nodes[node_count].b = b;
    nodes[node_count].parent = parent;

    if (parent == -1)
        nodes[node_count].g = 0;
    else
        nodes[node_count].g = nodes[parent].g + 1;

    nodes[node_count].h = heuristic(a, b);
    nodes[node_count].f = nodes[node_count].g + nodes[node_count].h;
    nodes[node_count].expanded = false;

    node_count++;
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

void astar_search() {
    add_state(0, 0, -1);

    int goal_index = -1;

    while (1) {
        int idx = get_best_node_index();
        if (idx == -1) break;

        Node cur = nodes[idx];
        nodes[idx].expanded = true;

        if (cur.a == 2) {
            goal_index = idx;
            break;
        }

        int a = cur.a;
        int b = cur.b;

        add_state(MAX_CAP_A, b, idx);
        add_state(a, MAX_CAP_B, idx);
        add_state(0, b, idx);
        add_state(a, 0, idx);

        int pourAB = (MAX_CAP_B - b < a) ? (MAX_CAP_B - b) : a;
        add_state(a - pourAB, b + pourAB, idx);

        int pourBA = (MAX_CAP_A - a < b) ? (MAX_CAP_A - a) : b;
        add_state(a + pourBA, b - pourBA, idx);
    }

    if (goal_index == -1) {
        printf("No solution found using A* Search.\n");
    } else {
        printf("Solution path using A* Search (A=4L, B=3L, Goal: 2L in A):\n");
        print_path(goal_index);
        printf("Total steps (optimal): %d\n", nodes[goal_index].g);
    }
}

int main() {
    for (int i = 0; i <= MAX_CAP_A; i++)
        for (int j = 0; j <= MAX_CAP_B; j++)
            visited[i][j] = false;

    astar_search();
    return 0;
}
