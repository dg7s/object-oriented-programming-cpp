#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <iostream>
#include "square.h"
#include "game.h"

class Game;
class  Square;

class Board {
    private:
        int start; // Index in vector of Start square.
        int boardSize; // Number of squares.
        int maxPlayerNumber; // Max available number of players on the board.
        vector < Square* > squares; // Vector of pointers to the squares.


public:
        // Constructors
        Board() = delete;
        // Vector of squares, maximum players number and index to start square.
        explicit Board(const vector<Square*> &squares, int _maxPlayerNumber,int start);

        // Destructor
        ~Board() = default;

        // Copy constructor and Assigment operator is deleted.
        Board(const Board& b) = delete;
        Board& operator=(const Board&) = delete;

        // Methods
        void addSquare(Square* square); // Add to list next square if possible.
        void makeAction(Player* player, int &square_index, const int game_id);
        bool makeHypotheticalAction(Player* player, int &square_index, const int game_id);
        bool makeHypotheticalEnd(int &square_index, int movement_number, const int game_id);

        // Getters
        int getBoardSize() const; // Returns a size of the board.
        int returnStart() const; // Returns a pointer to Start Square.
        //Square* playerSquare(Game*, Player*, int k); // Returns a pointer to a Square k away from the Player in the Game.
        int getMaxPlayerNumber() const;
        vector<square_name> NextSixFields(int square_index);
};


#endif // BOARD_H
