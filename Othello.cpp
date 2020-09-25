using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include  <algorithm>

/*
Implementation of the Othello game with human vs computer game play.
The user chooses whether they want to play black or white but the rule is black always plays first.
The rule of the game is that the opponents piece has to be in between your piece and your placed piece.
Press q to quit and see result or play until the end.
*/


//CONSTANTS - row size and column size
const int RSIZE = 8;
const int CSIZE = 8;

//Function prototypes
string calculateWin(char board[RSIZE][CSIZE], bool showResult);
void displayBoard(char board[][CSIZE]);
bool getMove(char board[][CSIZE], char user);
bool getMoveC(char board[][CSIZE], char user);
bool checkMove(char board[][CSIZE],char user, int r, int c);
bool checkLR(char board[][CSIZE],int r,int c, char user);
bool checkRL(char board[][CSIZE],int r,int c, char user);
bool checkUD(char board[][CSIZE],int r,int c, char user);
bool checkDU(char board[][CSIZE],int r,int c, char user);
bool checkDIAGL(char board[][CSIZE],int r,int c, char user);
bool checkDIAGLback(char board[][CSIZE],int r,int c, char user);
bool checkDIAGR(char board[][CSIZE],int r,int c, char user);
bool checkDIAGRback(char board[][CSIZE],int r,int c, char user);
vector<int> getValidMoves(char board[][CSIZE] , char user);


//Displays the board
void displayBoard(char board[][CSIZE]){

//print column title
cout << "    a   b   c   d   e   f   g   h" << endl;

for(int r = 0 ; r < RSIZE ; r++){

    //print row title
     cout << r+1 << " | " ;

   for(int c = 0 ; c < CSIZE ; c++){

    cout << board[r][c] << " | " ;

}
   cout << endl;
   cout << "  ---------------------------------" << endl;
}

}

//Counts the number of w and b on the board and the score gets printed every turn
//If bool showResult is true then calculateWin function returns the winner
string calculateWin(char board[RSIZE][CSIZE], bool showResult){

//originally 0 points for each
int w = 0;
int b = 0;

for(int r = 0 ; r < RSIZE ; r++){

   for(int c = 0 ; c < CSIZE ; c++){

        //if the spot contains a w or b increment the corresponding variable
        if(board[r][c] == 'w'){ w++;}
        if(board[r][c] == 'b'){ b++;}
}
}

//display the score
cout << "w : " << w << " b: " << b << endl;

//display the winner if passed in showResult boolean is true
if(showResult){
if(w > b){ return "white wins" ; }
else if(b > w){return "black wins" ; }
else{ return "draw"; }
}

return "";
}

//****************************USED BY OUTFLANK FUNCTION: PERFORM OUTFLANK**************************************************************************

//Outflank from right to left
bool swapRL(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find value to swap until
int x=c-1;
for(x ; x >= 0 ; x--){

if(board[r][x] == opp){
    //If the next piece is the enemy then keep changing x
    continue;
}else{
     //else break beause you have reached a value that is not the element
    break;
}
}

// if the value you have stopped at is yourself then perform swapping
if(board[r][x] == user){

    board[r][c] = user;

for(int i = 0 ; i < c-x; i++){

    board[r][x+i] = user;
}
return true;
}else{
    //the value you have stopped at is not yourself
return false;}
}

//Outflank from left ro right
bool swapLR(char board[][CSIZE] ,  int r, int c, char user){


//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find value to swap until
int xr = c + 1;
for(xr ; xr <= 7 ; xr++){

if(board[r][xr] == opp){
    //If the next piece is the enemy then keep changing x
    continue;
}else{
    //else break beause you have reached a value that is not the element
    break;
}
}

// if the value you have stopped at is yourself then perform swapping
if(board[r][xr] == user){ board[r][c] = user;
for(int i = 0 ; i < xr-c; i++){

    board[r][c+i] = user;

}

return true;
}else{
//the value you have stopped at is not yourself
return false;}

}

