#include "gameboard.hh"
#include <iostream>

using namespace std;

int main()
{
    char piece;
     std::cout << "Enter piece character: ";
     std::cin >> piece;
     GameBoard gameBoard(piece);
     gameBoard.initializeBoard();
     gameBoard.print();
    return 0;
}
