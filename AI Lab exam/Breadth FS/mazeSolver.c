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

void bfs(int start, int goal) {
    int queue[100];
    int front = 0, rear = 0;

    bool visited[NODES] = {false};
    int parent[NODES];

    for (int i = 0; i < NODES; i++)
        parent[i] = -1;

    queue[rear++] = start;
    visited[start] = true;

    bool found = false;

    while (front < rear) {
        int u = queue[front++];

        if (u == goal) {
            found = true;
            break;
        }

        for (int i = 0; i < deg[u]; i++) {
            int v = adj[u][i];
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                queue[rear++] = v;
            }
        }
    }

    if (!found) {
        printf("No path from %s to %s\n", names[start], names[goal]);
        return;
    }

    int path[100];
    int len = 0;
    int cur = goal;

    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    printf("Shortest path from %s to %s:\n", names[start], names[goal]);
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

    bfs(0, 11);

    return 0;
}