//Outflank from down to up
bool swapDU(char board[][CSIZE], int r, int c, char user){


//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find value to swap until
int yr = r - 1 ;
for(yr ; yr >= 0 ; yr--){

    if(board[yr][c] == opp){
        //If the next piece is the enemy then keep changing x
        continue;
    }else{
         //else break beause you have reached a value that is not the element
        break;
    }

}

// if the value you have stopped at is yourself then perform swapping
if(board[yr][c] == user){
    board[r][c] = user;
for(int i = 0 ; i < r-yr ; i++){
    board[r-i][c] = user;
}

return true;
}else{
 //the value you have stopped at is not yourself
return false;}
}

//Outflank from up to down
bool swapUD(char board[][CSIZE], int r, int c, char user){


//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find value to swap until
int yr = r + 1 ;
for(yr ; yr <=7  ; yr++){

    if(board[yr][c] == opp){
        //If the next piece is the enemy then keep changing x
        continue;
    }else{
         //else break beause you have reached a value that is not the element
         break;
    }

}

// if the value you have stopped at is yourself then perform swapping
if(board[yr][c] == user){
    board[r][c] = user;
for(int i = 0 ; i < yr-r ; i++){
    board[r+i][c] = user;
}

return true;
}else{
 //the value you have stopped at is not yourself
return false;}
}

//Outflank left diagonal
bool swapDIAGL(char board[][CSIZE],int r,int c, char user){


//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find values to swap until
int x=c+1;
int y=r+1;
for(x , y ; x <= 7 && y <= 7 ; x++, y++){

if(board[y][x] == opp){
    //If the next piece is the enemy then keep changing x
    continue;
}else{
     //else break beause you have reached a value that is not the element
    break;
}
}

// if the value you have stopped at is yourself then perform swapping
if(board[y][x] == user){ board[r][c] = user;
for(int i = 0 ; i < x-c; i++){

    board[r+i][c+i] = user;
}

return true;
}else{
 //the value you have stopped at is not yourself
return false;}
}

//Outflank left diagonaal back
bool swapDIAGLback(char board[][CSIZE],int r,int c, char user){


//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Find values to swap until
int x=c-1;
int y=r-1;
for(x , y ; x >=0 && y >= 0 ; x--, y--){

if(board[y][x] == opp){
   //If the next piece is the enemy then keep changing x
    continue;
}else{
     //else break beause you have reached a value that is not the element
    break;
}
}

// if the value you have stopped at is yourself then perform swapping
if(board[y][x] == user){ board[r][c] = user;
for(int i = 0 ; i < c-x ; i++){

    board[r-i][c-i] = user;
}

return true;
}else{
 //the value you have stopped at is not yourself
return false;}
}

//Outflank right diagonal
bool swapDIAGR(char board[][CSIZE],int r,int c, char user){


//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Find values to swap until
int y = r-1;
int x = c+1;

for(x , y ; x <= 7 && y >=0 ; x++, y--){


if(board[y][x] == opp){
    //If the next piece is the enemy then keep changing x
    continue;
}else{
     //else break beause you have reached a value that is not the element
    break;
}
}

// if the value you have stopped at is yourself then perform swapping
if(board[y][x] == user){ board[r][c] = user;
for(int i = 0 ; i < x-c ; i++){

    board[r-i][c+i] = user;

}

return true;
}else{
 //the value you have stopped at is not yourself
return false;}
}

//Outflank right diagonal back
bool swapDIAGRback(char board[][CSIZE],int r,int c, char user){


//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Find values to swap until
int y = r+1;
int x = c-1;

for(x , y ; y <= 7 && x >=0 ; x--, y++){
if(board[y][x] == opp){
    //If the next piece is the enemy then keep changing x
    continue;
}else{
     //else break beause you have reached a value that is not the element
    break;
}
}

// if the value you have stopped at is yourself then perform swapping
if(board[y][x] == user){
    board[r][c] = user;
for(int i = 0 ; i < y-r ; i++){
    board[r+i][c-i] = user;
}
return true;
}else{
 //the value you have stopped at is not yourself
return false;}
}

