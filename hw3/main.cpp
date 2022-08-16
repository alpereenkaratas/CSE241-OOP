#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;

const int M = 20;

enum CellState{
    user1 = 'x',
    user2 = 'o',
    emp = '.'
};

class Hex
{
private:
    class Cell
    {
    public:
        CellState getEnumCellState(){return cellSt;} // inline function
        inline void setEnumCellState(CellState setState){cellSt = setState;} // Redundant use of inline. But shown in a function for example.
        string getLoc();
        int getColofCell(string locInp);
        int getRowofCell(string locInp);
    private:
        CellState cellSt;
        string loc;
        int posofCell;
        int numofCell;
    };
    int boardSize;
    vector<vector<Cell> > hexCells;
    int arr[M][M]={0};
    int firstX;
    int firstO;
    int gameMode;
    static int markedCellCounter;
    int gameNumber = 0;
    int game1 = 0;
    int game2 = 0;
    int game3 = 0;
    int game4 = 0;
    int game5 = 0;
    int isSavedGame1 = 0; 
    int isSavedGame2 = 0;
    int isSavedGame3 = 0;
    int isSavedGame4 = 0;
    int isSavedGame5 = 0; 
    int isLoadedGame1 = 0;
    int isLoadedGame2 = 0;
    int isLoadedGame3 = 0;
    int isLoadedGame4 = 0;
    int isLoadedGame5 = 0;
    int firstGameMarkedCell = 0;

public:
    Hex(int bSize, char gMode);
    Hex(int bSize);
    Hex();
    int getBoardSize();
    void createBoard();
    void printBoard();
    void play();
    int play(string location);
    void play2users();
    void playGame();
    int checkRowforFirstX();
    int checkColforFirstO();
    int x_checkVictoryPath(int row, int col, int flag);
    int o_checkVictoryPath(int row, int col, int flag);
    string locInput();
    string locInputUser2();
    void gameModeInp();
    int getGameMode();
    int checkValidityforMarking(int i, int j);
    void savingFile();
    void loadingFile();
    static int totalMarkedCells();
    static void setZerotoCellCtr();
    int getTotalMarkedCells();
    void setGameNumber(){gameNumber++;}
    int getGameNumber(){return gameNumber;}
    void setGame1(){game1 = 1;}
    void setGame2(){game2 = 2;}
    void setGame3(){game3 = 3;}
    void setGame4(){game4 = 4;}
    void setGame5(){game5 = 5;}
    void setLoadedGame1(){isLoadedGame1 = 1;}
    void setLoadedGame2(){isLoadedGame2 = 2;}
    void setLoadedGame3(){isLoadedGame3 = 3;}
    void setLoadedGame4(){isLoadedGame4 = 4;}
    void setLoadedGame5(){isLoadedGame5 = 5;}
    int whichGameisSaved();
    int whichGameisLoaded();
    bool isLarger(Hex &other) {
        cout << "first game: " << getTotalMarkedCells() << "\n";
        cout << "second game: " << other.getTotalMarkedCells() << "\n";
        return getTotalMarkedCells() > other.getTotalMarkedCells();
    }

};

Hex::Hex(int bSize, char gMode) : boardSize(6), gameMode('1')
{ /*Body intentionally empty.*/}

Hex::Hex(int bSize) : boardSize(6)
{ /*Body intentionally empty.*/}

Hex::Hex() : boardSize(0), gameMode(0)
{ /*Body intentionally empty.*/}

int Hex::markedCellCounter = 0;

int Hex::totalMarkedCells(){
    return ++markedCellCounter;
}

void Hex::setZerotoCellCtr(){
    markedCellCounter = 0;
}

int Hex::getTotalMarkedCells(){
    return markedCellCounter;
}

string Hex::Cell::getLoc(){
    return loc;
}

int Hex::Cell::getRowofCell(string locInp){           // returns the related row number
    return static_cast<int>(locInp[1])-48-1;
}

int Hex::Cell::getColofCell(string locInp){             // returns the related col number
    return static_cast<int>(locInp[0])-65;
}

int Hex::getBoardSize(){
    return boardSize;
}

void Hex::createBoard(){
    Cell cl;
    for(int i = 0; i < getBoardSize(); ++i){
        vector<Cell> v1;
        for(int j = 0; j < getBoardSize(); j++){
            cl.setEnumCellState(emp);
            v1.push_back(cl);
        }
        hexCells.push_back(v1);
        // v1.clear();
    }
    
}

