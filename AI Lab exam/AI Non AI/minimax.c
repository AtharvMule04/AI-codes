#include <stdio.h>

#define PLAYER 'O'
#define AI 'X'

char board[3][3] = {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

void printBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int isMovesLeft() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '_')
                return 1;
    return 0;
}

int evaluate() {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] &&
            board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] &&
            board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    return 0;
}

int minimax(int depth, int isMax) {
    int score = evaluate();

    if (score == 10)
        return score - depth;

    if (score == -10)
        return score + depth;

    if (isMovesLeft() == 0)
        return 0;

    if (isMax) {
        int best = -1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = AI;
                    int value = minimax(depth + 1, 0);
                    if (value > best)
                        best = value;
                    board[i][j] = '_';
                }
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '_') {
                    board[i][j] = PLAYER;
                    int value = minimax(depth + 1, 1);
                    if (value < best)
                        best = value;
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = -1000;
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '_') {
                board[i][j] = AI;
                int moveVal = minimax(0, 0);
                board[i][j] = '_';

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[bestRow][bestCol] = AI;
    printf("AI chooses: (%d, %d)\n", bestRow, bestCol);
}

int main() {
    int row, col;
    int moves = 0;

    while (isMovesLeft()) {
        printBoard();

        if (moves % 2 == 0) {
            printf("Player turn (row col): ");
            scanf("%d %d", &row, &col);
            if (board[row][col] == '_') {
                board[row][col] = PLAYER;
            } else {
                printf("Invalid move. Try again.\n");
                continue;
            }
        } else {
            findBestMove();
        }

        int result = evaluate();
        if (result == 10) {
            printBoard();
            printf("AI Wins!\n");
            break;
        } else if (result == -10) {
            printBoard();
            printf("Player Wins!\n");
            break;
        } else if (!isMovesLeft()) {
            printBoard();
            printf("Draw!\n");
            break;
        }

        moves++;
    }
    return 0;
}