//outFlank is when we are ready to swap the pieces.
void outFlank(char board[][CSIZE], char user, int r, int c){

//Check and update who is the player and who is the opponent
    char opp = ' ';
    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//swap on the left
if(board[r][c-1] == opp){
    swapRL(board,r,c,user);
}

//swap on the right
if(board[r][c+1] == opp){
    swapLR(board, r, c, user);
}

//swap above
if(board[r-1][c] == opp){
    swapDU(board, r, c, user);
}

//swap below
if(board[r+1][c] == opp){
    swapUD(board, r, c, user);
}

//swap left diagonal
if(board[r+1][c+1] == opp){
    swapDIAGL(board, r, c, user);
}

//swap left diagonal back
if(board[r-1][c-1] == opp){
    swapDIAGLback(board, r, c, user);
}

//swap right diagonal
if(board[r-1][c+1] == opp){
    swapDIAGR(board, r, c, user);
}

//swap right diagonal back
if(board[r+1][c-1] == opp){
    swapDIAGRback(board, r, c, user);
}

return;
}


//******************************DONE PERFORMING OUTFLANK********************************************************************************************

//*******************************USED BY CHECKMOVE FUNCTION: CHECK IF LOCATION IS VALID*********************************************************

//CHECKING RIGHT TO LEFT
bool checkRL(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int x=c-1;
for(x ; x >= 0 ; x--){

if(board[r][x] == opp){
    //Enemy
    continue;
}else{
    //Reached the player/end
    break;
}
}

//Check if the last element is the player
if(board[r][x] == user){
return true;
}else{
return false;}
}

//CHECKING LEFT TO RIGHT
bool checkLR(char board[][CSIZE] ,  int r, int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int xr = c + 1;
for(xr ; xr <= 7 ; xr++){

if(board[r][xr] == opp){
    //Enemy
    continue;
}else{
    //Player/end
    break;
}
}

//Check if the last element is the player
if(board[r][xr] == user){
return true;
}else{
return false;}

}

//CHECKING DOWN TO UP
bool checkDU(char board[][CSIZE], int r, int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int yr = r - 1 ;
for(yr ; yr >= 0 ; yr--){

    if(board[yr][c] == opp){
        //Enemy
        continue;
    }else{
        //Player/end
        break;
    }

}
//Check if the last element is the player
if(board[yr][c] == user){
return true;
}else{
return false;}
}

//CHECKING UP TO DOWN
bool checkUD(char board[][CSIZE], int r, int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int yr = r + 1 ;
for(yr ; yr <=7  ; yr++){

    if(board[yr][c] == opp){
        //Enemy
        continue;
    }else{
        //Player/end
        break;
    }

}
//Check if the last element is the player
if(board[yr][c] == user){
return true;
}else{
return false;}
}

//CHECKING DIAGONAL UP
bool checkDIAGL(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int x=c+1;
int y=r+1;
for(x , y ; x <= 7 && y <= 7 ; x++, y++){

if(board[y][x] == opp){
    //Enemy
    continue;
}else{
    //Player/end
    break;
}
}
//Check if the last element is the player
if(board[y][x] == user){
return true;
}else{
return false;}
}

