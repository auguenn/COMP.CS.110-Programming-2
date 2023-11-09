#include "functions.hh"
#include "gameengine.hh"
#include <iostream>

using namespace std;

// Sets a desired number of players in the game engine given as a parameter.
void set_players(GameEngine& eng)
{
    cout << "Enter the number of players: ";
    string player_amount_str = "";
    getline(cin, player_amount_str);
    unsigned int player_amount = 0;
    if(player_amount_str.size() == 1 and isdigit(player_amount_str.at(0)))
    {
        player_amount = stoi(player_amount_str);
    }
    else
    {
        set_players(eng); // recursive call
    }
    for(unsigned int i = 0; i < player_amount; ++i)
    {
        Player player = {i + 1, INITIAL_NUMBER_OF_ROLLS, {}, {}};
        eng.add_player(player);
    }
}

// Enables playing the game until all players have used all their turns,
// or until the quit command is given.
// Based on user input, makes the game engine given as a parameter to
// roll dices, give turn to another player, or quit.
void play_game(GameEngine& eng)
{
    if(eng.is_game_over())
    {
        return;
    }
    eng.update_guide();
    cout << "Enter selection (R = roll, T = give turn, Q = quit): ";
    string selection = "";
    getline(cin, selection);
    if(selection == "R" or selection == "r")
    {
        eng.roll();
    }
    else if(selection == "T" or selection == "t")
    {
        eng.give_turn();
    }
    else if(selection == "Q" or selection == "q")
    {
        eng.report_winner();
        return;
    }
    else
    {
        cout << "wrong selection" << endl;
    }
    play_game(eng); // recursive call
}

// Short and sweet main function.
int main()
{
    GameEngine engine;
    set_players(engine);
    play_game(engine);
    return 0;
}
