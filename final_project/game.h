#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <utility>
#include "board.h"
#include "player.h"
#include "square.h"

class Board;
class Player;

using namespace std;
class Game {
    private:
        int turnsNumber; // Number of already played turns.
        bool isStarted; // True - game is on, False := game hasn't started.
        bool isWinner; // True if someone end a game.
        Board* board; // Pointer to the board.
        int game_id; // Game id.

        // Vector to the pair of pairs. We have pointer to player and his position on the board.
        vector < pair<Player*, int> > players;
        vector <int> winners;

        // Pointers to the three dices.
        Dice* common;
        Dice* deteriorating;
        Dice* defective;


    public:
        // Constructors
        Game() = delete;
        Game(Board* _board, const vector<Player*> &_players, Dice* _common,
         Dice* _deteriorating, Dice* _defective, int _game_id);

        // Destructor
        ~Game();

        // Copy constructor and Assigment operator is deleted.
        Game(const Game& g) = delete;
        Game& operator=(const Game&) = delete;

        // Methods.
        void addPlayer(Player* player, int game_id); // Add player to the game. Possible only before start of the game.
        void startGame(); // Starts the game.
        void makeTour(); // Make all moves in current tour.
        void finish(); // End the game and print the results.
        void makeMove(int move_number); // Make move for current player. Given index to player.


        // Methods connected to players.
        // If DokTOr_level = 13 player try to find tries to find the nearest end square within range k
        void tryToEnd(int player_index, int rolled_number);
        // If roll() = 6 maybe player wants to choose an earlier regeneration field.
        void tryToRegeneration(int player_index);
        void normalMove(int player_index, int rolled_number);
        int getTurnsNumber() const;

        // Getters to dices.
        Dice* getDice(dice_name);
};


#endif // GAME_H
