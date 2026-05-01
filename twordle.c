// Jayden Scott
// Project 10
// 4/27/26

#include <stdio.h>


void loadWord(char mystery[]);
int getLen(char str[]);
void toLowerCase(char str[]);
int isValid(char guess[]);
int contains(char c, char str[]);
void printBoard(char history[6][6], int attempts, char mystery[]);
int isMatch(char guess[], char mystery[]);

int main() {
    char mysteryWord[10] = {0}; 
    char history[6][6] = {0};
    char currentGuess[100];
    int attempts = 0;
    int won = 0; 

    loadWord(mysteryWord);
    toLowerCase(mysteryWord); 

    while (attempts < 6 && !won) {
        if (attempts == 5) {
            printf("FINAL GUESS : ");
        } else {
            printf("GUESS %d! Enter your guess: ", attempts + 1);
        }

        while (1) {
            scanf("%s", currentGuess);
            if (isValid(currentGuess)) break;
            printf("Please try again: ");
        }

        toLowerCase(currentGuess);

        
        for (int i = 0; i < 5; i++) history[attempts][i] = currentGuess[i];
        
        attempts++;

        if (isMatch(currentGuess, mysteryWord)) {
            won = 1;
            printf("================================\n");
            
            printf("        "); 
            for(int i=0; i<5; i++) printf("%c", mysteryWord[i] - 32);
            printf("\n    You won in %d guesses!\n        Amazing!\n", attempts);
        } else {
            printBoard(history, attempts, mysteryWord);
        }
    }

    if (!won) {
        printf("You lost, better luck next time!\n");
    }

    return 0;
}

/
void loadWord(char mystery[]) {
    FILE *fptr = fopen("mystery.txt", "r");
    if (fptr != NULL) {
        fscanf(fptr, "%s", mystery);
        fclose(fptr);
    }
}


int getLen(char str[]) {
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}


void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') str[i] += 32;
    }
}


int isValid(char guess[]) {
    int len = getLen(guess);
    int alphaOk = 1;
    for (int i = 0; i < len; i++) {
        if (!((guess[i] >= 'a' && guess[i] <= 'z') || (guess[i] >= 'A' && guess[i] <= 'Z'))) alphaOk = 0;
    }
    if (len != 5) printf("Your guess must be 5 letters long.");
    if (!alphaOk) printf("Your guess must contain only letters.");
    if (len != 5 || !alphaOk) { printf("\n"); return 0; }
    return 1;
}


int contains(char c, char str[]) {
    for (int i = 0; i < 5; i++) {
        if (str[i] == c) return 1;
    }
    return 0;
}


void printBoard(char history[6][6], int attempts, char mystery[]) {
    printf("================================\n");
    for (int i = 0; i < attempts; i++) {
       
        for (int j = 0; j < 5; j++) {
            if (history[i][j] == mystery[j]) printf("%c", history[i][j] - 32);
            else printf("%c", history[i][j]);
        }
        printf("\n");

       
        for (int j = 0; j < 5; j++) {
            if (history[i][j] != mystery[j] && contains(history[i][j], mystery)) printf("^");
            else printf(" ");
        }
        printf("\n");
    }
}


int isMatch(char guess[], char mystery[]) {
    for (int i = 0; i < 5; i++) {
        if (guess[i] != mystery[i]) return 0;
    }
    return 1;
}

