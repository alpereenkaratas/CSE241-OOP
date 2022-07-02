#include <iostream>
#include <string>
#include <ctime>
#include "lib.h"
using namespace std;

int main(){

    int boardSize;
    char gameModeSelection;
    bool keepPlayingFlag;
    string loc;
    int arr[M][M]={{0}};

    // game mode and board sizes are determined
    while(1){
        cout << "Select game mode:\n1) w/ computer\n2) Two player\n";
        cin >> gameModeSelection;
        cout << "Enter the board size: 6x6,7x7,8x8,9x9,10x10,11x11 or 12x12. (Enter it by one dimension. (For ex. 5,8 or 12)) --> ";
        cin >> boardSize;
        char board[M][M];
    
        keepPlayingFlag = createBoard(boardSize, board);
        if(keepPlayingFlag){
            if(gameModeSelection == '1')
                markTheLocationforCompMode(loc, boardSize, board, arr);
            else if (gameModeSelection = '2')
                markTheLocationfor2userMode(loc, boardSize, board, arr);
            else
                cout << "Enter valid mode";
        }    
    }

}