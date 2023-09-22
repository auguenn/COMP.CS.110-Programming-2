#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

// Pelilaudan koko
// Size of the gameboard
const unsigned int SIZE = 8;

// Vasemmanpuoleisimman sarakkeen koko, tarvitaan pelilaudan tulostamisessa
// Width of the left-most column, needed in printing the gameboard
const unsigned int LEFT_COLUMN_WIDTH = 5;

// GameBoard-luokka
// GameBoard class
class GameBoard
{
public:
    // Rakentaja: tarvittaessa voit lisätä parametreja
    // Constructor: you can add parameters if needed
    GameBoard();

    // Tulostaa pelilaudan (kunhan olet viimeistellyt metodin).
    // Prints the gameboard (after you have finished the method).
    void print() const;

private:
    // Tulostaa annetun pituisen rivin annettua tulostumerkkiä.
    // Prints a line with the given length and fill character.
    void print_line(unsigned int length, char fill_character) const;
};

#endif // GAMEBOARD_HH
