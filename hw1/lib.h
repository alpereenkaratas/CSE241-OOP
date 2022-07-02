#include <string>
using namespace std;
const int M = 20;
bool createBoard(int boardSize, char board[M][M]);
void markTheLocationfor2userMode(string loc, int boardSize, char board[M][M], int arr[M][M]);
void markTheLocationforCompMode(string loc, int boardSize, char board[M][M], int arr[M][M]);
int x_checkVictoryPath(char board[M][M], int arr[M][M], int boardSize, int row, int col, int flag);
int o_checkVictoryPath(char board[M][M], int arr[M][M], int boardSize, int row, int col, int flag);
int checkRowforFirstX(char board[M][M], int arr[M][M], int boardSize);
int checkColforFirstO(char board[M][M], int arr[M][M], int boardSize);
void printMarkedBoard(char board[M][M], int boardSize);