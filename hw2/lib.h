#include <string>
using namespace std;
const int M = 20;
bool createBoard(const int& boardSize, char board[M][M]);
void markTheLocationfor2userMode(int& boardSize, char board[M][M], int arr[M][M], string loc = "undefined");
void markTheLocationforCompMode(int& boardSize, char board[M][M], int arr[M][M], string loc = "undefined");
int x_checkVictoryPath(char board[M][M], int arr[M][M], int& boardSize, int row, int col, int flag);
int o_checkVictoryPath(char board[M][M], int arr[M][M], int& boardSize, int row, int col, int flag);
int checkRowforFirstX(char board[M][M], int arr[M][M], int& boardSize);
int checkColforFirstO(char board[M][M], int arr[M][M], int& boardSize);
void printMarkedBoard(char board[M][M], int& boardSize);
void savingFile(char board[][M], int& boardSize);
void loadingFile(char board[][M]);