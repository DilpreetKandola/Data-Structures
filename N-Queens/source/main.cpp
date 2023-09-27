#include <iostream>
#include <stack>
#include <vector>
#include <stdlib.h>
#include <limits>


bool conflictCheck(int, int, const std::vector<std::vector<int> >);
bool queenShift(int);
void NqueensSolver(std::vector<std::vector<int> >&);
void printBoard(const std::vector<std::vector<int> >);

//int that stores entered number by a user
int userNum = -1;

//struct that holds location of a queen
struct point {
    int row, column;
    point(int row, int column) : row(row), column(column) {};

};




int main() {

    //for while loop used for user input
    bool inputLoop = false;


    //while loop to get userinput while making sure fits criteria
    while(!inputLoop){

        std::cout << " Please enter a value N where |25 > N > 3|(Determines size of Board and amount of Queens): ";
        std::cin >> userNum;
        //checks if cin fail flag is set, then clears and ignores inputted characters
        if(std::cin.fail()){

            std::cout << "|Something went wrong, try again" << " (CIN INPUT FAIL)| " << std::endl;                                              

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        //else if to make sure input fits criteria
        else if(userNum > 3 && userNum <= 25){

            if(userNum > 10){
                std::cout << "WARNING: large N values are computationally expensive and may timeout depending on your system." << std::endl;
            }
            inputLoop = true;
        }
        
    }


    //DEFINITION(perfect for a chess board?): 2D vector in c++ is a vector of vectors. Allows manipulation of data in a grid format in my case 
    //creates 2D vector; N by N board where N is userinputted;
	std::vector<std::vector<int> > chessBoard(userNum, std::vector<int>(userNum, 0));


    NqueensSolver(chessBoard);
    printBoard(chessBoard);


}



void NqueensSolver(std::vector<std::vector<int> > &chessBoard){


    //booleans to see if goal is met, or needs back track
    bool goal = true, BackTrack = true;

    //variables for rows and columns; board fill tracker
    int qRow = 0, qCol = 0, fill = 0;

    //LAST IN FIRST OUT and stores queen position
    std::stack<point> Qstack;


    //one queen is pushed to first location
    chessBoard[0][0] = 1;
    Qstack.push(point(qRow, qCol));

    // code for actual N-Queen problem solving
    while(goal) {


        //conflict check and checks if backtrack is still needed
        if(conflictCheck(qRow, qCol, chessBoard) && BackTrack) {

            fill++;

            if(fill == userNum){
                goal = false;
            }

            //increment row and new col to 1; then push into stack
            else {
                qRow++, qCol = 0;
                chessBoard[qRow][qCol] = 1;
                Qstack.push(point(qRow, qCol));

            }

        }

        else if(queenShift(qCol + 1)){

            //make spot emtpy
            chessBoard[qRow][qCol] = 0;

            //pop queen for move
            Qstack.pop();
            qCol++;

            chessBoard[qRow][qCol] = 1;

            Qstack.push(point(qRow, qCol));
            BackTrack = true;

        }

        else {
            //row down if no location above
            fill--;

            chessBoard[qRow][qCol] = 0;
            Qstack.pop();

            //new spot for q
            qCol = Qstack.top().column, qRow = Qstack.top().row;
            BackTrack = false;

        }

    }




}





//function to check for queen conflicts(queen can take out another queenf or example)
bool conflictCheck(int qRow, int qCol, const std::vector<std::vector<int> > chessBoard){


	//traverse row columns 
    //nested loop to traverse rows and columns; better efficiency not needed till larger datasets of N
    for(int i = 0; i < userNum; i++){

        for(int j = 0; j < userNum; j++){

            //check position at I J for a queen
            if(chessBoard[i][j] == 1){

                //no conflict, thus continue
                if(qRow == i && qCol == j){
                    continue;
                }

                //same column conflict check
                else if(qCol == j){
                    return false;
                }

                //diagonal conflict check
                else if(abs(qCol - j) == abs(qRow - i)){
                    return false;
                }
            }
        }
    }

    //no conflict found
    return true;
}



//makes sure queens column number never exceeds userdefined N; this was part of the cause of segmentation error be more careful
bool queenShift(int qCol){

    if(qCol <= userNum - 1){
        return true;
    }

    return false;
}


//function to loop over 2darray and print out the board
void printBoard(const std::vector<std::vector<int> > chessBoard){

    for (int i = 0; i < userNum; i++) {
        for (int j = 0; j < userNum; j++) {
            std::cout << chessBoard[i][j]<< " ";
        }
        std::cout << std::endl;
    }



}