#include<bits/stdc++.h>
#include <windows.h>
#define UNASSIGNED 0
#define N 9
COORD coord= {0,0};
using namespace std;


class Sudoku {
    private:
        int grid[9][9];
        int solnGrid[9][9];
        int guessNum[9];
        int gridPos[81];
        int difficultyLevel;

    public:
        Sudoku ();
        void createSeed();
        void printGrid();
        bool solveGrid();
        void countSoln(int &number);
        void genPuzzle();
        void printSVG(string);
        void calculateDifficulty();
        int  branchDifficultyScore();
};

int game[9][9] = {0};
int problem[9][9] = {0};
int blank = 0;

void choice();
void chooseLevel();
void intro();
void Rules();
void StartGame();
void Game(int attempt);
void level(char ch);
void printGrid2(int grid[N][N]);
void delay(int t);
void gotoxy(int, int);
void SetColor(int ForgC);
int genRandNum(int maxLimit){
    return rand()%maxLimit;
}

void Sudoku::createSeed(){
    this->solveGrid();

    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            this->solnGrid[i][j] = this->grid[i][j];
        }
    }
}


Sudoku::Sudoku(){

    this->difficultyLevel = 0;

    for(int i = 0 ; i < 81 ; i++){
        this->gridPos[i] = i;
    }

    random_shuffle(this->gridPos, (this->gridPos) + 81, genRandNum);

    for(int i = 0 ;i < 9 ; i++){
        this->guessNum[i]=i+1;
    }

    random_shuffle(this->guessNum, (this->guessNum) + 9, genRandNum);

    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9; j++){
            this->grid[i][j]=0;
        }
    }

}


void Sudoku::printGrid(){
    /*
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            if(grid[i][j] == 0)
                cout<<".";
            else
                cout<<grid[i][j];

            cout<<"|";
        }
        cout<<endl;
    }
    */
    for(int i = 0 ; i < 9 ; i++){

        for(int j = 0 ; j < 9 ; j++){

            game[i][j] = grid[i][j];

            if(grid[i][j] == 0){

                blank++;

            }
        }
    }

    for(int i = 0 ; i < 9 ; i++){

        for(int j = 0 ; j < 9 ; j++){

            problem[i][j] = grid[i][j];

        }
    }

    //cout<<"\nDifficulty of current sudoku(0 being easiest): "<<this->difficultyLevel;
    //cout<<endl;
}


bool FindUnassignedLocation(int grid[9][9], int &row, int &col){

    for (row = 0; row < 9; row++){

        for (col = 0; col < 9; col++){

            if (grid[row][col] == UNASSIGNED){
                return true;
            }
        }
    }

    return false;
}

bool UsedInRow(int grid[9][9], int row, int num){

    for (int col = 0; col < 9; col++){

        if (grid[row][col] == num){

            return true;

        }
    }

    return false;
}

bool UsedInCol(int grid[9][9], int col, int num){
    for(int row = 0; row < 9; row++){

        if (grid[row][col] == num){
            return true;
        }

    }

    return false;
}

bool UsedInBox(int grid[9][9], int boxStartRow, int boxStartCol, int num){

    for (int row = 0; row < 3; row++){

        for (int col = 0; col < 3; col++){

            if (grid[row+boxStartRow][col+boxStartCol] == num){

                return true;

            }

        }

    }

    return false;
}

bool isSafe(int grid[9][9], int row, int col, int num){

    return !UsedInRow(grid, row, num) && !UsedInCol(grid, col, num) && !UsedInBox(grid, row - row%3 , col - col%3, num);

}


bool Sudoku::solveGrid(){

    int row, col;

    if (!FindUnassignedLocation(this->grid, row, col)){

       return true;

    }

    for (int num = 0; num < 9; num++){

        if (isSafe(this->grid, row, col, this->guessNum[num])){

            this->grid[row][col] = this->guessNum[num];

            if (solveGrid()){

                return true;

            }

            this->grid[row][col] = UNASSIGNED;

        }

    }

    return false;

}


void Sudoku::countSoln(int &number){
    int row, col;

    if(!FindUnassignedLocation(this->grid, row, col)){
        number++;
        return ;
    }


    for(int i = 0; i < 9 && number < 2; i++){
        if( isSafe(this->grid, row, col, this->guessNum[i]) ){
            this->grid[row][col] = this->guessNum[i];
            countSoln(number);
        }

        this->grid[row][col] = UNASSIGNED;
    }

}

bool FindUnassignedLocation(int grid[N][N], int &row, int &col);

bool isSafe(int grid[N][N], int row, int col, int num);

