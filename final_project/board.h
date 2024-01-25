#ifndef BOARD_H
#define BOARD_H

#include <list>
#include <iostream>
#include "square.h"
#include "game.h"

class Board {
    private:
        int start; // Index in vector of Start square.
        int boardSize; // Number of squares.
        int maxPlayerNumber; // Max available number of players on the board.
        vector < Square* > squares; // Vector of pointers to the squares.


public:
        // Constructors
        Board() = delete;
        Board(int _boardSize);
        Board(vector<Square*> );

        // Destructor
        ~Board() = default;

        // Copy constructor and Assigment operator is deleted.
        Board(const Board& b) = delete;
        Board& operator=(const Board&) = delete;

        // Methods
        void addSquare(Square* square); // Add to list next square if possible.
        bool tryToFindEND(int &player_position, int move_number);

        // Make
        void makeAction(Player* player, int &square_index);
        bool makeHipothethicalAction(Player* player, int &square_index, int movement_number);
        bool makeHipothethicalEnd(int &square_index, int movement_number);

    // Getters
        int getBoardSize() const; // Returns a size of the board.
        int returnStart(); // Returns a pointer to Start Square.
        Square* playerSquare(Game*, Player*, int k); // Returns a pointer to a Square k away from the Player in the Game.
        int getMaxPlayerNumber() const;
};


#endif // BOARD_H