void Hex::printBoard(){

    for(int i = 65; i < 65+getBoardSize(); ++i){
        cout << " " << static_cast<char>(i) << " ";
    }

    cout << "\n";
    
    for (int i = 0; i < hexCells.size(); i++) {
        cout << i+1 << " ";
        cout << string(i,' ');
        for (int j = 0; j < hexCells[i].size(); j++)
            cout << static_cast<char>(hexCells[i][j].getEnumCellState()) << "  ";
        cout << "\n";
    }
    
}

int Hex::checkColforFirstO(){
	
    int i;
	for(i = 0; i < getBoardSize(); i++){
		if(hexCells[0][i].getEnumCellState() == user2){
			arr[0][i] = 2;	
			break;
		}
	}
	if(arr[0][i] == 2) 
        return i;
	else 
        return 0;
}

int Hex::checkRowforFirstX(){
	
    int i;
	for(i = 0; i < getBoardSize(); i++){
		if(hexCells[i][0].getEnumCellState() == user1){
			arr[i][0] = 1;	
			break;
		}
	}
	if(arr[i][0] == 1) 
        return i;
	else 
        return 0;
}

int Hex::o_checkVictoryPath(int row, int col, int flag){  

    if(row == getBoardSize()){
		arr[row][col] = 2;							
		return 1;					
	}
	if(hexCells[row][col].getEnumCellState() == user2){
		arr[row][col] = 2;						
		if(flag != 6 && arr[row][col+1] != 1)			
            if(o_checkVictoryPath(row, col+1, 1) == 1) 		
                return 1;
		if(flag !=5 && arr[row+1][col] != 1)			
            if(o_checkVictoryPath(row+1, col, 2) == 1) 		
                return 1;
		if(row>=1 && flag!=4 && arr[row-1][col+1] != 1) 	
            if(o_checkVictoryPath(row-1, col+1, 3) == 1) 	
                return 1;
		if(col >= 1 && flag !=3 && arr[row+1][col-1] != 1)	
            if(o_checkVictoryPath(row+1, col-1, 4) == 1) 	
                return 1;
		if(row >=1 && flag != 2 && arr[row-1][col] != 1)		
            if(o_checkVictoryPath(row-1, col, 5) == 1) 		
                return 1;
		if(col >= 1 && flag !=1 && arr[row][col-1] != 1)		
            if(o_checkVictoryPath(row, col-1, 6) == 1) 		
                return 1; 
		arr[row][col] = 0;							
	}
	return 0;  
}

int Hex::x_checkVictoryPath(int row, int col, int flag){  

    if(col == getBoardSize()){
		arr[row][col] = 1;							
		return 1;					
	}
	if(hexCells[row][col].getEnumCellState() == user1){
		arr[row][col] = 1;						
		if(flag != 6 && arr[row][col+1] != 1)			
            if(x_checkVictoryPath(row, col+1, 1) == 1) 		
                return 1;
		if(flag !=5 && arr[row+1][col] != 1)			
            if(x_checkVictoryPath(row+1, col, 2) == 1) 		
                return 1;
		if(row>=1 && flag!=4 && arr[row-1][col+1] != 1) 	
            if(x_checkVictoryPath(row-1, col+1, 3) == 1) 	
                return 1;
		if(col >= 1 && flag !=3 && arr[row+1][col-1] != 1)	
            if(x_checkVictoryPath(row+1, col-1, 4) == 1) 	
                return 1;
		if(row >=1 && flag != 2 && arr[row-1][col] != 1)		
            if(x_checkVictoryPath(row-1, col, 5) == 1) 		
                return 1;
		if(col >= 1 && flag !=1 && arr[row][col-1] != 1)		
            if(x_checkVictoryPath(row, col-1, 6) == 1) 		
                return 1; 
		arr[row][col] = 0;							
	}
	return 0;  
}

int Hex::checkValidityforMarking(int i, int j){

    if(j >= getBoardSize() || i >= getBoardSize() || j < 0 || i < 0){     
        cerr << "The location you enter must not exceed the dimensions of a " << getBoardSize() << "x" << getBoardSize() << " board, and must be upper letters. Try again.\n";
        return 2;
    }
    else if(hexCells[i][j].getEnumCellState() != emp){
        cerr << "You cannot mark the marked point again!\n";
        return 2;
    }
}

