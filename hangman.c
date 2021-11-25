#include <stdio.h>
#include <string.h>

void start()
{
    printf("**********************\n");
    printf("*    HANGMAN GAME    *\n");
    printf("**********************\n");
}

void guess(char guesses[26], int attempts)
{

    char guess;
    scanf(" %c", &guess);
    guesses[attempts] = guess;
}
int main()
{
    char secretWord[20];

    sprintf(secretWord, "MELANCIA");

    int win = 0;
    int hanged = 0;
    char guesses[26];
    int attempts = 0;

    start();

    do
    {
        for (int i = 0; i < strlen(secretWord); i++)
        {
            int find = 0;
            for (int j = 0; j < attempts; j++)
            {
                if (guesses[j] == secretWord[i])
                {
                    find = 1;
                    break;
                }
            }

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
        guess(guesses, attempts);
        attempts++;
    } while (!win && !hanged);
}