bool SolveSudoku(int grid[N][N]){
    int row, col;

    if (!FindUnassignedLocation(grid, row, col)){
        return true;
	}


	for (int num = 1; num <= 9; num++){

		if (isSafe(grid, row, col, num)){

			grid[row][col] = num;

			if (SolveSudoku(grid)){

				return true;

			}

			grid[row][col] = UNASSIGNED;

		}
	}

	return false;

}


void Sudoku::genPuzzle(){

    for(int i = 0 ; i < 81 ; i++){

        int x = ( this -> gridPos[i] ) / 9;

        int y = ( this -> gridPos[i] ) % 9;

        int temp = this -> grid[x][y];

        this -> grid[x][y] = UNASSIGNED;

        int check=0;

        countSoln(check);

        if(check != 1){

            this -> grid[x][y] = temp;

        }
    }
}

/*

// START: Printing into SVG file
void Sudoku::printSVG(string path="")
{
  string fileName = path + "svgHead.txt";
  ifstream file1(fileName.c_str());
  stringstream svgHead;
  svgHead << file1.rdbuf();

  ofstream outFile("puzzle.svg");
  outFile << svgHead.rdbuf();

  for(int i=0;i<9;i++)
  {
    for(int j=0;j<9;j++)
    {
      if(this->grid[i][j]!=0)
      {
        int x = 50*j + 16;
        int y = 50*i + 35;

        stringstream text;
        text<<"<text x=\""<<x<<"\" y=\""<<y<<"\" style=\"font-weight:bold\" font-size=\"30px\">"<<this->grid[i][j]<<"</text>\n";

        outFile << text.rdbuf();
      }
    }
  }

    outFile << "<text x=\"50\" y=\"500\" style=\"font-weight:bold\" font-size=\"15px\">Difficulty Level (0 being easiest): "                  <<this->difficultyLevel<<"</text>\n";
    outFile << "</svg>";

}
// END: Printing into SVG file
*/

// START: Calculate branch difficulty score
int Sudoku::branchDifficultyScore(){

    int emptyPositions = -1;

    int tempGrid[9][9];

    int sum=0;

    for(int i = 0 ; i < 9 ; i++){

        for(int j = 0 ; j < 9 ; j++){

            tempGrid[i][j] = this->grid[i][j];

        }

    }

    while(emptyPositions!=0){
        vector<vector<int> > empty;

        for(int i = 0 ; i < 81 ; i++){
            if(tempGrid[(int)(i / 9)][(int)(i % 9)] == 0){
                vector<int> temp;
                temp.push_back(i);

                for(int num=1;num<=9;num++){
                    if(isSafe(tempGrid,i/9,i%9,num)){
                        temp.push_back(num);
                    }
                }

                empty.push_back(temp);
            }
        }

        if(empty.size() == 0){
            cout << "Hello : " << sum << endl;
            return sum;
        }

        int minIndex = 0;

        int check = empty.size();

        for(int i = 0 ; i < check ; i++){
            if(empty[i].size() < empty[minIndex].size())
                minIndex = i;
        }

        int branchFactor=empty[minIndex].size();

        int rowIndex = empty[minIndex][0]/9;

        int colIndex = empty[minIndex][0]%9;

        tempGrid[rowIndex][colIndex] = this->solnGrid[rowIndex][colIndex];

        sum = sum + ((branchFactor-2) * (branchFactor-2)) ;

        emptyPositions = empty.size() - 1;
    }

    return sum;
}

void Sudoku::calculateDifficulty(){
    int B = branchDifficultyScore();

    int emptyCells = 0;

    for(int i = 0; i < 9 ; i++){
        for(int j = 0; j < 9; j++){
            if(this->grid[i][j] == 0){
                emptyCells++;
            }
        }
    }

    this->difficultyLevel = B*100 + emptyCells;
}
void SetColor(int ForgC)
{
     WORD wColor;
     //This handle is needed to get the current background attribute

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     //csbi is used for wAttributes word

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          //To mask out all but the background attribute, and to add the color
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void printGrid2(int grid[9][9]){
    for(int i = 0 ; i < 9 ; i++){
        for(int j = 0 ; j < 9 ; j++){
            if(grid[i][j] == 0)
                cout<<".";
            else
                cout<<grid[i][j];

            cout<<"|";
        }
        cout<<endl;
    }
}

void level(char choice){
    StartGame();
    if(choice == 'E' || choice == 'e'){
        Game(7);
    }else if(choice == 'M' || choice == 'm'){
        Game(4);
    }else if(choice == 'H' || choice == 'h'){
        Game(2);
    }else{
        Game(7);
    }
}

void Game(int attempt){
    SolveSudoku(game);
    printGrid2(problem);
    int row, col, value;
    char ch;
    //string str;
    //int t = 4;
    while(blank && attempt){
        cout << "\nEnter row, col, and value in x,y,z format : ";
        //cin >> str;
        cin >> row; cin >> ch; cin >> col; cin >> ch; cin >> value;

        if(problem[row - 1][col - 1] != 0){
            cout << "\nAlready filled.\n";
        }
        else if(game[row - 1][col - 1] == value){
            problem[row - 1][col - 1] = value;
            system("CLS");
            printGrid2(problem);
        }else{
            cout << "\nWrong!!!!\tTry again.\n";
            blank--;
            cout << "Attempt left : " << --attempt;
        }
    }

    cout<<"\nSolution : \n";
    printGrid2(game);
}

void StartGame(){

    srand(time(NULL));


    Sudoku *puzzle = new Sudoku();


    puzzle->createSeed();


    puzzle->genPuzzle();

    puzzle->calculateDifficulty();

    puzzle->printGrid();


}
void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}


