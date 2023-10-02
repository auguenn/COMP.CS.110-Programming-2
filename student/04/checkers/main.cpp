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
    std::cout << "Enter start point (x, y) and destination point (x, y), or q to quit: ";
    getline(std::cin, input);

    std::vector<std::string> coords = split(input, separator);

    if (gameBoard.validateInput(coords)) {
        std::cout<<coords.size()<<std::endl;
        std::cout<<"jee"<<std::endl;
    }

    return EXIT_SUCCESS;
}
