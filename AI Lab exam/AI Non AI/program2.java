import java.util.Scanner;

public class program2 {
    static int[] board = {2, 2, 2, 2, 2, 2, 2, 2, 2};
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        int turn = 1;
        printBoard();

        while (turn <= 9) {
            if (turn % 2 == 1) {
                System.out.println("Turn " + turn + " (You - X):");
                userMove();
            } else {
                System.out.println("Turn " + turn + " (Computer - O):");
                oMove(turn);
            }

            printBoard();

            if (checkWin(3)) {
                System.out.println("You (X) win!");
                break;
            } else if (checkWin(5)) {
                System.out.println("Computer (O) wins!");
                break;
            }

            turn++;
        }

        if (turn > 9) {
            System.out.println("It's a draw!");
        }

        System.out.println("Game Over!");
    }

    static void userMove() {
        int pos;
        while (true) {
            System.out.print("Enter your move (1-9): ");
            pos = sc.nextInt() - 1;

            if (pos < 0 || pos > 8) {
                System.out.println("Invalid input! Please enter a number between 1 and 9.");
            } else if (board[pos] != 2) {
                System.out.println("That position is already occupied. Try again.");
            } else {
                break;
            }
        }

        board[pos] = 3;
        System.out.println("You placed X at position: " + (pos + 1));
    }

    static void oMove(int turn) {
        int pos = -1;

        switch (turn) {
            case 2:
                if (board[4] == 2)
                    pos = 4;
                else
                    pos = 0;
                break;
            case 4:
                pos = posswin(3);
                if (pos == -1) pos = make2();
                break;
            case 6:
                pos = posswin(5);
                if (pos == -1) pos = posswin(3);
                if (pos == -1) pos = make2();
                break;
            case 8:
                pos = posswin(5);
                if (pos == -1) pos = posswin(3);
                if (pos == -1) pos = findBlank();
                break;
        }

        board[pos] = 5;
        System.out.println("Computer placed O at position: " + (pos + 1));
    }

    static int posswin(int player) {
        int[][] winLines = {
                {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                {0, 4, 8}, {2, 4, 6}
        };

        int winProd = player * player * 2;

        for (int[] line : winLines) {
            int prod = board[line[0]] * board[line[1]] * board[line[2]];
            if (prod == winProd) {
                for (int idx : line) {
                    if (board[idx] == 2)
                        return idx;
                }
            }
        }
        return -1;
    }

    static int make2() {
        int[] prefs = {1, 3, 5, 7};
        for (int i : prefs) {
            if (board[i] == 2)
                return i;
        }
        return findBlank();
    }

    static int findBlank() {
        for (int i = 0; i < 9; i++) {
            if (board[i] == 2)
                return i;
        }
        return -1;
    }

    static boolean checkWin(int player) {
        int[][] winLines = {
                {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
                {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
                {0, 4, 8}, {2, 4, 6}
        };

        for (int[] line : winLines) {
            if (board[line[0]] == player &&
                board[line[1]] == player &&
                board[line[2]] == player)
                return true;
        }
        return false;
    }

    static void printBoard() {
        System.out.println();
        for (int i = 0; i < 9; i++) {
            char c;
            if (board[i] == 2)
                c = ' ';
            else if (board[i] == 3)
                c = 'X';
            else
                c = 'O';

            System.out.print(" " + c + " ");
            if (i % 3 != 2)
                System.out.print("|");
            else if (i != 8)
                System.out.println("\n-----------");
        }
        System.out.println("\n");
    }
}