void Rules(){
    delay(1);
    gotoxy(5,5);
        SetColor(150);
      cout<<"Games would be divided into three parts"<<endl;
      delay(1);
      gotoxy(7,6);
      SetColor(120);
      cout<<"\t*Easy Level"<<endl;
      delay(1);
      gotoxy(7,7);
      SetColor(130);
      cout<<"\t*Medium Level"<<endl;
      delay(1);
      gotoxy(7,8);
      SetColor(140);
      cout<<"\t*Hard Level"<<endl;
      delay(1);
      gotoxy(10,10);
      SetColor(150);
      cout<<":Easy level will have 7 life/chances for the wrong attempt"<<endl;
      delay(1);
      gotoxy(11,11);
      SetColor(155);
      cout<<":Medium level will have 4 life/chances for the wrong attempt"<<endl;
      delay(1);
      gotoxy(12,12);
      SetColor(162);
      cout<<":Hard Level will have 2 life/chances for the wrong attempt"<<endl;
      delay(1);
      gotoxy(13,13);
      SetColor(145);
      cout<<":After exhausting all the life game will be ended"<<endl;
      delay(1);
      gotoxy(14,14);
      SetColor(100);
      choice();
}
void gotoxy(int x, int y)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	_COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hConsole, pos);
}


void intro(){
    SetColor(149);
    cout<<"\n\t\t%%%%%%%%%       ##       ##  %%%%%%%%%%%  ****     %%%  %%%%    ##       ## ";
    cout<<"\n\t\t%%              ##       ##    %%     %%  ****     %%%  %%%     ##       ##   ";
    cout<<"\n\t\t%%%%%%%%%%      ##       ##    %%     %%  ****     %%% %%       ##       ##         ";
    cout<<"\n\t\t        %%%     ##       ##    %%     %%  ****     %%%   %%%    ##       ##      ";
    cout<<"\n\t\t%%%%%%%%%%%     ###########  %%%%%%%%%%%  ****     %%%   %%%%   ########### ";
    cout<<endl;
    delay(2);
    gotoxy(20,10);
    SetColor(145);
    cout<<"ALGORITHM LAB PROJECT";
    cout<<endl;
    delay(2);
    gotoxy(30,12);
    SetColor(130);
    cout<<"::Enter N/n to play the game and Q/q to quit : ";
    char ch;
    cin>>ch;

    if(ch == 'n' || ch == 'N'){
        system("CLS");
        Rules();
    }
    else if(ch == 'Q' || ch == 'q'){
        _Exit(10);
    }
}

void chooseLevel(){
    char choice;
    label :
    system("cls");
    SetColor(155);
    cout << "Choose the Level \n *E for easy \n *M for medium \n *H for hard  \n\nChoice : ";
    delay(2);
    cin >> choice;
SetColor(136);
    if(choice != 'E' && choice != 'e' && choice != 'M' && choice != 'm' && choice != 'H' && choice != 'h'){
        system("cls");
        cout << "\nWrong Choice. Enter Again : ";
        goto label;
    }
    system("cls");
    level(choice);
}

void choice(){
    gotoxy(15,14);
    cout<<"\n\tEnter N/n to continue the game, B/b to go back and Q/q to quit : ";
    char ch1;
    cin>>ch1;

    if(ch1 == 'n' || ch1 == 'N'){
        system("cls");
        chooseLevel();
    }else if(ch1 == 'b' || ch1 == 'B'){
        system("cls");
        intro();
    }else if(ch1 == 'q' || ch1 == 'Q'){
        system("cls");
        _Exit(10);
    }
}

int main(int argc, char const *argv[]){

    intro();

    return 0;
}
