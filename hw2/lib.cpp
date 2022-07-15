#include <iostream>
#include <string>
#include <ctime>
#include "lib.h"
#include <fstream>
using namespace std;

enum CellState{
    user1 = 'x',
    user2 = 'o',
    emp = '.'
};

// function by which board dimensions are determined
bool createBoard(const int &boardSize, char board[][M]){
    
    if(boardSize >= 6 && boardSize <= 12){

        for(int i = 0; i < boardSize; ++i){
            for(int j = 0; j < boardSize; ++j){
                board[i][j] = emp;
            }
        }

        for(int i = 65; i < 65+boardSize; ++i){
            cout << " " << static_cast<char>(i) << " ";
        }
        
        cout << "\n";

        for(int i = 0; i < boardSize; ++i){
            cout << i+1 << " ";
            cout << string(i,' ');
            for(int j = 0; j < boardSize; ++j){
                cout << board[i][j];
                cout << "  ";
            }
            cout << "  ";
            cout << "\n";
        }
        return true;
    }
    else{
        cerr << "Please enter valid dimension\n";
        return false;
    }
}

// the function of the game mode, which allows it to be played with one player and computer
void markTheLocationforCompMode(int& boardSize, char board[][M], int arr[][M], string loc){
    string sameLocErr = "You cannot mark the marked point again!";
    bool turnFlag = false;
    int firstX, firstO;
    while(1){
        
        if (turnFlag==false){
            cout << "user1's turn: Enter the location you want to change: ";
            getline(cin >> ws, loc);    
            if(loc == "SAVE FILE.TXT"){
                turnFlag = !turnFlag;
                savingFile(board, boardSize);
            }
            else if(loc == "LOAD FILE.TXT"){
                turnFlag = !turnFlag;
                loadingFile(board);
                printMarkedBoard(board,boardSize);
            }
            else{
                auto col = static_cast<int>(loc[0])-65;
                auto row = static_cast<int>(loc[1])-48;
                try{  // checking whether the area to be marked is markable
                    if(col >= boardSize || row > boardSize || col < 0 || row < 0){     
                        throw (boardSize);
                    }
                    if (board[row-1][col] != emp){
                        throw (sameLocErr);
                    }
                }
                catch(int boardSize){   // throws an error and takes action to get input again
                    cerr << "The location you enter must not exceed the dimensions of a " << boardSize << "x" << boardSize << " board, and must be upper letters. Try again.";
                    turnFlag = !turnFlag;
                }
                catch(string sameLocErr){  // throws an error and takes action to get input again
                    cerr << sameLocErr;
                    turnFlag = !turnFlag;
                }
                if(board[row-1][col] != user2 && turnFlag == false){  // marking is done if conditions are satisfied
                    board[row-1][col] = user1;
                    printMarkedBoard(board, boardSize);
                    firstX = checkRowforFirstX(board, arr, boardSize);
                    if(x_checkVictoryPath(board, arr, boardSize, firstX, 0, 0)){   // checking the win status after each mark
                        cout << "user1 WON THE GAME!\n";
                        break;
                    }  
                }
            }
            turnFlag = !turnFlag; 
            cout << "\n";
        }

        else{
            // computer gameplay prepared in this else block
            srand((unsigned) time(0));  // the first location to be marked is chosen randomly
            auto row = (rand() % boardSize);
            auto col = (rand() % boardSize);

            // the computer controls its field and moves accordingly to make logical markings
            // if the top left is empty, go there, if not, go to the top right, if not... etc.
            if(board[row-1][col] == emp && row-1 >= 0)
                board[row-1][col] = user2;
            else if(board[row-1][col+1] == emp && row-1 >= 0 && col+1 < boardSize)
                board[row-1][col+1] = user2;
            else if(board[row][col+1] == emp && col+1 < boardSize)
                board[row][col+1] = user2;
            else if(board[row+1][col] == emp && row+1 < boardSize)
                board[row+1][col] = user2;
            else if(board[row+1][col-1] == emp && row+1 >= 0 && col-1 >= 0)
                board[row+1][col-1] = user2;
            else if(board[row][col-1] == emp && col-1 >= 0)
                board[row][col-1] = user2;
            else{  // mark randomly if no location is available
                row = (rand() % boardSize);
                col = (rand() % boardSize);
                board[row][col] = user2;
            }

            printMarkedBoard(board, boardSize);
            firstO = checkColforFirstO(board, arr, boardSize);
            if(o_checkVictoryPath(board, arr, boardSize, 0, firstO, 0)){ // checking the win status after each mark
                cout << "user2 WON THE GAME!\n";
                break;
            }
            turnFlag = !turnFlag;
            cout << "\n";
        }
    }
}

