#include "gameboard.hh"
#include <iostream>
#include <string>
#include <vector>

//Jakaa merkkijono osiin.
//Parametrit: jaettava merkkijono, osien välinen erotin
//Paluuarvo: merkkijono jaettuna osiin
std::vector<std::string> split(const std::string& s, const char delimiter) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(new_part.empty() == false) {
            result.push_back(new_part);
        }
    }
    result.push_back(tmp);
    return result;
}


int main() {

    std::string character = "";
    std::cout << "Enter piece character: ";
    getline(std::cin, character);

    char piece = character.at(0);

    GameBoard gameBoard(piece);
    gameBoard.initializeBoard();
    gameBoard.print();

    std::string input = "";
    char separator = ' ';
    while (true) {
            std::cout << "Enter start point (x, y) and destination point (x, y),"
                            " or q to quit: ";
            getline(std::cin, input);

            if (input == "q") {
                break;
            }
            else {
                std::vector<std::string> coords = split(input, separator);

                if (!gameBoard.validateCoordinates(coords)) {
                    continue;
                }

                int x1 = std::stoi(coords[0]);
                int y1 = std::stoi(coords[1]);
                int x2 = std::stoi(coords[2]);
                int y2 = std::stoi(coords[3]);

                if (!gameBoard.validateMove(x1, y1, x2, y2)) {
                    continue;
                }


                gameBoard.makeMove(x1, y1, x2, y2);

            }
        }
    int moves = gameBoard.getMoveCount();
    int pieces = gameBoard.getPiecesLeft();
    std::cout << moves << " move(s) made." << std::endl;
    std::cout << pieces << " piece(s) left." << std::endl;
    return EXIT_SUCCESS;
}
