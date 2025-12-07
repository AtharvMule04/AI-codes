#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 20
#define MAX_LETTERS 10

char word1[MAX_WORD_LEN];
char word2[MAX_WORD_LEN];
char word3[MAX_WORD_LEN];

char letters[MAX_LETTERS];
int letterIndex[26];
int numLetters = 0;

int assignDigit[MAX_LETTERS];
bool digitUsed[10];
bool cannotBeZero[MAX_LETTERS];

bool solutionFound = false;

long long evalWord(const char *w) {
    long long value = 0;
    for (int i = 0; w[i] != '\0'; i++) {
        char c = w[i];
        int idx = letterIndex[c - 'A'];
        int d = assignDigit[idx];
        value = value * 10 + d;
    }
    return value;
}

void solve(int pos) {
    if (pos == numLetters) {
        int idx1 = letterIndex[word1[0] - 'A'];
        int idx2 = letterIndex[word2[0] - 'A'];
        int idx3 = letterIndex[word3[0] - 'A'];
        if (assignDigit[idx1] == 0 || assignDigit[idx2] == 0 || assignDigit[idx3] == 0)
            return;

        long long v1 = evalWord(word1);
        long long v2 = evalWord(word2);
        long long v3 = evalWord(word3);

        if (v1 + v2 == v3) {
            solutionFound = true;
            printf("\nSolution:\n");
            printf("  %s = %lld\n", word1, v1);
            printf("+ %s = %lld\n", word2, v2);
            printf("= %s = %lld\n", word3, v3);

            printf("\nLetter to digit mapping:\n");
            for (int i = 0; i < numLetters; i++) {
                printf("  %c = %d\n", letters[i], assignDigit[i]);
            }
            printf("\n");
        }
        return;
    }

    for (int d = 0; d <= 9; d++) {
        if (digitUsed[d]) continue;
        if (d == 0 && cannotBeZero[pos]) continue;

        digitUsed[d] = true;
        assignDigit[pos] = d;

        solve(pos + 1);

        assignDigit[pos] = -1;
        digitUsed[d] = false;
    }
}

int main() {
    for (int i = 0; i < 26; i++)
        letterIndex[i] = -1;

    printf("Enter first word  (e.g., SEND): ");
    scanf("%s", word1);
    printf("Enter second word (e.g., MORE): ");
    scanf("%s", word2);
    printf("Enter result word (e.g., MONEY): ");
    scanf("%s", word3);

    char *words[3] = {word1, word2, word3};

    for (int w = 0; w < 3; w++) {
        for (int i = 0; words[w][i] != '\0'; i++) {
            char c = toupper((unsigned char)words[w][i]);
            words[w][i] = c;
            if (c < 'A' || c > 'Z') continue;

            if (letterIndex[c - 'A'] == -1) {
                if (numLetters >= MAX_LETTERS) {
                    printf("\nError: More than %d distinct letters.\n", MAX_LETTERS);
                    return 1;
                }
                letterIndex[c - 'A'] = numLetters;
                letters[numLetters] = c;
                numLetters++;
            }
        }
    }

    for (int i = 0; i < numLetters; i++)
        cannotBeZero[i] = false;

    if (isalpha(word1[0])) cannotBeZero[letterIndex[word1[0] - 'A']] = true;
    if (isalpha(word2[0])) cannotBeZero[letterIndex[word2[0] - 'A']] = true;
    if (isalpha(word3[0])) cannotBeZero[letterIndex[word3[0] - 'A']] = true;

    for (int i = 0; i < numLetters; i++)
        assignDigit[i] = -1;
    for (int d = 0; d < 10; d++)
        digitUsed[d] = false;

    printf("\nSolving cryptarithmetic: %s + %s = %s\n", word1, word2, word3);
    printf("(Max distinct letters allowed: %d)\n", MAX_LETTERS);

    solve(0);

    if (!solutionFound) {
        printf("\nNo solution found.\n");
    }

    return 0;
}
