#include <stdio.h>

#define EMPTY 0
#define CIRCLE 1
#define CROSS 2

/* Initialize the game board by setting all squares to EMPTY */
void initGameBoard(int gameBoard[6][7]) {

    // TODO : Complete this part
    int i, j;
    for (i=0; i<6; i++) {
        for (j=0; j<7; j++) {
            gameBoard[i][j] = EMPTY;
        }
    }

}



/* Display the game board on the screen.*/

void printGameBoard(int gameBoard[6][7]) {

    // TODO : Complete this part

        int i, j;
        for (i=0; i<6; i++) {
            for (j=0; j<7; j++) {
                if(gameBoard[i][j] == CIRCLE)
                    printf("|O|");
                else if(gameBoard[i][j] == CROSS)
                    printf("|X|");
                else
                    printf("| |");
            }
            printf("\n");
        }
    printf(" 1  2  3  4  5  6  7\n");
}



/* Ask the human player to place the mark.
   Assume that the user input must be an integer. */
void placeMarkByHumanPlayer(int gameBoard[6][7], int mark) {

    // TODO : Complete this part
    int i, place, printed = 0;


    while (1) {

        scanf("%d",&place);
        place -= 1;

        if(place < 0 || place > 6) {
            printf("Input out of range. Please input again:\n");
            continue;
        }
        else if(gameBoard[0][place]) {
            printf("Column is full. Please input again:\n");
            continue;
        }
        else
            break;

    }

    for (i=5; i>=0; i--) {
        if(!gameBoard[i][place] && !printed) {
            gameBoard[i][place] = mark;
            printed++;
        }
    }


}



/* Return 1 if there is a winner in the game, otherwise return 0.
   Note: the winner is the current player indicated in main(). */
int hasWinner(int gameBoard[6][7]){

    // TODO : Complete this part
    int i, j, mark;

    for(mark=1; mark<= 2; mark++) {
        //Get each first element
        for (i=0; i<6; i++) {
            for (j=0; j<7; j++) {;
                if(gameBoard[i][j] == mark) {

                    if(j <= 7 - 4) {
                        //Right Case
                        if(gameBoard[i][j + 1] == mark && gameBoard[i][j + 2] == mark && gameBoard[i][j + 3] == mark)
                            return 1;


                        if(i <= 6 - 4) {
                            //Diagonal Down Case
                            if(gameBoard[i + 1][j + 1] == mark && gameBoard[i + 2][j + 2] == mark && gameBoard[i + 3][j + 3] == mark)
                                return 1;

                        } else {
                            //Diagonal Up Case
                            if(gameBoard[i - 1][j + 1] == mark && gameBoard[i - 2][j + 2] == mark && gameBoard[i - 3][j + 3] == mark)
                                return 1;

                        }
                    }

                    //Down Case
                    if(i <= 6 - 4)
                        if(gameBoard[i + 1][j] == mark && gameBoard[i + 2][j] == mark && gameBoard[i + 3][j] == mark)
                                return 1;

                }
            }
        }
    }

    return 0;

}



/* Return 1 if the game board is full, otherwise return 0. */
int isFull(int gameBoard[6][7]) {

    // TODO : Complete this part
    int i;

    if(!hasWinner(gameBoard)){
        for (i=0; i<=6; i++) {
            if(gameBoard[0][i] == EMPTY) {
                return 0;
            }
        }
    }

    return 1;
}



/* Determine the next move of the computer player.*/

void placeMarkByComputerPlayer(int gameBoard[6][7]) {

    int player, i, j, added = 0;

    //Search Win Step
    for(player = 2; player >= 1; player--) {
        //2: Computer 1: Player
        for (i=0; i<6; i++) {
            for (j=0; j<7; j++) {
                if(!gameBoard[i][j] && !added) {

                    if(i != 6)
                        if(gameBoard[i+1][j] == EMPTY)
                            continue;

                    gameBoard[i][j] = player;

                    if(hasWinner(gameBoard)) {
                        added++;
                        if(player == 1)
                            gameBoard[i][j] = 2;
                    }
                    else
                        gameBoard[i][j] = 0;
                }
            }
        }
    }

    for (i=5; i>=0; i--) {
        for (j=6; j>=0; j--) {
            if(!gameBoard[i][j] && !added) {
                gameBoard[i][j] = 2;
                added++;
            }
        }
    }
}


/* The main function */
int main()
{
    /* Local variables */
    int gameBoard[6][7];    // Each element stores 0 (EMPTY), 1 (CIRCLE), or 2 (CROSS)
    int currentPlayer;      // 1: Player 1             2: Player 2
    int gameContinue;       // 1: The game continues   0: The game ends
    int numOfHumanPlayers;  // 1 or 2

    /* Initialize the local variables */
    initGameBoard(gameBoard);
    currentPlayer = 1;
    gameContinue = 1;
    printf("Enter the number of human players [1-2]:\n");
    scanf("%d", &numOfHumanPlayers);    // Assume that the user input must be valid


    /* Game start
       If there are two human players, they are Player 1 and Player 2
       If there is only one human player, he/she is Player 1 and another player is the computer player
       For both cases, Player 1 moves first and places the CIRCLE mark; while Player 2 (or the computer player) places the CROSS mark */

    printGameBoard(gameBoard);
    while(gameContinue) {
        if(numOfHumanPlayers == 1 && currentPlayer == 2) {
            printf("Computer's turn:\n");
            placeMarkByComputerPlayer(gameBoard);
        } else {
            printf("Player %d's turn:\n",currentPlayer);
            placeMarkByHumanPlayer(gameBoard, currentPlayer);
        }

        printGameBoard(gameBoard);

        if(hasWinner(gameBoard)) {
            if(numOfHumanPlayers == 1 && currentPlayer == 2)
                printf("Computer wins!");
            else
                printf("Congratulations! Player %d wins!",currentPlayer);
            gameContinue--;
        } else if(isFull(gameBoard)) {
            printf("Draw game.");
            gameContinue--;
        } else {
            currentPlayer = (currentPlayer - 1) ? 1 : 2;
        }

    }

    return 0;
}
