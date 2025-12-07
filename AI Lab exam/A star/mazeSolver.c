#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define NODES 16
#define MAX_DEG 4
#define INF 1000000

const char *names[NODES] = {
    "S","A","B","C",
    "D","E","F","G",
    "H","I","J","Key",
    "K","L","M","N"
};

int adj[NODES][MAX_DEG];
int deg[NODES];

int g_cost[NODES];
int h_cost[NODES];
int f_cost[NODES];
int parent_arr[NODES];
bool in_open[NODES];
bool closed[NODES];

void add_edge(int u, int v) {
    adj[u][deg[u]++] = v;
    adj[v][deg[v]++] = u;
}

int heuristic(int node, int goal) {
    int row = node / 4;
    int col = node % 4;
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
    int best_f = INF;

    for (int i = 0; i < NODES; i++) {
        if (in_open[i] && !closed[i] && f_cost[i] < best_f) {
            best_f = f_cost[i];
            best = i;
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

    printf("Path from %s to %s using A* Search:\n", names[start], names[goal]);
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", names[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\nTotal cost (steps) = %d\n", g_cost[goal]);
}

void astar(int start, int goal) {
    for (int i = 0; i < NODES; i++) {
        g_cost[i] = INF;
        h_cost[i] = 0;
        f_cost[i] = INF;
        parent_arr[i] = -1;
        in_open[i] = false;
        closed[i] = false;
    }

    g_cost[start] = 0;
    h_cost[start] = heuristic(start, goal);
    f_cost[start] = g_cost[start] + h_cost[start];
    in_open[start] = true;

    while (1) {
        int u = get_best_node();
        if (u == -1) {
            printf("No path found from %s to %s using A*.\n",
                   names[start], names[goal]);
            return;
        }

        if (u == goal) {
            print_path(start, goal);
            return;
        }

        in_open[u] = false;
        closed[u] = true;

        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            if (closed[v]) continue;

            int tentative_g = g_cost[u] + 1;

            if (!in_open[v] || tentative_g < g_cost[v]) {
                parent_arr[v] = u;
                g_cost[v] = tentative_g;
                h_cost[v] = heuristic(v, goal);
                f_cost[v] = g_cost[v] + h_cost[v];
                in_open[v] = true;
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

    int start = 0;
    int goal  = 11;

    printf("Maze solving using A* Search (S to Key):\n\n");
    astar(start, goal);

    return 0;
}
