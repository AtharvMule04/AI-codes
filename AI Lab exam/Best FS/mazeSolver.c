#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define NODES 16
#define MAX_DEG 4

const char *names[NODES] = {
    "S","A","B","C",
    "D","E","F","G",
    "H","I","J","Key",
    "K","L","M","N"
};

int adj[NODES][MAX_DEG];
int deg[NODES];

int parent_arr[NODES];
int h[NODES];
bool visited[NODES];
bool discovered[NODES];

void add_edge(int u, int v) {
    adj[u][deg[u]++] = v;
    adj[v][deg[v]++] = u;
}

int heuristic(int node) {
    int row = node / 4;
    int col = node % 4;

    int goal = 11;
    int goal_row = goal / 4;
    int goal_col = goal % 4;

    int dr = row - goal_row;
    if (dr < 0) dr = -dr;

    int dc = col - goal_col;
    if (dc < 0) dc = -dc;

    return dr + dc;
}

int get_best_node() {
    int best = -1;
    int best_h = INT_MAX;

    for (int i = 0; i < NODES; i++) {
        if (discovered[i] && !visited[i]) {
            if (h[i] < best_h) {
                best_h = h[i];
                best = i;
            }
        }
    }
    return best;
}

void print_path(int start, int goal) {
    int path[100];
    int len = 0;
    int cur = goal;

    while (cur != -1) {
        path[len++] = cur;
        cur = parent_arr[cur];
    }

    printf("Path from %s to %s using Best First Search:\n", names[start], names[goal]);
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", names[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\n");
}

void best_first_search(int start, int goal) {
    for (int i = 0; i < NODES; i++) {
        parent_arr[i] = -1;
        visited[i] = false;
        discovered[i] = false;
        h[i] = INT_MAX;
    }

    discovered[start] = true;
    h[start] = heuristic(start);

    while (1) {
        int u = get_best_node();
        if (u == -1) {
            printf("No path from %s to %s (Best First Search)\n",
                   names[start], names[goal]);
            return;
        }

        visited[u] = true;

        if (u == goal) {
            print_path(start, goal);
            return;
        }

        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];

            if (!visited[v] && !discovered[v]) {
                discovered[v] = true;
                parent_arr[v] = u;
                h[v] = heuristic(v);
            }
        }
    }
}

int main() {
    add_edge(0,1);
    add_edge(1,2);
    add_edge(2,3);

    add_edge(5,6);
    add_edge(8,9);
    add_edge(9,10);
    add_edge(10,11);

    add_edge(12,13);
    add_edge(13,14);
    add_edge(14,15);

    add_edge(0,4);
    add_edge(1,5);
    add_edge(2,6);
    add_edge(3,7);

    add_edge(4,8);
    add_edge(5,9);
    add_edge(6,10);
    add_edge(7,11);

    add_edge(8,12);
    add_edge(9,13);
    add_edge(10,14);
    add_edge(11,15);

    best_first_search(0, 11);

    return 0;
}
