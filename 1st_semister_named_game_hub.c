#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Four in a Row
#define ROWS 6
#define COLS 7

char fourInARowBoard[ROWS][COLS];

// Function to initialize the Four in a Row board
void initializeFourInARowBoard() {
    int i;
	for ( i = 0; i < ROWS; i++) {
        int j;
		for ( j = 0; j < COLS; j++) {
            fourInARowBoard[i][j] = ' ';
        }
    }
}

// Function to display the Four in a Row board
void displayFourInARowBoard() {
    printf("\n");
    int i;
	for (i = 0; i < ROWS; i++) {
        int j;
		for ( j = 0; j < COLS; j++) {
            printf("| %c ", fourInARowBoard[i][j]);
        }
        printf("|\n");
    }
    int j;
	for ( j = 0; j < COLS; j++) {
        printf(" ---");
    }
    printf("\n");
}

// Function to check if a player has won in Four in a Row
int checkFourInARowWin(char player) {
    // Check rows
    int i;
	for ( i = 0; i < ROWS; i++) {
        int j;
		for ( j = 0; j <= COLS - 4; j++) {
            if (fourInARowBoard[i][j] == player &&
                fourInARowBoard[i][j + 1] == player &&
                fourInARowBoard[i][j + 2] == player &&
                fourInARowBoard[i][j + 3] == player)
                 {
                    
                return 1; // Player has won
            }
        }
    }

    // Check columns
    
	for ( i = 0; i <= ROWS - 4; i++) {
        int j;
		for ( j = 0; j < COLS; j++) {
            if (fourInARowBoard[i][j] == player &&
                fourInARowBoard[i + 1][j] == player &&
                fourInARowBoard[i + 2][j] == player &&
                fourInARowBoard[i + 3][j] == player) {
                return 1; // Player has won
            }
        }
    }

    // Check diagonals
    
	for (i = 0; i <= ROWS - 4; i++) {
        int j;
		for ( j = 0; j <= COLS - 4; j++) {
            if (fourInARowBoard[i][j] == player &&
                fourInARowBoard[i + 1][j + 1] == player &&
                fourInARowBoard[i + 2][j + 2] == player &&
                fourInARowBoard[i + 3][j + 3] == player) {
                return 1; // Player has won
            }
        }
    }

    for ( i = 0; i <= ROWS - 4; i++) {
        int j;
		for ( j = 3; j < COLS; j++) {
            if (fourInARowBoard[i][j] == player &&
                fourInARowBoard[i + 1][j - 1] == player &&
                fourInARowBoard[i + 2][j - 2] == player &&
                fourInARowBoard[i + 3][j - 3] == player) {
                return 1; // Player has won
            }
        }
    }

    return 0; // No win yet
}

// Function to make a move in Four in a Row
int makeFourInARowMove(int col, char player) {
    int i;
	for ( i = ROWS - 1; i >= 0; i--) {
        if (fourInARowBoard[i][col] == ' ') {
            fourInARowBoard[i][col] = player;
            return 1; // Valid move
        }
    }
    return 0; // Invalid move (column is full)
}

// Function to check if the Four in a Row board is full
int isFourInARowBoardFull() {
    int i;
	for (i = 0; i < COLS; i++) {
        if (fourInARowBoard[0][i] == ' ') {
            return 0; // The board is not full
        }
    }
    return 1; // The board is full
}

// Hangman

int attempts;
int incorrectGuesses;
int ts;  // Total attempts allowed

// Function to randomly select a word based on the chosen category
const char* chooseWord(const char* category) {
    const char* animalWords[] = {"lion", "elephant", "giraffe", "monkey", "zebra","panda",};
    const char* countryWords[] = {"france", "canada", "japan", "brazil", "india","pakistan",};

    int wordCount;
    const char** wordList;

    if (strcmp(category, "animals") == 0) {
        wordList = animalWords;
        wordCount = sizeof(animalWords) / sizeof(animalWords[0]);
    } else if (strcmp(category, "countries") == 0) {
        wordList = countryWords;
        wordCount = sizeof(countryWords) / sizeof(countryWords[0]);
    } else {
        printf("Invalid category.\n");
        exit(EXIT_FAILURE);
    }

    // Generate a random index to select a word from the chosen category
    int randomIndex = rand() % wordCount;

    return wordList[randomIndex];
}

// Function to initialize the display word (replacing letters with underscores)
void initializeDisplayWord(const char* word, char* displayWord) {
    int length = strlen(word);
    int i;
    for (i = 0; i < length; i++) {
        if (word[i] >= 'a' && word[i] <= 'z') {
            displayWord[i] = '_';
        } else {
            displayWord[i] = word[i];
        }
    }
    displayWord[length] = '\0';
}

