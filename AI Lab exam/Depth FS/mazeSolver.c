#include <stdio.h>
#include <stdbool.h>

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

void add_edge(int u, int v) {
    adj[u][deg[u]++] = v;
    adj[v][deg[v]++] = u;
}

bool visited[NODES];
int parent_arr[NODES];
bool found_goal = false;

void dfs_util(int u, int goal) {
    if (found_goal) return;
    visited[u] = true;

    if (u == goal) {
        found_goal = true;
        return;
    }

    for (int i = 0; i < deg[u]; i++) {
        int v = adj[u][i];
        if (!visited[v]) {
            parent_arr[v] = u;
            dfs_util(v, goal);
            if (found_goal) return;
        }
    }
}

void dfs(int start, int goal) {
    for (int i = 0; i < NODES; i++) {
        visited[i] = false;
        parent_arr[i] = -1;
    }

    found_goal = false;
    dfs_util(start, goal);

    if (!found_goal) {
        printf("No path from %s to %s (DFS)\n", names[start], names[goal]);
        return;
    }

    int path[100];
    int len = 0;
    int cur = goal;

    while (cur != -1) {
        path[len++] = cur;
        cur = parent_arr[cur];
    }

    printf("Path from %s to %s using DFS:\n", names[start], names[goal]);
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", names[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\n");
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

    dfs(0, 11);
    return 0;
}
