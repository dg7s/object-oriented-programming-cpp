#include "board.h"
#include "square.h"

Board::Board(const vector<Square*> &squares, int _maxPlayerNumber, int _start): boardSize(squares.size()),
maxPlayerNumber(_maxPlayerNumber), squares(squares), start(_start) {}

int Board::getBoardSize() const{
    return boardSize;
}

int Board::getMaxPlayerNumber() const{
    return maxPlayerNumber;
}

int Board::returnStart() const {
    return start;
}

void Board::addSquare(Square *square) {
    squares.push_back(square);
    boardSize++;
}

vector<square_name> Board::NextSixFields(int square_index) {
    vector<square_name> futureFields;
    for(int i = 1; i <= 6; i++){
        square_index = (square_index + 1) % boardSize;
        squares[square_index]->addSquareToVector(futureFields);
    }
    return futureFields;
}

void Board::makeAction(Player *player, int &square_index, const int game_id) {
    squares[square_index]->action(player, square_index, game_id);
    square_index = square_index % boardSize;
}

bool Board::makeHypotheticalEnd( int &square_index, int movement_number, const int game_id) {
    for(int i = 1; i <= movement_number; i++){
        int current_position = (square_index + i) % boardSize;

        // Check if we find End square.
        if(squares[current_position]->hypotheticalEnd(square_index, game_id)){
            // Updated square index.
            square_index = current_position;
            cout<<" and moved to the square "<<current_position<<"\n";
            return true;
        }
    }
    // The End square was not found.
    return false;
}

bool Board::makeHypotheticalAction(Player *player, int &square_index, const int game_id) {
    for(int i = 1; i <= 6; i++){
        int current_position = (square_index + i) % boardSize;

        // Check if we find HypotheticalAction square.
        if(squares[current_position]->hypotheticalAction(player, game_id)){
            // Update square index.
            square_index = current_position;
            cout<<" and moved to the square "<<current_position<<"\n";
            return true;
        }
    }
    // The End square was not found.
    return false;

}

