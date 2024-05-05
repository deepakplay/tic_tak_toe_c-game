#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <windows.h>

#define ROW 3
#define COL 3

char grid[ROW][COL] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '},
};

char player[2] = {'X', 'O'};
int currentPlayer = 0;

void printGrid();
int checkWin();
void resetGame();
bool isValidMove(int col, int row);
void makeMove(int col, int row);
int getPlayerType(char p);

int main()
{
    bool gameloop = true;

    int colInput = 0;
    int rowInput = 0;

    int checkWinStatus = -1;

    while (gameloop)
    {
        printGrid();
        checkWinStatus = checkWin();
        if (checkWinStatus != -1)
        {
            if (checkWinStatus == 1 || checkWinStatus == 2)
            {
                printf("\n\t\t\t\t\t\tPlayer [%c] Wins :-) ", player[checkWinStatus - 1]);
            }
            else if (checkWinStatus == 3)
            {
                printf("\n\t\t\t\t\t\tDraw Match !! ");
            }

            printf("\n\t\t\t\t\tDo You want to continue the game (Y/n)? ");

            fflush(stdin);

            char close = getchar();
            if (close != 'Y' && close != 'y')
                gameloop = false;
            else
                resetGame();

            continue;
        }

        printf("\n\t\t\t\t      Current Player [%c] Enter (x y): ", player[currentPlayer]);

        scanf("%d %d", &colInput, &rowInput);

        colInput--;
        rowInput--;

        if (!isValidMove(colInput, rowInput))
        {
            printf("\n\t\t\t\t\t  Invalid move! Try again");
            system("pause>nul");
            continue;
        }

        makeMove(colInput, rowInput);

        currentPlayer = !currentPlayer;
    }

    return 0;
}

void printGrid()
{
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\tTicTacToe Game by Deepak Kumar\n\n");
    printf("\t\t\t\t\tPlayer 1 [%c]\t   Player 2 [%c]", player[0], player[1]);
    printf("\n\n\n");
    printf("\t\t\t\t\t\t   1   2   3 \n\n");
    printf("\t\t\t\t\t\t1  %c | %c | %c \n", grid[0][0], grid[0][1], grid[0][2]);
    printf("\t\t\t\t\t\t  ---+---+---\n");
    printf("\t\t\t\t\t\t2  %c | %c | %c \n", grid[1][0], grid[1][1], grid[1][2]);
    printf("\t\t\t\t\t\t  ---+---+---\n");
    printf("\t\t\t\t\t\t3  %c | %c | %c \n", grid[2][0], grid[2][1], grid[2][2]);
}

bool isValidMove(int col, int row)
{
    if (row < 0 || row >= ROW || col < 0 || col >= COL || grid[row][col] != ' ')
        return false;
    return true;
}

void makeMove(int col, int row)
{
    grid[row][col] = player[currentPlayer];
}

int checkWin()
{
    /**
     * @return -1 not win
     * @return 1 Player 1 Win
     * @return 2 Player 2 Win
     * @return 3 Draw Match
     */

    for (int x = 0; x < 3; x++)
    {
        // horizontal
        if (((grid[x][0] == grid[x][1]) && (grid[x][1] == grid[x][2])) && grid[x][0] != ' ')
            return getPlayerType(grid[x][0]);

        // vertical
        if (((grid[0][x] == grid[1][x]) && (grid[1][x] == grid[2][x])) && grid[0][x] != ' ')
            return getPlayerType(grid[0][x]);
    }

    // left top to right bottom diagnoal
    if ((grid[0][0] == grid[1][1]) && (grid[1][1] == grid[2][2]) && grid[0][0] != ' ')
        return getPlayerType(grid[0][0]);

    // left bottom to right top diagnoal
    if ((grid[2][0] == grid[1][1]) && (grid[1][1] == grid[0][2]) && grid[2][0] != ' ')
        return getPlayerType(grid[2][0]);

    // check empty place in grid
    for (int y = 0; y < COL; y++)
        for (int x = 0; x < ROW; x++)
            if (grid[x][y] == ' ')
                return -1;

    return 3;
}

void resetGame()
{
    for (int y = 0; y < COL; y++)
        for (int x = 0; x < ROW; x++)
            grid[x][y] = ' ';

    currentPlayer = 0;
}

int getPlayerType(char p)
{
    if (p == player[0])
        return 1;
    else if (p == player[1])
        return 2;

    return -1;
}