void Hex::play2users(){
    string a;
    Cell temp;
    bool turn = false;
    while(true){
        if(turn == false){
            a = locInput();

            if(a == "SAVE FILE.TXT"){
                turn = !turn;
                savingFile();
            }

            else if(a == "LOAD FILE.TXT"){
                turn = !turn;
                loadingFile();
                printBoard();
            }

            else if(a == "MENU")
                break;

            else{
                auto i = temp.getRowofCell(a);
                auto j = temp.getColofCell(a);

                if(checkValidityforMarking(i,j) == 2)
                    turn = !turn;

                else{
                    hexCells[i][j].setEnumCellState(user1);
                    printBoard();
                    cout << "Total number of marked cells: " << totalMarkedCells() << "\n";
                    firstX = checkRowforFirstX();
                    if(x_checkVictoryPath(firstX, 0, 0)==1){  // checking the win status after each mark
                        printBoard();
                        cout << "user1 WON THE GAME!\n";
                        break;
                    }
                }
            }
            turn = !turn;
            cout << "\n";
        }
        else{
            a = locInputUser2();
            auto i = temp.getRowofCell(a);
            auto j = temp.getColofCell(a);

            if(a == "SAVE FILE.TXT"){
                turn = !turn;
                savingFile();
            }

            else if(a == "LOAD FILE.TXT"){
                turn = !turn;
                loadingFile();
                printBoard();
            }

            else if(a == "MENU")
                break;

            else{
                if(checkValidityforMarking(i,j) == 2)
                    turn = !turn;

                else{
                    hexCells[i][j].setEnumCellState(user2);
                    printBoard();
                    cout << "Total number of marked cells: " << totalMarkedCells() << "\n";
                    firstO = checkColforFirstO();
                    if(o_checkVictoryPath(0, firstO, 0)==1){  // checking the win status after each mark
                        printBoard();
                        cout << "user2 WON THE GAME!\n";
                        break;
                    }
                }
            }
            turn = !turn;
            cout << "\n";
        }
    }
}

// play function for user1;
int Hex::play(string location){

    Cell temp;
    int i = temp.getRowofCell(location);
    int j = temp.getColofCell(location);

    if(location == "SAVE FILE.TXT"){
        savingFile();
        return 2;
    }

    else if(location == "LOAD FILE.TXT"){
        loadingFile();
        printBoard();
        return 2;
    }

    else if(location == "MENU")
        return 3;

    else{
        if(checkValidityforMarking(i,j) == 2)
            return 2;
        
        hexCells[i][j].setEnumCellState(user1);
        cout << "Total number of marked cells: " << totalMarkedCells() << "\n";
        firstX = checkRowforFirstX();
        if(x_checkVictoryPath(firstX, 0, 0)==1){  // checking the win status after each mark
            printBoard();
            cout << "user1 WON THE GAME!\n";
            return 1;
        }
    }
    return 0;  
}

// play function for computer
void Hex::play(){
    while(true){
        srand((unsigned) time(0));  // the first location to be marked is chosen randomly
        int i = (rand() % getBoardSize());
        int j = (rand() % getBoardSize());
        // cout << "SAAA\n";
        // cout << "i: " << i << " j: " << j << "\n";
        // the computer controls its field and moves accordingly to make logical markings
        // if the top left is empty, go there, if not, go to the top right, if not... etc.
        // if(hexCells[i+1][j].getEnumCellState() == emp)
        //     hexCells[i+1][j].setEnumCellState(user2);
        // else if(hexCells[i+1][j-1].getEnumCellState() == emp && j-1 >= 0 && j-1 < getBoardSize())
        //     hexCells[i+1][j-1].setEnumCellState(user2);
        // else if(hexCells[i][j+1].getEnumCellState() == emp && j+1 < getBoardSize() && j > 0)
        //     hexCells[i][j+1].setEnumCellState(user2);
        // else if(hexCells[i][j-1].getEnumCellState() == emp && j-1 < getBoardSize() && j-1 > getBoardSize())
        //     hexCells[i][j-1].setEnumCellState(user2);
        // else if(hexCells[i-1][j+1].getEnumCellState() == emp && j+1 < getBoardSize() && i-1 >= 0)
        //     hexCells[i-1][j+1].setEnumCellState(user2);   
        // else if(hexCells[i-1][j].getEnumCellState() == emp && i-1 >= 0)
        //     hexCells[i-1][j].setEnumCellState(user2);
        // else{  // mark randomly if no location is available
        //     srand((unsigned) time(0));  // the first location to be marked is chosen randomly
        //     auto i = (rand() % getBoardSize());
        //     auto j = (rand() % getBoardSize());
        //     hexCells[i][j].setEnumCellState(user2);
        // }
        // if (turnFlag == true)
        if (hexCells[i][j].getEnumCellState() == emp){
            hexCells[i][j].setEnumCellState(user2);
            firstO = checkColforFirstO();
            if(o_checkVictoryPath(0, firstO, 0)==1){  // checking the win status after each mark
                printBoard();
                cout << "computer WON THE GAME!\n";
                break;
            }
            break;            
        }
    }

}

