void start();

void guess(char guesses[26], int *attempts);

int madeAGuess(char letter, char guesses[26], int attempts);

void printHangman(char secretWord[20], char guesses[26], int attempts);

void chooseWord(char secretWord[20]);

int win(char secretWord[20], char guesses[26], int attempts);

int wrongGuess(char secretWord[20], char guesses[26], int attempts);
int hanged(char secretWord[20], char guesses[26], int attempts);

void addWord();