#include "gameboard.hh"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>



GameBoard::GameBoard(char piece) : piece_(piece), moves_(0), pieces_left_(48) {
    initializeBoard();
}



void GameBoard::initializeBoard() {
    board.resize(SIZE, std::vector<char>(SIZE, ' '));

    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if ((i < 2 || i > 5) || (j < 2 || j > 5)) {
                board[i][j] = piece_;
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

bool GameBoard::validateCoordinates(const std::vector<std::string>& input) {

    // Tarkista, että syötteessä on 4 koordinaattia
    if (input.size() != 4) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    int x1, y1, x2, y2;

    // Yritä muuntaa syötteet luvuiksi
    if (!(std::istringstream(input[0]) >> x1) || !(std::istringstream(input[1]) >> y1) ||
        !(std::istringstream(input[2]) >> x2) || !(std::istringstream(input[3]) >> y2)) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    // Tarkista, että koordinaatit ovat pelilaudan sisällä (1-8)
    if (x1 < 1 || x1 > 8|| y1 < 1 || y1 > 8|| x2 > 8|| y2 < 1 || y2 > 8) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    return true;
}

bool GameBoard::validateMove(int x1, int y1, int x2, int y2) {
    // Tarkista, että lähtö- ja kohdepisteet ovat pelilaudalla
    if (x1 < 1 || x1 > 8 || y1 < 1 || y1 > 8 || x2 < 1 || x2 > 8 || y2 < 1 || y2 > 8) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    // Tarkista, että lähtöpisteessä on nappula ja kohdepisteessä on tyhjä
    if (board[x1 - 1][y1 - 1] != piece_ || board[x2 - 1][y2 - 1] != ' ') {
        std::cout << "Cannot move from start point to destination point." << std::endl;
        return false;
    }
    // Tarkista, että siirto on viistoon
    if (abs(x2 - x1) != 2 || abs(y2 - y1) != 2) {
        std::cout << "Cannot move from start point to destination point." << std::endl;
        return false;
    }
    // Tarkista, että lähtöpisteen ja kohdepisteen välissä on täsmälleen yksi nappula
    int mid_x = (x1 + x2) / 2;
    int mid_y = (y1 + y2) / 2;

    if (board[mid_x - 1][mid_y - 1] != piece_) {
        std::cout << "Cannot move from start point to destination point." << std::endl;
        return false;
    }

    moves_ += 1;
    pieces_left_ -= 1;
    return true;
}

//void GameBoard::makeMove(int x1, int y1, int x2, int y2) {
       // board[x2][y2] = piece;
        //board[x1][y1] = ' ';
        //board[(x1 + x2) / 2][(y1 + y2) / 2] = ' ';
        //print();
//}


int GameBoard::getMoveCount() const {
    return moves_;
}

int GameBoard::getPiecesLeft() const {
    return pieces_left_;
}