string Hex::locInput(){
    string locInp;
    cout << "user1's turn: Enter the location you want to change: ";
    getline(cin >> ws, locInp);
    return locInp;
}

string Hex::locInputUser2(){
    string locInp;
    cout << "user2's turn: Enter the location you want to change: ";
    getline(cin >> ws, locInp);
    return locInp;
}

void Hex::gameModeInp(){
    cout << "enter game mode:\n1) Two players\n2) One player against computer\n";
    cin >> gameMode;
}

int Hex::getGameMode(){
    return gameMode;
}

void Hex::playGame(){
    int x,y,z=0;
    while(true){
        if(isSavedGame1 != 1 && isSavedGame2 != 2 && isSavedGame3 != 3 && isSavedGame4 != 4 && isSavedGame5 != 5){
            cout << "Enter the board size: 6x6,7x7,8x8,9x9,10x10,11x11 or 12x12. (Enter it by one dimension. (For ex. 6,8 or 12)) --> ";
            cin >> boardSize;
        }
        if(boardSize >= 6 || boardSize <= 12){
            if(isSavedGame1 != 1 && isSavedGame2 != 2 && isSavedGame3 != 3 && isSavedGame4 != 4 && isSavedGame5 != 5){
                createBoard();
                printBoard();
            }
            while(true){
                if(isSavedGame1 != 1 && isSavedGame2 != 2 && isSavedGame3 != 3 && isSavedGame4 != 4 && isSavedGame5 != 5){   
                    gameModeInp();
                    y = getGameMode();
                }
                else
                    y = gameMode;
                if (y == 1){
                    play2users();
                    z++;
                    break;
                }
                else if (y == 2){
                    while(true){
                        x = play(locInput());
                        if(x==1)
                            break;
                        else if(x==2){
                            string s = locInput();
                            if (play(s) == 0)
                                play();
                            else if (play(s) == 3){
                                z++;
                                break;
                            }
                        }
                        else if(x==0)
                            play();
                        else if(x==3){
                            z++;
                            break;
                        }
                        printBoard();
                        cout << "Total number of marked cells: " << totalMarkedCells() << "\n";
                        cout << "\n";
                    }
                }
                else
                    cerr << "Invalid game mode. Choose again.\n\n";
                if (z!=0)
                    break;
            }
        }
        else
            cerr << "Invalid board size. Try again.\n";
        if (z!=0)
            break;
    }
}

int Hex::whichGameisSaved(){
    if(game1 == 1){
        return 1;
    }
    else if(game2 == 2){
        return 2;
    }
    else if(game3 == 3){
        return 3;
    }
    else if(game4 == 4){
        return 4;
    }
    else if(game5 == 5){
        return 5;
    }
}

// function to save current game state to file
void Hex::savingFile(){
    int saved = whichGameisSaved();
    ofstream outStream;
    if(saved == 1){
        isSavedGame1 = saved;
        outStream.open("file1.txt");
    }
    else if(saved == 2){
        isSavedGame2 = saved;
        outStream.open("file2.txt");
    }
    else if(saved == 3){
        isSavedGame3 = saved;
        outStream.open("file3.txt");
    }
    else if(saved == 4){
        isSavedGame4 = saved;
        outStream.open("file4.txt");
    }
    else if(saved == 5){
        isSavedGame5 = saved;
        outStream.open("file5.txt");
    }
    if(outStream.fail()){
        cerr << "File opening failed.\n";
        exit(1);
    }
    outStream << getBoardSize() << "\n";
    outStream << getTotalMarkedCells() << "\n";
    outStream << getGameMode() << "\n";
    for(int i = 0; i < getBoardSize(); ++i)
        for(int j = 0; j < getBoardSize(); ++j)
            outStream << static_cast<char>(hexCells[i][j].getEnumCellState());
    cout << "Game saved succesfully.\n";
    outStream.close();
}   

int Hex::whichGameisLoaded(){

    if(isLoadedGame1 == 1){
        return 1;
    }
    else if(isLoadedGame2 == 2){
        return 2;
    }
    else if(isLoadedGame3 == 3){
        return 3;
    }
    else if(isLoadedGame4 == 4){
        return 4;
    }
    else if(isLoadedGame5 == 5){
        return 5;
    }
}