// Function to update the display word based on the guessed letter
void updateDisplayWord(const char* word, char* displayWord, char guessedLetter) {
    int length = strlen(word);
    int i;
    for (i = 0; i < length; i++) {
        if (word[i] == guessedLetter) {
            displayWord[i] = guessedLetter;
        }
    }
}

// Function to check if the word has been completely guessed
int isWordGuessed(const char* displayWord) {
    return strchr(displayWord, '_') == NULL;
}

// Function to draw the hangman figure
void drawHangman(int incorrectGuesses) {
    switch (incorrectGuesses) {
        case 1:
            printf("  O\n");
            break;
        case 2:
            printf("  O\n  |\n");
            break;
        case 3:
            printf("  O\n \\|\n");
            break;
        case 4:
            printf("  O\n \\|/\n");
            break;
        case 5:
            printf("  O\n \\|/\n  |\n");
            break;
        case 6:
            printf("  O\n \\|/\n  |\n /\n");
            break;
        case 7:
            printf("  O\n \\|/\n  |\n / \\\n");
            break;
        case 8:
            printf("  O\n \\|/\n  |\n / \\\n");
            break;
        default:
            break;
    }
}

int playHangman(const char* category) {
    attempts = ts;
    incorrectGuesses = 0;

    char guessedLetter;
    const char* word = chooseWord(category);
    char displayWord[strlen(word)];

    initializeDisplayWord(word, displayWord);

    while (attempts > 0) {
        printf("\nCategory: %s\n", category);
        printf("Word: %s\n", displayWord);
        printf("Attempts left: %d\n", attempts);

        drawHangman(incorrectGuesses);

        printf("Enter a letter: ");
        scanf(" %c", &guessedLetter); // Leave a space before %c to consume the newline character
system("cls");
        // Check if the guessed letter is in the word
        if (strchr(word, guessedLetter) != NULL) {
            printf("Correct!\n");
            updateDisplayWord(word, displayWord, guessedLetter);

            // Check if the word has been completely guessed
            if (isWordGuessed(displayWord)) {
                printf("Congratulations! You guessed the word: %s\n", word);
                return 1; // Player wins
            }
        } else {
            printf("Incorrect. Try again.\n");
            attempts--;
            incorrectGuesses++;

            // Check if the player has run out of attempts
            if (attempts == 0) {
                printf("Sorry, you ran out of attempts. The correct word was: %s\n", word);
                return 0; // Player loses
           
            }
        }
    }

    return 0;
}

// Tic-Tac-Toe
#define TIC_TAC_TOE_SIZE 3

char ticTacToeBoard[TIC_TAC_TOE_SIZE][TIC_TAC_TOE_SIZE];

// Function to initialize the Tic-Tac-Toe board
void initializeTicTacToeBoard() {
    int i;
	for (i = 0; i < TIC_TAC_TOE_SIZE; i++) {
        int j;
		for (j = 0; j < TIC_TAC_TOE_SIZE; j++) {
            ticTacToeBoard[i][j] = ' ';
        }
    }
}

