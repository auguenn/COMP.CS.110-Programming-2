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


#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH
#include <vector>
#include <string>

// Pelilaudan koko
const unsigned int SIZE = 8;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard-luokka
class GameBoard {
public:
    // Rakentaja
    GameBoard(char piece);

    // Hakee tehtyjen siirtojen määrän.
    // Parametrit: ei parametreja.
    // Paluuarvo: tehtyjen siirtojen lukumäärä.
    int getMoveCount() const;

    // Hakee jäljellä olevien pelimerkkien määrän.
    // Parametrit: ei parametreja.
    // Paluuarvo: jäljellä olevien pelimerkkien lukumäärä.
    int getPiecesLeft() const;

    // Tarkistaa, että käyttäjän antamat koodrinaatit ovat kelvolliset.
    // Parametrit: vektori, jossa käyttäjän antama syöte.
    // Paluuarvo: totuusarvo siitä, ovatko koordinaatit kelvolliset.
    bool validateCoordinates(const std::vector<std::string>& input);

    // Tarkistaa, että käyttäjän haluama siirto on mahdollinen.
    // Parametrit: koordinaatit (x1, y1, x2, y2) kokonaislukuina.
    // Paluuarvo: totuusarvo siitä, onko toivottu siirto mahdollinen.
    bool validateMove(int x1, int y1, int x2, int y2);

    // Tekee siirron pelilaudalla.
    // Parametrit: koordinaatit (x1, y1, x2, y2) kokonaislukuina.
    //Paluuarvo: vektori, jossa merkkijono jaettuna osiin
    void makeMove(int x1, int y1, int x2, int y2);

    // Alustaa pelilaudan.
    // Parametrit: ei parametreja.
    // Paluuarvo: ei paluuarvoa.
    void initializeBoard();

    // Tulostaa pelilaudan.
    // Parametrit: ei parametreja.
    // Paluuarvo: ei paluuarvoa.
    void print() const;


private:
    char piece_;
    int moves_;
    int pieces_left_;

    // Tulostaa annetun pituisen rivin annettua tulostumerkkiä.
    // Parametrit: kokonaisluku pituus ja merkki täyttävästä merkistä.
    // Paluuarvo: ei paluuarvoa.
    void print_line(unsigned int length, char fill_character) const;

    // Vektori, johon pelilauta ja sen pelinappulat lisätään.
    std::vector<std::vector<char>> board;

};

#endif // GAMEBOARD_HH