// function to retrieve saved game state from file
void Hex::loadingFile(){
    int loadedBoardSize;
    int loadedMarkedCell;
    int loadedGameMode;
    char c;
    int loaded = whichGameisLoaded();
    cout << "the game loaded is: " << loaded;
    cout << "\n";

    ifstream inStream;
    if(loaded == 1){
        inStream.open("file1.txt");
    }
    else if(loaded == 2){
        inStream.open("file2.txt");
    }
    else if(loaded == 3){
        inStream.open("file3.txt");
    }
    else if(loaded == 4){
        inStream.open("file4.txt");
    }
    else if(loaded == 5){
        inStream.open("file5.txt");
    }
    else{
        cerr << "there is not such a game\n";
    }
    if(inStream.fail()){
        cerr << "File opening failed.\n";
        exit(1);
    }
    inStream >> loadedBoardSize >> loadedMarkedCell >> loadedGameMode;
    cout << "bsize:" << loadedBoardSize << endl;
    cout << "loadmarkedcells:" << loadedMarkedCell << endl;
    cout << "gamemode: " << loadedGameMode << endl;
    
    decltype(loadedBoardSize) size = loadedBoardSize;
    markedCellCounter = loadedMarkedCell;
    gameMode = loadedGameMode;

    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            inStream >> c;
            if(c == '.')
                hexCells[i][j].setEnumCellState(emp);
            else if(c == 'x')
                hexCells[i][j].setEnumCellState(user1);
            else
                hexCells[i][j].setEnumCellState(user2);
        }   
    }
    cout << "Game loaded succesfully.\n";
    inStream.close();
}  

int main(){
    int menu;
    int game;
    int gameCompare1, gameCompare2;
    Hex h1,h2,h3,h4,h5;

    while(true){
        cout << "1) New game\n2) Load game\n3)Compare games marked cells\n";
        cin >> menu;
        if (menu == 1){
            if(h1.getGameNumber() == 0){
                cout << "GAME 1\n";
                h1.setGame1();
                h1.setGameNumber();
                h1.playGame();
            }
            else if(h2.getGameNumber() == 0){
                cout << "GAME 2\n";
                h2.setZerotoCellCtr();
                h2.setGame2();
                h2.setGameNumber();
                h2.playGame();
            }
            else if(h3.getGameNumber() == 0){
                cout << "GAME 3\n";
                h3.setZerotoCellCtr();
                h3.setGame3();
                h3.setGameNumber();
                h3.playGame();
            }
            else if(h4.getGameNumber() == 0){
                cout << "GAME 4\n";
                h4.setZerotoCellCtr();
                h4.setGame4();
                h4.setGameNumber();
                h4.playGame();
            }
            else if(h5.getGameNumber() == 0){
                cout << "GAME 5\n";
                h5.setZerotoCellCtr();
                h5.setGame5();
                h5.setGameNumber();
                h5.playGame();
            }
        }
        else if(menu == 2){
            cout << "Select the game you want to continue: 1/2/3/4/5\n";
            cin >> game;
            if(game == 1){
                h1.setLoadedGame1();
                h1.loadingFile();
                h1.printBoard();
                h1.playGame();
            }
            if(game == 2){
                h2.setLoadedGame2();
                h2.loadingFile();
                h2.printBoard();
                h2.playGame();
            }
            if(game == 3){
                h3.setLoadedGame3();
                h3.loadingFile();
                h3.printBoard();
                h3.playGame();
            }
            if(game == 4){
                h4.setLoadedGame4();
                h4.loadingFile();
                h4.printBoard();
                h4.playGame();
            } 
            if(game == 5){
                h5.setLoadedGame5();
                h5.loadingFile();
                h5.printBoard();
                h5.playGame();
            }   
        }
        else if(menu == 3){
            Hex temp1,temp2;
            cout << "Select first game number: ";
            cin >> gameCompare1;
            if(gameCompare1 == 1)
                temp1 = h1;
            else if(gameCompare1 == 2)
                temp1 = h2;
            else if(gameCompare1 == 3)
                temp1 = h3;
            else if(gameCompare1 == 4)
                temp1 = h4;
            else if(gameCompare1 == 5)
                temp1 = h5;
            cout << "Select second game number: ";
            cin >> gameCompare2;
            if(gameCompare2 == 1)
                temp2 = h1;
            else if(gameCompare2 == 2)
                temp2 = h2;
            else if(gameCompare2 == 3)
                temp2 = h3;
            else if(gameCompare2 == 4)
                temp2 = h4;
            else if(gameCompare2 == 5)
                temp2 = h5;
            
            if(temp1.isLarger(temp2)){
                cout << "First game has more amount of marked cells.\n";
            }
        }
    }
    cout << "returned to menu";
}