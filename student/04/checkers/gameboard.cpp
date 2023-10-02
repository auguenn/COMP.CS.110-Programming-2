#include "gameboard.hh"
#include <iostream>
#include <vector>


GameBoard::GameBoard(char piece) : piece(piece) {
    initializeBoard();
}



void GameBoard::initializeBoard() {
    board.resize(SIZE, std::vector<char>(SIZE, ' '));

    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if ((i < 2 || i > 5) || (j < 2 || j > 5)) {
                board[i][j] = piece;
            }
            else {
                board[i][j] = ' ';
            }
        }
    }
}

void GameBoard::print() const {
    // Tulostetaan yläreuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');

    // Tulostetaan otsikkorivi
    std::cout << "|   | ";
    for (unsigned int i = 0; i < SIZE; ++i) {
        std::cout << i + 1 << " ";
    }
    std::cout << "|" << std::endl;

    // Tulostetaan viiva otsikkorivin alle
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '-');

    // Tulostetaan pelilauta
    for (unsigned int i = 0; i < SIZE; ++i) {
        std::cout << "| " << i + 1 << " | ";
        for (unsigned int j = 0; j < SIZE; ++j) {
            std::cout << board[i][j] << " ";
        }
        std::cout << "|" << std::endl;
    }

    // Tulostetaan alareuna
    print_line(LEFT_COLUMN_WIDTH + 1 + 2 * SIZE + 1, '=');
}

void GameBoard::print_line(unsigned int length, char fill_character) const {
    for (unsigned int i = 0; i < length; ++i) {
        std::cout << fill_character;
    }
    std::cout << std::endl;
}

bool GameBoard::validateInput(std::vector<std::string>& input) {

        std::cout<<input.size()<<std::endl;
        return true;
}
