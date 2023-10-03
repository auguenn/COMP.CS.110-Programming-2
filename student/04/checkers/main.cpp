/* Tammipeli (yhdelle pelaajalle)
 *
 * Kuvaus:
 *   Ohjelma toteuttaa tammipelin yhdelle pelaajalle. Pelilaudan koko
 * on 8 x 8, ja se täytetään tyhjillä sekä pelinappuloilla (käyttäjän
 * valitsema merkki).
 *   Pelilauta on aluksi täynnä nappuloita, mutta keskellä on 4 x 4
 * -kokoinen alue tyhjää. Tarkoitus on saada pelilauta tyhjennettyä
 * niin, että jäljellä on vain yksi pelinappula. Nappulaa voi siirtää
 * viistosti toisen nappulan yli, jolloin poistetaan se nappula, jonka
 * yli hypättiin.
 *   Joka kierroksella käyttäjältä kysytään kahta pistettä (neljää
 * koordinaattia): siirrettävää nappulaa ja sen kohdesijaintia.
 * Ohjelma tarkistaa, voidaanko siirto tehdä.
 *   Ohjelma päättyy, kun pelilaudalla on enää yksi pelinappula tai kun
 * käyttäjä antaa lopetuskomennon (merkki 'q' tai 'Q'). Tällöin ohjelma
 * tulostaa, kuinka monta siirtoa tehtiin ja kuinka monta nappulaa on
 * vielä jäljellä.
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
#include <string>
#include <vector>

//Jakaa merkkijonon osiin.
//Parametrit: jaettava merkkijono, osien välinen erotin
//Paluuarvo: vektori, jossa merkkijono jaettuna osiin
std::vector<std::string> split(const std::string& string, const char delimiter) {
    std::vector<std::string> result;

    // Kopioidaan annettu merkkijono 'string' väliaikaiseen muuttujaan 'temp'
    // jotta alkuperäistä merkkijonoa ei muuteta.
    std::string temp = string;

    while(temp.find(delimiter) != std::string::npos) {
        std::string new_substring = temp.substr(0, temp.find(delimiter));
        temp = temp.substr(temp.find(delimiter)+1, temp.size());
        if(new_substring.empty() == false) {
            result.push_back(new_substring);
        }
    }
    result.push_back(temp);
    return result;
}


// Pääohjelma, joka pyytää käyttäjältä pelimerkin, minkä jälkeen pyytää
// käyttäjältä koordinaatteja siirtojen tekemiseksi.
// Kutsuu ylläolevaa funktiota sekä luokan GameBoard metodeja ja toteuttaa
// ohjelman paluuarvot.
// Paluuarvo: EXIT_SUCCESS
int main() {
    std::string character = "";

    std::cout << "Enter piece character: ";
    getline(std::cin, character);

    char piece = character.at(0);

    // Luodaan pelilauta käyttäen annettua pelinappulan merkkiä.
    GameBoard gameBoard(piece);

    gameBoard.initializeBoard();
    gameBoard.print();

    std::string input = "";
    char separator = ' ';

    // Luodaan pääohjelman silmukka, joka suorittaa pelaajan syötteitä kunnes
    // pelaaja päättää lopettaa.
    while (true) {
        std::cout << "Enter start point (x, y) and destination point (x, y),"
                            " or q to quit: ";
        getline(std::cin, input);

        if (input == "q" || input == "Q") {
            break;
        }

        else {
            // Jaetaan input-merkkijono koordinaatteihin.
            std::vector<std::string> coords = split(input, separator);

            if (!gameBoard.validateCoordinates(coords)) {
                continue;
            }

            // Muunnetaan koordinaatit kokonaisluvuiksi.
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
