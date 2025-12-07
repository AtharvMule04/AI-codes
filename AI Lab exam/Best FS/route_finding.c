#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX 20

int adj[MAX][MAX];
int n;
int heuristic[MAX];
char name[MAX][20];

bool visited[MAX];
int parent[MAX];

int get_best_neighbor(int cur) {
    int best = -1;
    int best_h = INT_MAX;

    for (int v = 0; v < n; v++) {
        if (adj[cur][v] > 0 && !visited[v]) {
            if (heuristic[v] < best_h) {
                best_h = heuristic[v];
                best = v;
            }
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

    printf("\nFinal Route: ");
    for (int i = len - 1; i >= 0; i--) {
        printf("%s", name[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\n");
}

void best_first_search(int start, int goal) {
    printf("Best First Search from %s to %s\n\n", name[start], name[goal]);

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        parent[i] = -1;
    }

    int cur = start;

    while (1) {
        visited[cur] = true;
        printf("Visiting: %s (h=%d)\n", name[cur], heuristic[cur]);

        if (cur == goal) {
            printf("\nGoal Reached: %s\n", name[cur]);
            print_route(start, goal);
            return;
        }

        int next = get_best_neighbor(cur);

        if (next == -1) {
            printf("\nNo path found from %s.\n", name[cur]);
            return;
        }

        parent[next] = cur;
        cur = next;
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
        {0,2,0,1,0},
        {2,0,3,0,0},
        {0,3,0,4,2},
        {1,0,4,0,5},
        {0,0,2,5,0}
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

    best_first_search(start, goal);

    return 0;
}
