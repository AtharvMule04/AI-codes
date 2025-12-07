/* Missionaries and Cannibals using A* Search
 *
 * State: (M, C, boat)
 *   M    = missionaries on left bank
 *   C    = cannibals on left bank
 *   boat = 0 -> boat on left, 1 -> boat on right
 *
 * Start state: (3,3,0)
 * Goal state : (0,0,1)
 *
 * A*:
 *   g(n) = number of boat moves from start
 *   h(n) = M + C  (people still left on left bank)
 *   f(n) = g(n) + h(n)
 *
 * Compile:
 *   gcc astar_mnc.c -o astar_mnc
 *
 * Run:
 *   ./astar_mnc
 */

#include <stdio.h>
#include <stdbool.h>

#define MAX_STATES 1000
#define INF 1000000

typedef struct {
    int M;        // missionaries on left
    int C;        // cannibals on left
    int boat;     // 0 = left, 1 = right
    int parent;   // parent index in S[]
    int g;        // cost so far (number of moves)
    int h;        // heuristic value
    int f;        // f = g + h
    bool expanded;// whether this node has been expanded
} Node;

Node S[MAX_STATES];
int state_count = 0;

// ---------- Utility functions ----------

// check if state is safe on both banks
bool is_safe(int M, int C) {
    int Mr = 3 - M;  // missionaries on right
    int Cr = 3 - C;  // cannibals on right

    // left bank unsafe: cannibals > missionaries and missionaries present
    if (M > 0 && C > M) return false;

    // right bank unsafe: cannibals > missionaries and missionaries present
    if (Mr > 0 && Cr > Mr) return false;

    return true;
}

bool same_state(Node a, Node b) {
    return a.M == b.M && a.C == b.C && a.boat == b.boat;
}

bool is_visited(Node s) {
    for (int i = 0; i < state_count; i++) {
        if (same_state(S[i], s)) return true;
    }
    return false;
}

// heuristic: number of people still on left bank
int heuristic(int M, int C, int boat) {
    (void)boat; // not used here, but kept for extensibility
    return M + C;
}

// Add new state to S[], return its index or -1 if not added
int add_state(int M, int C, int boat, int parent) {
    if (!is_safe(M, C)) return -1;

    Node s;
    s.M = M;
    s.C = C;
    s.boat = boat;
    s.parent = parent;
    s.expanded = false;

    if (parent == -1)
        s.g = 0;                 // start state
    else
        s.g = S[parent].g + 1;   // each move cost = 1

    s.h = heuristic(M, C, boat);
    s.f = s.g + s.h;

    if (is_visited(s)) return -1;

    if (state_count >= MAX_STATES) {
        printf("Too many states!\n");
        return -1;
    }

    S[state_count] = s;
    return state_count++;
}

void print_path(int idx) {
    if (idx == -1) return;
    print_path(S[idx].parent);
    printf("(%dM, %dC, Boat: %s)\n",
           S[idx].M, S[idx].C,
           S[idx].boat == 0 ? "Left" : "Right");
}

// Get index of unexpanded node with smallest f = g + h
int get_best_node_index() {
    int best = -1;
    int best_f = INF;

    for (int i = 0; i < state_count; i++) {
        if (!S[i].expanded && S[i].f < best_f) {
            best_f = S[i].f;
            best = i;
        }
    }
    return best;
}

// ---------- A* Search ----------
void astar_search() {
    // initial: 3M,3C on left, boat on left
    int root_index = add_state(3, 3, 0, -1);

    if (root_index == -1) {
        printf("Failed to create initial state.\n");
        return;
    }

    int goal_index = -1;

    while (1) {
        int idx = get_best_node_index();
        if (idx == -1) break;  // no more nodes

        Node cur = S[idx];
        S[idx].expanded = true;

        // goal: all on right -> left has 0M,0C, boat right
        if (cur.M == 0 && cur.C == 0 && cur.boat == 1) {
            goal_index = idx;
            break;
        }

        int M = cur.M;
        int C = cur.C;

        if (cur.boat == 0) {
            // boat on left → send to right
            int child;
            if (M >= 1) {
                child = add_state(M-1, C, 1, idx);
                (void)child;
            }
            if (M >= 2) {
                child = add_state(M-2, C, 1, idx);
                (void)child;
            }
            if (C >= 1) {
                child = add_state(M, C-1, 1, idx);
                (void)child;
            }
            if (C >= 2) {
                child = add_state(M, C-2, 1, idx);
                (void)child;
            }
            if (M >= 1 && C >= 1) {
                child = add_state(M-1, C-1, 1, idx);
                (void)child;
            }
        } else {
            // boat on right → bring back to left
            int child;
            if (M <= 2) {
                child = add_state(M+1, C, 0, idx);
                (void)child;
            }
            if (M <= 1) {
                child = add_state(M+2, C, 0, idx);
                (void)child;
            }
            if (C <= 2) {
                child = add_state(M, C+1, 0, idx);
                (void)child;
            }
            if (C <= 1) {
                child = add_state(M, C+2, 0, idx);
                (void)child;
            }
            if (M <= 2 && C <= 2) {
                child = add_state(M+1, C+1, 0, idx);
                (void)child;
            }
        }
    }

    if (goal_index == -1) {
        printf("No solution using A* Search.\n");
    } else {
        printf("Solution using A* Search (Missionaries and Cannibals):\n");
        print_path(goal_index);
        printf("Total moves (g) = %d\n", S[goal_index].g);
    }
}

// ---------- main ----------
int main() {
    astar_search();
    return 0;
}