// the function of the game mode, which allows it to be played with two players
void markTheLocationfor2userMode(int& boardSize, char board[][M], int arr[][M], string loc){

    string sameLocErr = "You cannot mark the marked point again!";
    bool turnFlag = false;
    int firstX, firstO;
    while(1){
        
        if (turnFlag==false){
            cout << "user1's turn: Enter the location you want to change: ";
            getline(cin >> ws, loc);    
            if(loc == "SAVE FILE.TXT"){
                turnFlag = !turnFlag;
                savingFile(board, boardSize);
            }
            else if(loc == "LOAD FILE.TXT"){
                turnFlag = !turnFlag;
                loadingFile(board);
                printMarkedBoard(board,boardSize);
            }
            else{
                auto col = static_cast<int>(loc[0])-65;
                auto row = static_cast<int>(loc[1])-48;
                try{  // checking whether the area to be marked is markable
                    if(col >= boardSize || row > boardSize || col < 0 || row < 0){
                        throw (boardSize);
                    }
                    if (board[row-1][col] != emp){
                        throw (sameLocErr);
                    }
                }
                catch(int boardSize){  // throws an error and takes action to get input again
                    cerr << "The location you enter must not exceed the dimensions of a " << boardSize << "x" << boardSize << " board, and must be upper letters. Try again.";
                    turnFlag = !turnFlag;
                }
                catch(string sameLocErr){  // throws an error and takes action to get input again
                    cerr << sameLocErr;
                    turnFlag = !turnFlag;
                }
                if(board[row-1][col] != user2 && turnFlag == false){  // marking is done if conditions are satisfied
                    board[row-1][col] = user1;
                    printMarkedBoard(board, boardSize);
                    firstX = checkRowforFirstX(board, arr, boardSize);
                    if(x_checkVictoryPath(board, arr, boardSize, firstX, 0, 0)){  // checking the win status after each mark
                        cout << "user1 WON THE GAME!\n";
                        break;
                    }  
                }
            }
            turnFlag = !turnFlag; 
            cout << "\n";
        }

        else{
            cout << "user2's turn: Enter the location you want to change: ";
            getline(cin >> ws, loc);    
            if(loc == "SAVE FILE.TXT"){
                turnFlag = !turnFlag;
                savingFile(board, boardSize);
            }
            else if(loc == "LOAD FILE.TXT"){
                turnFlag = !turnFlag;
                loadingFile(board);
                printMarkedBoard(board,boardSize);
            }
            else{
                auto col = static_cast<int>(loc[0])-65;
                auto row = static_cast<int>(loc[1])-48;
                try{  // checking whether the area to be marked is markable
                    if(col >= boardSize || row > boardSize || col < 0 || row < 0){
                        throw (boardSize);
                    }
                    if (board[row-1][col] != emp){
                        throw (sameLocErr);
                    }
                }
                catch(int boardSize){  // throws an error and takes action to get input again
                    cerr << "The location you enter must not exceed the dimensions of a " << boardSize << "x" << boardSize << " board, and must be upper letters. Try again.";
                    turnFlag = !turnFlag;
                }
                catch(string sameLocErr){  // throws an error and takes action to get input again
                    cerr << sameLocErr;
                    turnFlag = !turnFlag;
                }
                if(board[row-1][col] != user1 && turnFlag == true){  // marking is done if conditions are satisfied
                    board[row-1][col] = user2;
                    printMarkedBoard(board, boardSize);
                    firstO = checkColforFirstO(board, arr, boardSize);
                    if(o_checkVictoryPath(board, arr, boardSize, 0, firstO, 0)){  // checking the win status after each mark
                        cout << "user2 WON THE GAME!\n";
                        break;
                    }  
                }
            }   
            turnFlag = !turnFlag;
            cout << "\n";
        }    
    }
}

// function that allows the board to be redrawn when the board is marked
void printMarkedBoard(char board[][M], int& boardSize){

    for(int i = 65; i < 65+boardSize; ++i){
        cout << " " << static_cast<char>(i) << " ";
    }

    cout << "\n";

    for(int i = 0; i < boardSize; ++i){
        cout << i+1 << " ";
        cout << string(i,' ');
        for(int j = 0; j < boardSize; ++j){
            cout << board[i][j];
            cout << "  ";
        }
        cout << "  ";
        cout << "\n";
    }
}

// function to find the first x in a row to check the path of the x's
int checkRowforFirstX(char board[][M], int arr[][M], int& boardSize){
	
    int i;
	for(i = 0; i < boardSize; i++){
		if(board[i][0] == user1){
			arr[i][0] = 1;	
			break;
		}
	}
	if(arr[i][0] == 1) 
        return i;
	else 
        return 0;
}

