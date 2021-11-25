#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "hangman.h"

void start()
{
    printf("**********************\n");
    printf("*    HANGMAN GAME    *\n");
    printf("**********************\n");
}

void guess(char guesses[26], int *attempts)
{

    char guess;
    scanf(" %c", &guess);
    guesses[(*attempts)] = guess;
    (*attempts)++;
}
int madeAGuess(char letter, char guesses[26], int attempts)
{
    int find = 0;
    for (int j = 0; j < attempts; j++)
    {
        if (guesses[j] == letter)
        {
            find = 1;
            break;
        }
    }

    return find;
}

void printHangman(char secretWord[20], char guesses[26], int attempts)
{
    int errors = wrongGuess(secretWord, guesses, attempts);
    printf("  _______      \n");
    printf(" |/      |     \n");
    printf(" |      %c%c%c     \n", (errors >= 1 ? '(' : ' '),
           (errors >= 1 ? '_' : ' '), (errors >= 1 ? ')' : ' '));
    printf(" |      %c%c%c \n", (errors >= 3 ? '\\' : ' '), (errors >= 2 ? '|' : ' '), (errors >= 3 ? '/' : ' '));
    printf(" |       %c    \n", (errors >= 2 ? '|' : ' '));
    printf(" |      %c %c  \n", (errors >= 4 ? '/' : ' '), (errors >= 4 ? '\\' : ' '));
    printf(" |             \n");
    printf("_|___          \n");
    printf("\n\n");

    for (int i = 0; i < strlen(secretWord); i++)
    {
        int find = madeAGuess(secretWord[i], guesses, attempts);
        if (find)
        {
            printf("%c ", secretWord[i]);
        }
        else
        {
            printf("_ ");
        }
    }
    printf("\n");
}

void addWord()
{
    char yes;

    printf("want to add new word ? (S/N)");
    scanf(" %c", &yes);

    if (yes == 'S')
    {
        char newWord[256];
        printf("type a word: ");
        scanf("%s", newWord);

        FILE *f;

        f = fopen("words.txt", "r+");
        if (f == 0)
        {
            printf("Error\n");
            exit(1);
        }

        int amount;
        fscanf(f, "%d", &amount);
        amount++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", amount);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newWord);

        fclose(f);
    }
}

void chooseWord(char secretWord[20])
{
    FILE *f;
    int count;
    f = fopen("words.txt", "r");
    if (f == 0)
    {
        printf("Error\n");
        exit(1);
    }
    fscanf(f, "%d", &count);
    srand(time(0));
    int random = rand() % count;

    for (int i = 0; i <= random; i++)
        fscanf(f, "%s", secretWord);
    fclose(f);
}

int win(char secretWord[20], char guesses[26], int attempts)
{
    for (int i = 0; i < strlen(secretWord); i++)
    {
        if (!madeAGuess(secretWord[i], guesses, attempts))
        {
            return 0;
        }
    }

    return 1;
}

int wrongGuess(char secretWord[20], char guesses[26], int attempts)
{
    int errors = 0;

    for (int i = 0; i < attempts; i++)
    {
        int exist = 0;

        for (int j = 0; j < strlen(secretWord); j++)
        {
            if (guesses[i] == secretWord[j])
            {
                exist = 1;
                break;
            }
        }

        if (!exist)
            errors++;
    }

    return errors;
}
int hanged(char secretWord[20], char guesses[26], int attempts)
{
    return wrongGuess(secretWord, guesses, attempts) >= 5;
}
int main()
{
    char secretWord[20];

    char guesses[26];
    int attempts = 0;
    chooseWord(secretWord);
    start();

    do
    {
        printHangman(secretWord, guesses, attempts);
        guess(guesses, &attempts);

    } while (!win(secretWord, guesses, attempts) && !hanged(secretWord, guesses, attempts));
    if (hanged(secretWord, guesses, attempts))
    {
        printf("** You lose, Word is %s **\n", secretWord);
    }
    else
    {
        printf("Nice, you win :D\n");
    }
    addWord();
}