// Function to display the Tic-Tac-Toe board
void displayTicTacToeBoard() {
    printf("\n");
    int i;
	for (i = 0; i < TIC_TAC_TOE_SIZE; i++) {
        int j;
		for (j = 0; j < TIC_TAC_TOE_SIZE; j++) {
            printf("| %c ", ticTacToeBoard[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}

// Function to check if a player has won in Tic-Tac-Toe
int checkTicTacToeWin(char player) {
    // Check rows and columns
    int i;
	for (i = 0; i < TIC_TAC_TOE_SIZE; i++) {
        if ((ticTacToeBoard[i][0] == player && ticTacToeBoard[i][1] == player && ticTacToeBoard[i][2] == player) ||
            (ticTacToeBoard[0][i] == player && ticTacToeBoard[1][i] == player && ticTacToeBoard[2][i] == player)) {
            return 1; // Player has won
        }
    }

    // Check diagonals
    if ((ticTacToeBoard[0][0] == player && ticTacToeBoard[1][1] == player && ticTacToeBoard[2][2] == player) ||
        (ticTacToeBoard[0][2] == player && ticTacToeBoard[1][1] == player && ticTacToeBoard[2][0] == player)) {
        return 1; // Player has won
    }

    return 0; // No win yet
}

// Function to check if the Tic-Tac-Toe board is full
int isTicTacToeBoardFull() {
    int i;
	for ( i = 0; i < TIC_TAC_TOE_SIZE; i++) {
        int j;
		for (j = 0; j < TIC_TAC_TOE_SIZE; j++) {
            if (ticTacToeBoard[i][j] == ' ') {
                return 0; // The board is not full
            }
        }
    }
    return 1; // The board is full
}

// Function to make a move in Tic-Tac-Toe
int makeTicTacToeMove(int row, int col, char player) {
    if (row < 0 || row >= TIC_TAC_TOE_SIZE || col < 0 || col >= TIC_TAC_TOE_SIZE || ticTacToeBoard[row][col] != ' ') {
        return 0; // Invalid move
    }

    ticTacToeBoard[row][col] = player;
    return 1; // Valid move
}

// Game Hub
int main() {
    int gameChoice;
    char currentPlayer;
    system("cls");
    // Seed the random number generator for Hangman
    srand(time(NULL));
    do {
        printf("\n\n\n\n\n\t\t\t\t\t\t WELCOME    TO \n\n\t\t\t\t\t\t    Game Hub\n\n\t\t\t\t\t      CREATED BY THE CODERS\n\n");
       getchar();
                 system("cls");
	    printf ("Enter the game number that you want to play \n\n\n");
	    printf("1. Four in a Row\n\n");
        printf("2. Hangman\n\n");
        printf("3. Tic-Tac-Toe\n\n");
        printf("0. Exit\n");
        printf("Enter your choice (0-3): ");
        scanf("%d", &gameChoice);
                 system("cls");

        switch (gameChoice) {
            case 1:
                // Four in a Row
                initializeFourInARowBoard();
                currentPlayer = 'X';

                do {
                    displayFourInARowBoard();

                    // Get the column where the current player wants to place their piece
                    int column;
                    printf("Player %c, enter column (1-7): ", currentPlayer);
                    scanf("%d", &column);

                    // Adjust column to 0-based index
                    column--;
                    system("cls");

                    // Check if the move is valid
                    if (column < 0 || column >= COLS || !makeFourInARowMove(column, currentPlayer)) {
                        printf("Invalid move. Please try again.\n");
                       
                        continue;
                    }

                    // Check for a win
                    if (checkFourInARowWin(currentPlayer)) {
                        displayFourInARowBoard();
                        printf("Player %c wins!\n", currentPlayer);
                        break;
                    }

                    // Check for a tie
                    if (isFourInARowBoardFull()) {
                        displayFourInARowBoard();
                        printf("It's a tie!\n");
                        break;
                    }

                    // Switch to the other player
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                   
                } while (1);
                printf("the game has ended ");
                 
				 
				 
                 
                 scanf("%");
				break;

            case 2:
                // Hangman
             ts = 8;  // Change the number of attempts here

    char category[20];
    int gameResult;

    printf("Hangman with Categories\n");
    printf("Choose a category: animals or countries\n");
    scanf("%s", category);
system("cls");
    gameResult = playHangman(category);

    if (gameResult) {
        printf("You won!\n");
    } else {
        printf("You lost.\n");
    }

   
   
    
    
    printf("the game has ended");
             scanf("%");
                 
                 continue;
      
	  return 0 ;
	            break;

            case 3:
                // Tic-Tac-Toe
                initializeTicTacToeBoard();
                currentPlayer = 'X';

                do {
                    displayTicTacToeBoard();

                    // Get the row and column where the current player wants to place their mark
                    int row, col;
                    printf("Player %c, enter row and column (1-3): ", currentPlayer);
                    scanf("%d %d", &row, &col);
                    system("cls");

                    // Adjust row and column to 0-based index
                    row--;
                    col--;

                    // Check if the move is valid
                    if (!makeTicTacToeMove(row, col, currentPlayer)) {
                        printf("Invalid move. Please try again.\n");
                        continue;
                    }

                    // Check for a win
                    if (checkTicTacToeWin(currentPlayer)) {
                        displayTicTacToeBoard();
                        printf("Player %c wins!\n", currentPlayer);
                        break;
                    }

                    // Check for a tie
                    if (isTicTacToeBoardFull()) {
                        displayTicTacToeBoard();
                        printf("It's a tie!\n");
                        break;
                    }

                    // Switch to the other player
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

                } while (1);
                 scanf("%");
                 return 1;
                 system("cls");
                 continue;
				
				break;

            case 0:
                printf("Exiting the Game Hub. Goodbye!\n");
                 getchar();
                 system("cls");
                 continue;
                 
                 
				break;

            default:
                printf("Invalid choice. Please enter a number between 0 and 3.\n");
        }

    } while (gameChoice != 0);

    return 0;

}

