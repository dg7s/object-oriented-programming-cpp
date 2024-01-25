#include "game.h"
#include <iostream>
#include <utility>
#include <vector>
#include "player.h"
#include "square.h"
#include "dice.h"
#include "cassert"

Game::Game(Board* _board, const vector<Player*> &_players, Dice* _common,
           Dice* _deteriorating, Dice* _defective, int _game_id): turnsNumber(0), isStarted(false),
                                               isWinner(false), board(_board),  common(_common),
                                               deteriorating(_deteriorating), defective(_defective), game_id(_game_id){
    if(_players.size() > _board->getMaxPlayerNumber()) {
        throw logic_error("The maximum number of players has been exceeded.");
    }
    // Initialize vector <Players*, turns_to_wait
    for (auto & player : _players) {
        addPlayer(player);
    }
}

// Methods.
void Game::addPlayer(Player* player) {
    if(isStarted) {
        throw logic_error("The game is in progress.");
    }
    if (players.size() + 1 > board->getMaxPlayerNumber()) {
        throw logic_error("The maximum number of players has been exceeded.");
    } else {
        players.emplace_back(player, board->returnStart());
    }
}

void Game::startGame() {
    isStarted = true;
    while(!isWinner) {
        makeTour();
    }
    finish();
}

int Game::getTurnsNumber() const{
    return turnsNumber;
}

void Game::makeTour(){
    for( int index = 0; index < players.size(); index++) {
        makeMove(index);
    }
    turnsNumber++;
}

// k - index of player in our vector.
void Game::makeMove(int index) {
    player_decision decision = players[index].first->playerDecision(game_id);

    switch(decision) {
        case player_decision::wait:
            // Player waits a turn and his waitTime attribute decreases by one.
            break;
        case player_decision::end_game:
            // Player looks for an end square.
            tryToEnd(index);
            break;
        case player_decision::find_regenerate_square:
            tryToRegeneration(index);
            break;
        case player_decision::normal_move:
            normalMove(index);
            break;
    }

}

Dice* Game::getDice(dice_name _dice_name){
    switch(_dice_name) {
        case dice_name::common:
            return common;
        case dice_name::defective:
            return defective;
        case dice_name::deteriorating:
            return deteriorating;
        default:
            throw logic_error("Incorrect dice name.");
    }
}


void Game::tryToEnd(int player_index){
    // Players chooses a die.
    Dice * dice = getDice(players[player_index].first->chooseDice());

    // Player rolls the dice.
    int rolled_number = players[player_index].first->roll(dice);

    // If expression is false.
    if(!board->makeHipothethicalEnd(players[player_index].second,rolled_number)){
        normalMove(player_index);
    } else {
        // Add the player to winners.
        isWinner = true;
        winners.push_back(player_index);
    }


}
void Game::tryToRegeneration(int player_index){
    // Players chooses a die.
    Dice * dice = getDice(players[player_index].first->chooseDice());

    // Player rolls the dice.
    int rolled_number = players[player_index].first->roll(dice);

    // If the expression is false, we perform normal movement.
    if(!board->makeHipothethicalAction(players[player_index].first, players[player_index].second,rolled_number)){
        normalMove(player_index);
    }
}


void Game::normalMove(int player_index) {
    // Players chooses a die.
    Dice * dice = getDice(players[player_index].first->chooseDice());

    // Player rolls the dice, and we calculate the final index of square.
    // new_player_position = (rolled_number + actual index on the board) modulo size of the board
    int new_player_position = (players[player_index].first->roll(dice) + players[player_index].second)
            % board->getBoardSize();

    players[player_index].second = new_player_position;

    // The appropriate action for the square is performed. Function updates the player's position.
    board->makeAction(players[player_index].first, players[player_index].second);
}

// Print out the winners.
void Game::finish(){
    cout<<"After ";
    cout<<getTurnsNumber();

    assert((!winners.empty()) && "Error during ending the game.");

    if(winners.size() == 1) {
        cout<<"round the game is over.";
        cout << "Player ";
        players[winners[0]].first->coutName();
        cout << " won the game.";
    }
    else {
        cout<<"rounds the game is over.";
        cout<<"Players: ";
        for(int i = 0; i < winners.size(); i++){
            players[winners[0]].first->coutName();
            cout<<", ";
        }
        cout<<"won the game.";
    }
}
