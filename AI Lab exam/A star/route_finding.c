#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 20
#define INF 1000000000

int adj[MAX][MAX];
int n;

int heuristic[MAX];
char name[MAX][20];

int g_cost[MAX];
int f_cost[MAX];
int parent[MAX];
bool in_open[MAX];
bool closed[MAX];

int get_best_node() {
    int best = -1;
    int best_f = INF;

    for (int i = 0; i < n; i++) {
        if (in_open[i] && !closed[i] && f_cost[i] < best_f) {
            best_f = f_cost[i];
            best = i;
        }
    }
    return best;
}

void print_route(int start, int goal) {
    int path[MAX];
    int len = 0;
    int cur = goal;

    while (cur != -1) {
        path[len++] = cur;
        cur = parent[cur];
    }

    printf("Shortest route from %s to %s (A* Search):\n", name[start], name[goal]);
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", name[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\nTotal distance = %d\n", g_cost[goal]);
}

void astar(int start, int goal) {
    for (int i = 0; i < n; i++) {
        g_cost[i] = INF;
        f_cost[i] = INF;
        parent[i] = -1;
        in_open[i] = false;
        closed[i] = false;
    }

    g_cost[start] = 0;
    f_cost[start] = g_cost[start] + heuristic[start];
    in_open[start] = true;

    while (1) {
        int u = get_best_node();
        if (u == -1) {
            printf("No path found from %s to %s.\n", name[start], name[goal]);
            return;
        }

        if (u == goal) {
            print_route(start, goal);
            return;
        }

        in_open[u] = false;
        closed[u] = true;

        for (int v = 0; v < n; v++) {
            if (adj[u][v] > 0 && !closed[v]) {
                int w = adj[u][v];
                int tentative_g = g_cost[u] + w;

                if (!in_open[v] || tentative_g < g_cost[v]) {
                    parent[v] = u;
                    g_cost[v] = tentative_g;
                    f_cost[v] = g_cost[v] + heuristic[v];
                    in_open[v] = true;
                }
            }
        }
    }
}

int main() {
    n = 5;

    sprintf(name[0], "A");
    sprintf(name[1], "B");
    sprintf(name[2], "C");
    sprintf(name[3], "D");
    sprintf(name[4], "E");

    int adj_temp[5][5] = {
        {0, 2, 0, 1, 0},
        {2, 0, 3, 0, 0},
        {0, 3, 0, 4, 2},
        {1, 0, 4, 0, 5},
        {0, 0, 2, 5, 0}
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = adj_temp[i][j];

    heuristic[0] = 7;
    heuristic[1] = 6;
    heuristic[2] = 2;
    heuristic[3] = 4;
    heuristic[4] = 0;

    int start = 0;
    int goal  = 4;

    printf("Shortest Route Finding using A* Search\n\n");
    astar(start, goal);

    return 0;
}