//CHECKING DIAGONAL LEFT UP
bool checkDIAGLback(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int x=c-1;
int y=r-1;
for(x , y ; x >=0 && y >= 0 ; x--, y--){

if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
//Check if the last element is the player
if(board[y][x] == user){
return true;
}else{
return false;
}
}

//CHECKING DIAGONAL RIGHT
bool checkDIAGR(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int y = r-1;
int x = c+1;

for(x , y ; x <= 7 && y >=0 ; x++, y--){

if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
//Check if the last element is the player
if(board[y][x] == user){
return true;
}else{
return false;}


}

//CHECKING DIAGONAL RIGHT DOWN
bool checkDIAGRback(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

//Check if location is enemy, and if the last element is it the player. If so return true
int y = r+1;
int x = c-1;

for(x , y ; y <= 7 && x >=0 ; x--, y++){

if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
//Check if the last element is the player
if(board[y][x] == user){
return true;
}else{
return false;}
}


//****************************************DONE PERFORMING CHECKING************************************************************************************************************

bool checkMove(char board[][CSIZE], char user, int r, int c, vector<int> &vmoves){

//Set player and opponent
char opp = ' ';

if(user == 'w'){

    opp = 'b';

}else{ opp = 'w' ;}

if(board[r][c] != ' '){
    return false;
}

//Check all 8 directions, if the location is valid (returns true) for a direction push it into the validmoves vector

//check on the left
if(board[r][c-1] == opp){
    if(checkRL(board,r,c,user)){vmoves.push_back(r*10+c);}
}
//check on the right
if(board[r][c+1] == opp){
    if(checkLR(board, r, c, user)){vmoves.push_back(r*10+c);}
}
//check above
if(board[r-1][c] == opp){
    if(checkDU(board, r, c, user)){vmoves.push_back(r*10+c);}
}
//check below
if(board[r+1][c] == opp){
    if(checkUD(board, r, c, user)){vmoves.push_back(r*10+c);}
}

//check left diagonal
if(board[r+1][c+1] == opp){
    if(checkDIAGL(board, r, c, user)){vmoves.push_back(r*10+c);}
}
//check left diagonal up
if(board[r-1][c-1] == opp){
    if(checkDIAGLback(board, r, c, user)){vmoves.push_back(r*10+c);}
}

//check right diagonal
if(board[r-1][c+1] == opp){
    if(checkDIAGR(board, r, c, user)){vmoves.push_back(r*10+c);}
}

//check right diagonal up
if(board[r+1][c-1] == opp){
    if(checkDIAGRback(board, r, c, user)){vmoves.push_back(r*10+c);}
}

return true;


}

//GET HUMAN MOVE
bool getMove(char board[RSIZE][CSIZE], char user){

    //Make sure user enters valid location using while(boolean)
    bool choice = false;

    while(!choice){

    //Get valid moves for player
    vector<int> vmoves = getValidMoves(board,user);

    //vr = valid row
    //vc = valid column
    int vr ;
    int vc ;

    //Print valid user moves
    cout << "valid user moves: " << endl;

    for(int i = 0 ; i < vmoves.size() ; i++ ){

        //Format the moves
        if((vmoves.at(i) / 10)  != 0){
        vr = vmoves.at(i) / 10;
        }else{vr = 0;}

        if((vmoves.at(i) % 10)  != 0){
        vc = vmoves.at(i) % 10;
        }else{vc = 0;}

    //Show valid moves in letter-number format
    cout << (char)('a' + vc) << "" << (vr+1) << " ";

    }

    cout << endl;

    //IF VALID MOVES VECTOR IS 0 THAT MEANS THERE ARE NO VALID MOVES FOR THE PLAYER + SO IT IS TIME TO EXIT (RETURN)
    if(vmoves.size() == 0){
            cout << "You have no valid moves" << endl;
            return false;
    }


    string move = "";
    //Get users move
    cout << "Enter column and row ex. f5 OR q to quit: " ;
    cin >> move;
    
    cout << endl;

    //If user enters q they choose to quit. If so, show the winner
	if(move == "q"){
            cout << calculateWin(board, true) << endl;
            exit(0);
            return false;
            }

    //Break the users string move into row and column
	int rmove = (move.at(1)-'0') - 1;
    int cmove =move.at(0)-'a';

    //Check if useres move is valid and if so perform out flank

    //Check if users entered location is not empty.
    if(board[rmove][cmove] != ' '){
        cout << "Spot occupied. " ;
    }

    //Check if users move is inside the valid moves vector.
    //find returns vector end size if users entered move is not found in the valid moves vector
    if(find(vmoves.begin(), vmoves.end(), rmove*10+cmove) != vmoves.end()){
    outFlank(board, user, rmove, cmove);
    //Break out of while(boolean) because the users move is valid and the outflank has been performed. No need to ask the user to enter another move.
    choice = true;
    }else{ cout << "Try again." << endl;}

    }

    return true;

}


//Runs through the 8x8 grid and find all valid moves for the current player
vector<int> getValidMoves(char board[][CSIZE] , char user){

vector<int> validmoves ;

for(int i = 0 ; i < RSIZE ; i++){

    for(int j = 0 ; j < CSIZE ; j++){

        {
        //If the board is empty then check if it the current location is valid (checks all 8 directions)
        if(board[i][j] == ' '){
        checkMove(board, user , i , j, validmoves);
        }

        }

    }
}
//Returns the vector of valid moves
return validmoves;

}


//---------------------------- USED BY CALCULATEMOSTPOINTS FUNCTION: calculates points for the passed in move in each direction, if direction is invalid returns 0 points. (points = # of swaps) ---------------------------------------------

//CALCULATES POINTS FOR RIGHT TO LEFT OUTFLANK
int calcRL(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int x=c-1;
for(x ; x >= 0 ; x--){

if(board[r][x] == opp){
    continue;
}else{
    break;
}
}
if(board[r][x] == user){
    //Return the number of swaps in between
    return c-x;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}
}

//CALCULATES POINTS FOR LEFT TO RIGHT OUTFLANK
int calcLR(char board[][CSIZE] ,  int r, int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int xr = c + 1;
for(xr ; xr <= 7 ; xr++){

if(board[r][xr] == opp){
    continue;
}else{break;}
}

if(board[r][xr] == user){
    //Return the number of swaps in between
    return xr - c;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}

}

//CALCULATES POINTS FOR DOWN TO UP OUTFLANK
int calcDU(char board[][CSIZE], int r, int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int yr = r - 1 ;
for(yr ; yr >= 0 ; yr--){

    if(board[yr][c] == opp){
        continue;
    }else{break;}

}
if(board[yr][c] == user){
    //Return the number of swaps in between
    return r - yr;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}
}

//CALCULATES POINTS FOR UP TO DOWN OUTFLANK
int calcUD(char board[][CSIZE], int r, int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int yr = r + 1 ;
for(yr ; yr <=7  ; yr++){

    if(board[yr][c] == opp){
        continue;
    }else{break;}

}
if(board[yr][c] == user){
    //Return the number of swaps in between
    return yr - r;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}
}

//CALCULATES POINTS FOR DIAGONAL UP OUTFLANK
int calcDIAGL(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int x=c+1;
int y=r+1;
for(x , y ; x <= 7 && y <= 7 ; x++, y++){

if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
if(board[y][x] == user){
    //Return the number of swaps in between
    return x-c;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}
}

//CALCULATES POINTS FOR DIAGONAL LEFT UP OUTFLANK
int calcDIAGLback(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int x=c-1;
int y=r-1;
for(x , y ; x >=0 && y >= 0 ; x--, y--){

if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
if(board[y][x] == user){
    //Return the number of swaps in between
    return c-x;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}
}

//CALCULATES POINTS FOR DIAGONAL RIGHT OUTFLANK
int calcDIAGR(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int y = r-1;
int x = c+1;

for(x , y ; x <= 7 && y >=0 ; x++, y--){

if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
if(board[y][x] == user){
    //Return the number of swaps in between
    return x-c;
}else{
    //If it is not a valid move then return 0 points
    return 0;
    }

}

//CALCULATES POINTS FOR DIAGONAL RIGHT DOWN OUTFLANK
int calcDIAGRback(char board[][CSIZE],int r,int c, char user){

//Set player and opponent
    char opp = ' ';

    if(user == 'w'){

        opp = 'b';

    }else{ opp = 'w' ;}

//Find start and end values and calculate the number of swaps in between (including start and end)
int y = r+1;
int x = c-1;

for(x , y ; y <= 7 && x >=0 ; x--, y++){
if(board[y][x] == opp){
    continue;
}else{
    break;
}
}
if(board[y][x] == user){
    //Return the number of swaps in between
    return y -r;
}else{
    //If it is not a valid move then return 0 points
    return 0;
}

}

//-------------------------------------DONE CALCULATING POINTS-----------------------------------------------------------------------


//Used by AImove2. Calculates the points for each move ( checks points for each direction ). (points = # of swaps)
int calculateMostPoints(char board[][CSIZE],int r,int c, char user){
    //Gets points (swaps) in each of the directions
    //If the move is not valid in a direction it returns 0 points.
    int points = calcRL(board,r,c,user) + calcLR(board,r,c,user) + calcUD(board,r,c,user) + calcDU(board,r,c,user) +calcDIAGL(board,r,c,user) +calcDIAGLback(board,r,c,user) + calcDIAGR(board,r,c,user) + calcDIAGRback(board,r,c,user);
    return points;
}

//AIMOVE : when it is the computers move, the computer recieves the valid moves that it can play.
//Then it calls the calculateMostPoints for each location in the valid moves vector. It saves the points results for each location in a vector called points.
//Then the computer chooses to play the move that gives it the most points.
void getAImove2(char board[][CSIZE] , char user){

//Get valid moves that the computer can play
vector<int> cmoves = getValidMoves(board,user);

vector<int> points ;

//If valid moves vector is size 0 that means there are no valid moves to play and either give your turn to the other player or it is game over if both players have no moves.
if(cmoves.size() == 0){
        cout << "Computer has no valid moves" << endl;
        return ;
}

//calculate points for each of the valid moves
for(unsigned int i = 0 ; i < cmoves.size() ; i++){

    int rmove;
    if((cmoves.at(i) / 10)  != 0){
    rmove = cmoves.at(i) / 10;
    }else{rmove = 0;}

    int cmove ;
    if((cmoves.at(i) % 10)  != 0){
    cmove = cmoves.at(i) % 10;
    }else{cmove = 0;}

    //calculate points for that move and add the points to points array
    //depending on the index of the move in the valid moves vector, the index of that moves points will be the same.
    points.push_back(calculateMostPoints(board,rmove,cmove,user));

}

//Get the index of the value that gives the most points
int posbest =  distance(points.begin(), max_element(points.begin(),points.end()));

//Find the location on the grid that gives the most points by using the index calculated above.
int best = cmoves.at(posbest);

    //Break move into row and column to perform outflank
    int rmove;
    if((best / 10)  != 0){
    rmove = best / 10;
    }else{rmove = 0;}

    int cmove ;
    if((best % 10)  != 0){
    cmove = best % 10;
    }else{cmove = 0;}

    //vr = valid row
    //vc = valid column
    int vr;
    int vc;

    //Show all computer moves
    
    cout << endl;
    
      cout << "valid computer moves: " << endl;

    //Formatting
    for(unsigned int i = 0 ; i < cmoves.size() ; i++ ){

    if((cmoves.at(i) / 10)  != 0){
    vr = cmoves.at(i) / 10;
    }else{vr = 0;}

    if((cmoves.at(i) % 10)  != 0){
    vc = cmoves.at(i) % 10;
    }else{vc = 0;}

   cout << (char)('a' + vc) << "" << (vr+1) << " ";

    }


    
//Print computer move
cout << "COMPUTER PLAYS " << (char)('a' + cmove) << "" << (rmove+1) << endl;
    cout << endl;
//Perform outflank for the location the computer has chosen to play
outFlank(board,user,rmove,cmove);


}

//main function starts and runs the Othello game until game over (each player has no valid moves)
int main(){

//Create board
char board[RSIZE][CSIZE] ;

//initialize board to be empty
for(int r = 0 ; r < RSIZE ; r++){
   for(int c = 0 ; c < CSIZE ; c++){
    board[r][c] = ' ';
   }
}

//Set 4 initial pieces
board[3][3] = 'w';
board[4][4] = 'w';
board[3][4] = 'b';
board[4][3] = 'b';

//User & computer player variables
char user ;
char comp ;

//The human player gets to choose whether they want to play white or black - their result is saved in char res variable
char res = ' ';

//If human player has entered something other than w or b then ask to enter the letter again
bool choice = false;

//Keep asking until choice becomes true
while(!choice){

cout << "Would you like to play black or white? Enter w or b" << endl;
cin >> res;

//Once usr is set then set the opponent (computer)
if(res == 'b'){
    user = 'b';
    comp = 'w';
    choice = true;

//Something entered other than w or b ask user to try again
}else if(res != 'b' && res != 'w'){
    cout << "Try again." << endl;

}else{
    comp = 'b';
    user = 'w';
    choice = true;
}
}

//bool play controls the while loop to run the game
bool play = true;

//I switch the players using integer player variable. Depending on which player plays, the variable will increment up or down.
int player = 0;

cout << endl;

//Display first unplayed board
displayBoard(board);

//If user entered they want to be w, then that means the computer goes first
if(comp == 'b'){

cout <<"COMPUTER PLAYS: " << endl;
   getAImove2(board,comp);
   //Now that the computer has player, the next to play is the human which is player # 1
   player = 1;


}else{
//else the user entered b so the human plays first
//and the computer player integer is 0
    getMove(board,user);

}

//1 play has been made, display the board again.
displayBoard(board);

//Enter while loop to play game back and forth between human and computer
while(play){

    //Player 1 = human player
    if(player == 1){
           getMove(board,user);
           displayBoard(board);
            calculateWin(board,false);
            player --;
       cout << endl;
    }

    //Player 0 = computer move
      if(player == 0){
            getAImove2(board,comp);
           //getMoveC(board,comp);
           displayBoard(board);
            calculateWin(board,false);
            player ++;
         cout << endl;
    }

    //Make sure that if both players have no valid moves to play then it is game over
    vector<int> umoves = getValidMoves(board,user) ;
    vector<int> cmoves = getValidMoves(board,comp) ;

    if(umoves.size() == 0 && cmoves.size() == 0){
        play = false;
        //Print end game message & show game winner. Could be a draw.
        cout << "No more moves to play. Game over." << endl;
        cout << calculateWin(board,true) << endl;

    }

}

return 0;

}



// ----------------------PAST AI STRATEGIES COMMENTED OUT AND MY BEST STRATEGY (GETAIMOVE2) USED ABOVE ---------------------------

/*
void getAImove(char board[][CSIZE] , char user){

vector<int> cmoves = getValidMoves(board,user);

int counter = 0;
int best = 0;

//starts with first index
for (int i = 0; i < cmoves.size(); i++){
    int newcounter = 1;
    int current = cmoves.at(i);
    //checks with the value in front
    for (int j = i + 1; j < cmoves.size(); j++){
        //if they are the same increment the counter
        if (cmoves.at(j) == current){
            counter++;
        }
    }
    //
    if (newcounter >= counter){
        counter = newcounter;
        best = current;
    }
}

int rmove;
if((best / 10)  != 0){
rmove = best / 10;
}else{rmove = 0;}

int cmove ;
if((best % 10)  != 0){
cmove = best % 10;
}else{cmove = 0;}

int vr;
int vc;

  cout << "valid computer moves: " << endl;

    for(int i = 0 ; i < cmoves.size() ; i++ ){

    if((cmoves.at(i) / 10)  != 0){
    vr = cmoves.at(i) / 10;
    }else{vr = 0;}

    if((cmoves.at(i) % 10)  != 0){
    vc = cmoves.at(i) % 10;
    }else{vc = 0;}

   cout << (char)('a' + vc) << "" << (vr+1) << " ";

    }

    cout << endl;



cout << "COMPUTER PLAYS " << (char)('a' + cmove) << "" << (rmove+1) << endl;

outFlank(board,user,rmove,cmove);


}
*/

/*
//GET COMPUTER MOVE
bool getMoveC(char board[][CSIZE], char user){

vector<int> vmoves = getValidMoves(board, user);

if(vmoves.size() == 0){
        cout << "Computer has no valid moves" << endl;
        return false;
}
int vr ;
int vc ;


  cout << "valid computer moves: " << endl;

    for(int i = 0 ; i < vmoves.size() ; i++ ){

    if((vmoves.at(i) / 10)  != 0){
    vr = vmoves.at(i) / 10;
    }else{vr = 0;}

    if((vmoves.at(i) % 10)  != 0){
    vc = vmoves.at(i) % 10;
    }else{vc = 0;}

   cout << (char)('a' + vc) << "" << (vr+1) << " ";

    }

    cout << endl;


int rmove;
if((vmoves.at(0) / 10)  != 0){
rmove = vmoves.at(0) / 10;
}else{rmove = 0;}

int cmove ;
if((vmoves.at(0) % 10)  != 0){
cmove = vmoves.at(0) % 10;
}else{cmove = 0;}


cout << "COMPUTER PLAYS " << (char)('a' + cmove) << "" << (rmove+1) << endl;

outFlank(board,user,rmove,cmove);

}
*/
