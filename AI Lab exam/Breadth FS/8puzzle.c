#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 9
#define MAX_STATES 400000

typedef struct {
    int tiles[N];
    int parent;
} Node;

Node queue_states[MAX_STATES];
int front = 0, rear = 0;

int goal_state[N] = {1, 2, 3,
                     4, 5, 6,
                     7, 8, 0};

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

bool is_goal(const int *tiles) {
    for (int i = 0; i < N; i++) {
        if (tiles[i] != goal_state[i])
            return false;
    }
    return true;
}

bool are_same(const int *a, const int *b) {
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

int find_blank(const int *tiles) {
    for (int i = 0; i < N; i++) {
        if (tiles[i] == 0)
            return i;
    }
    return -1;
}

bool is_visited(const int *tiles) {
    for (int i = 0; i < rear; i++) {
        if (are_same(queue_states[i].tiles, tiles))
            return true;
    }
    return false;
}

void copy_state(const int *src, int *dst) {
    for (int i = 0; i < N; i++)
        dst[i] = src[i];
}

void enqueue(const int *tiles, int parent_index) {
    if (rear >= MAX_STATES) {
        printf("Error: Queue overflow\n");
        exit(1);
    }
    copy_state(tiles, queue_states[rear].tiles);
    queue_states[rear].parent = parent_index;
    rear++;
}

void print_solution_path(int goal_index) {
    int path[MAX_STATES];
    int length = 0;

    int index = goal_index;
    while (index != -1) {
        path[length++] = index;
        index = queue_states[index].parent;
    }

    printf("\nSolution found in %d moves:\n", length - 1);
    for (int i = length - 1; i >= 0; i--) {
        printf("\nStep %d:\n", length - 1 - i);
        print_state(queue_states[path[i]].tiles);
    }
}

void bfs() {
    int goal_index = -1;

    while (front < rear) {
        Node current = queue_states[front];
        int current_index = front;
        front++;

        if (is_goal(current.tiles)) {
            goal_index = current_index;
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

                if (!is_visited(new_tiles)) {
                    enqueue(new_tiles, current_index);
                }
            }
        }
    }

    if (goal_index == -1) {
        printf("No solution found.\n");
    } else {
        print_solution_path(goal_index);
    }
}

int main() {
    int initial[N];

    input_initial(initial);
    enqueue(initial, -1);
    bfs();

    return 0;
}
