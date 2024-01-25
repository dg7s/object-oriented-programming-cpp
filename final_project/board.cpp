#include "board.h"
#include <iostream>
#include "square.h"

int Board::getBoardSize() const{
    return boardSize;
}

int Board::getMaxPlayerNumber() const{
    return maxPlayerNumber;
}

int Board::returnStart() {
    return start;
}

void Board::makeAction(Player *player, int &square_index) {
    squares[square_index]->action(player, square_index);
}

bool Board::makeHipothethicalEnd( int &square_index, int movement_number) {
    for(int i = 1; i <= movement_number; i++){
        int current_position = (square_index + i) % boardSize;

        // Check if we find End square.
        if(squares[current_position]->hypotheticalEnd(square_index)){
            // Updated square index.
            square_index = current_position;
            return true;
        }
    }
    // The End square was not found.
    return false;
}

bool Board::makeHipothethicalAction(Player *player, int &square_index, int movement_number) {
    for(int i = 1; i <= movement_number; i++){
        int current_position = (square_index + i) % boardSize;

        // Check if we find HipothethicalAction square.
        if(squares[current_position]->hypotheticalAction(player, square_index)){
            // Update square index.
            square_index = current_position;
            return true;
        }
    }
    // The End square was not found.
    return false;

}