// function to find the first o in a column to check the path of the o's
int checkColforFirstO(char board[][M], int arr[][M], int& boardSize){
	
    int i;
	for(i = 0; i < boardSize; i++){
		if(board[0][i] == user2){
			arr[0][i] = 2;	
			break;
		}
	}
	if(arr[0][i] == 2) 
        return i;
	else 
        return 0;
}

// function that examines the control of the path where the x's join from edge to edge using the backtracking algorithm
int x_checkVictoryPath(char board[][M], int arr[][M], int& boardSize, int row, int col, int flag)
{   
    if(col == boardSize){
		arr[row][col] = 1;							
		return 1;					
	}
	if(board[row][col] == user1){
		arr[row][col] = 1;						
		if(flag != 6 && arr[row][col+1] != 1)			
            if(x_checkVictoryPath(board, arr, boardSize, row, col+1, 1) == 1) 		
                return 1;
		if(flag !=5 && arr[row+1][col] != 1)			
            if(x_checkVictoryPath(board,arr, boardSize, row+1,col, 2)==1) 		
                return 1;
		if(row>=1 && flag!=4 && arr[row-1][col+1] != 1) 	
            if(x_checkVictoryPath(board, arr, boardSize, row-1,col+1, 3)==1) 	
                return 1;
		if(col >= 1 && flag !=3 && arr[row+1][col-1] != 1)	
            if(x_checkVictoryPath(board, arr, boardSize, row+1,col-1, 4)==1) 	
                return 1;
		if(row >=1 && flag != 2 && arr[row-1][col] != 1)		
            if(x_checkVictoryPath(board, arr, boardSize, row-1,col, 5)==1) 		
                return 1;
		if(col >= 1 && flag !=1 && arr[row][col-1] != 1)		
            if(x_checkVictoryPath(board, arr, boardSize, row,col-1 ,6)==1) 		
                return 1; 
		arr[row][col]=0;							
	}
	return 0;
    
}

// function that examines the control of the path where the o's join from edge to edge using the backtracking algorithm
int o_checkVictoryPath(char board[][M], int arr[][M], int& boardSize, int row, int col, int flag)
{   
    if(row == boardSize){
		arr[row][col] = 2;							
		return 1;					
	}
	if(board[row][col] == user2){
		arr[row][col] = 2;						
		if(flag != 6 && arr[row][col+1] != 2)			
            if(o_checkVictoryPath(board, arr, boardSize, row, col+1, 1) == 1)
                return 1;	         
		if(flag !=5 && arr[row+1][col] != 2)			
            if(o_checkVictoryPath(board,arr, boardSize, row+1,col, 2)==1) 		
                return 1;
		if(row>=1 && flag!=4 && arr[row-1][col+1] != 2) 	
            if(o_checkVictoryPath(board, arr, boardSize, row-1,col+1, 3)==1) 	
                return 1;
		if(col >= 1 && flag !=3 && arr[row+1][col-1] != 2)	
            if(o_checkVictoryPath(board, arr, boardSize, row+1,col-1, 4)==1) 	
                return 1;
		if(row >=1 && flag != 2 && arr[row-1][col] != 2)		
            if(o_checkVictoryPath(board, arr, boardSize, row-1,col, 5)==1) 		
                return 1;
		if(col >= 1 && flag !=1 && arr[row][col-1] != 2)		
            if(o_checkVictoryPath(board, arr, boardSize, row,col-1 ,6)==1) 		
                return 1; 
		arr[row][col] = 0;							
	}
	return 0;
    
}

// function to save current game state to file
void savingFile(char board[][M], int& boardSize){
    ofstream outStream;
    outStream.open("file.txt");
    if(outStream.fail()){
        cerr << "File opening failed.\n";
        exit(1);
    }
    outStream << boardSize;
    for(int i = 0; i < boardSize; ++i)
        for(int j = 0; j < boardSize; ++j)
            outStream << board[i][j];
    cout << "Game saved succesfully.\n";
}   

// function to retrieve saved game state from file
void loadingFile(char board[][M]){
    int bSize;
    ifstream inStream;
    inStream.open("file.txt");
    if(inStream.fail()){
        cerr << "File opening failed.\n";
        exit(1);
    }
    inStream >> bSize;
    decltype(bSize) boardSize = bSize;
    for(int i = 0; i < boardSize; ++i)
        for(int j = 0; j < boardSize; ++j)
            inStream >> board[i][j];
    cout << "Game loaded succesfully.\n";
}  