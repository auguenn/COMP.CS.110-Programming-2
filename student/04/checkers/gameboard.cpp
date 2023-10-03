/* Tammipeli (yhdelle pelaajalle)
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Enna Augustin
 * Opiskelijanumero: 50235634
 * Käyttäjätunnus: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 *
 * */


#include "gameboard.hh"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>



GameBoard::GameBoard(char piece) : piece_(piece), moves_(0), pieces_left_(48) {
    initializeBoard();
}


int GameBoard::getMoveCount() const {
    return moves_;
}


int GameBoard::getPiecesLeft() const {
    return pieces_left_;
}


bool GameBoard::validateCoordinates(const std::vector<std::string>& input) {
    // Tarkistetaan, että syötteessä on 4 koordinaattia.
    if (input.size() != 4) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    unsigned int x1 = 0;
    unsigned int y1 = 0;
    unsigned int x2 = 0;
    unsigned int y2 = 0;

    // Yritetään muuntaa syötteet luvuiksi ja tulostetaan mahdollinen
    // virheilmoitus.
    if (!(std::istringstream(input[0]) >> x1) || !(std::istringstream(input[1])
                                                                      >> y1) ||
        !(std::istringstream(input[2]) >> x2) || !(std::istringstream(input[3])
                                                                      >> y2)) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    // Tarkistetaan, että koordinaatit ovat pelilaudan sisällä.
    if (x1 < 1 || x1 > SIZE || y1 < 1 || y1 > SIZE || x2 > SIZE || y2 < 1
                                                                || y2 > SIZE) {
        std::cout << "Invalid start/destination point." << std::endl;
        return false;
    }

    return true;
}


bool GameBoard::validateMove(int x1, int y1, int x2, int y2) {
    // Tarkistetaan, että lähtöpisteessä on nappula ja kohdepisteessä on tyhjä
    // peliruutu.
    if (board[y1 - 1][x1 - 1] != piece_ || board[y2 - 1][x2 - 1] != ' ') {
        std::cout << "Cannot move from start point to "
                                             "destination point." << std::endl;
        return false;
    }

    // Tarkistetaan, että siirto on viistoon.
    if (std::abs(x2 - x1) != 2 || std::abs(y2 - y1) != 2) {
        std::cout << "Cannot move from start point to "
                                             "destination point." << std::endl;
        return false;
    }

    // Tarkistetaan, että lähtöpisteen ja kohdepisteen välissä on täsmälleen
    // yksi nappula.
    int mid_x = (x1 + x2) / 2;
    int mid_y = (y1 + y2) / 2;

    if (board[mid_y - 1][mid_x - 1] != piece_) {
        std::cout << "Cannot move from start point to "
                                             "destination point." << std::endl;
        return false;
    }

    moves_ += 1;
    pieces_left_ -= 1;
    return true;
}


void GameBoard::makeMove(int x1, int y1, int x2, int y2) {
    // Suoritetaan siirto.
    board[y2 - 1][x2 - 1] = piece_;
    board[y1 - 1][x1 - 1] = ' ';

    // Lasketaan siirron keskelle jäävä koordinaatti ja poistetaan siitä
    // pelimerkki.
    int mid_x = (x1 + x2) / 2;
    int mid_y = (y1 + y2) / 2;

    board[mid_y - 1][mid_x - 1] = ' ';

    // Tulostetaan uusi pelitilanne.
    print();
}


void GameBoard::initializeBoard() {
    // Alustetaan pelilauta, joka on vektori vektorissa
    // (2-ulotteinen pelilauta).
    board.resize(SIZE, std::vector<char>(SIZE, ' '));

    for (unsigned int i = 0; i < SIZE; i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            // Muodostetaan rajoitteet keskustan tyhjälle ruudulle.
            if ((j < 2 || j > 5) || (i < 2 || i > 5)) {
                // Asetetaan koordinaattin pelinappula (piece_), jos se on
                // tyhjäksi jäävän alueen ulkopuolella.
                board[i][j] = piece_;
            }
            else {
                // Jos koordinaatti on halutun tyhjän alueen sisällä, asetetaan
                // siihen tyhjä ruutu.
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

