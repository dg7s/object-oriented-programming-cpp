#include "game.h"
#include <iostream>
#include <vector>
#include <memory>
#include "player.h"
#include "dice.h"
#include "cassert"

Game::Game(Board* _board, const vector<std::unique_ptr<Player>>& _players, Dice* _common,
           Dice* _deteriorating, Dice* _defective, int _game_id): turnsNumber(0), isStarted(false),
                                                                  isWinner(false), board(_board),  common(_common),
                                                                  deteriorating(_deteriorating), defective(_defective), game_id(_game_id){
    if(_players.size() > _board->getMaxPlayerNumber()) {
        throw logic_error("The maximum number of players has been exceeded.");
    }
    // Initialize vector <Players*, turns_to_wait>
    for (const auto & player : _players) {
        addPlayer(player.get());
    }
}

Game::~Game() {}

// Methods.
void Game::addPlayer(Player* player) {
    if(isStarted) {
        throw logic_error("The game is in progress.");
    }
    if (players.size() + 1 > board->getMaxPlayerNumber()) {
        throw logic_error("The maximum number of players has been exceeded.");
    } else {
        players.emplace_back(player, board->returnStart());
        player->joinNewGame(game_id);
    }
}

void Game::startGame() {
    cout<<"The game has started.\n";
    isStarted = true;
    while(!isWinner) {
        cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        cout<<"Round number "<<turnsNumber<<"\n";
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
void Game::makeMove(int player_index) {

    cout<<"Turn of ";
    players[player_index].first->coutStatus(game_id);
    cout<<"\n";

    // Check if player need to wait.
    // If true method decrease wait time and end round for this player.
    if(players[player_index].first->needToWait(game_id)) {return;}

    Dice *dice;

    // Check if player need to know the next 6 fields.
    if(players[player_index].first->needToKnowFuture()){
        vector<square_name> future = showTheNextSixFields(player_index);
        dice = getDice(players[player_index].first->chooseDiceWithFuture(future));
    }
    else {
        //If not.
        // Players chooses a die.
        dice = getDice(players[player_index].first->chooseDice());
    }

    // Player rolls the dice.
    int rolled_number = players[player_index].first->roll(dice);

    player_decision decision = players[player_index].first->playerDecision(game_id, rolled_number);

    switch(decision) {
        case player_decision::end_game:
            // Player looks for an end square.
            tryToEnd(player_index, rolled_number);
            break;
        case player_decision::find_regenerate_square:
            tryToRegeneration(player_index);
            break;
        case player_decision::normal_move:
            normalMove(player_index,rolled_number);
            break;
    }

}

vector<square_name> Game::showTheNextSixFields(int player_index) {
    return board->NextSixFields(players[player_index].second);
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


void Game::tryToEnd(int player_index, int rolled_number){


    // If expression is false.
    if(!board->makeHypotheticalEnd(players[player_index].second,rolled_number, game_id)){
        normalMove(player_index,rolled_number);
    } else {
        // Add the player to winners.
        isWinner = true;
        winners.push_back(player_index);
    }


}
void Game::tryToRegeneration(int player_index){

    // If the expression is false, we perform normal movement.
    if(!board->makeHypotheticalAction(players[player_index].first, players[player_index].second, game_id)){
        normalMove(player_index,6);
    }
}


void Game::normalMove(int player_index, int rolled_number) {
    // new_player_position = (rolled_number + actual index on the board) modulo size of the board
    int new_player_position = (rolled_number+ players[player_index].second)
            % board->getBoardSize();

    players[player_index].second = new_player_position;

    // The appropriate action for the square is performed. Function updates the player's position.
    board->makeAction(players[player_index].first, players[player_index].second, game_id);
}

// Print out the winners.
void Game::finish(){
    cout<<"After ";
    cout<<getTurnsNumber();

    assert((!winners.empty()) && "Error during ending the game.");

    if(winners.size() == 1) {
        cout<<" round the game is over.\n";
        cout << "Player ";
        players[winners[0]].first->coutName();
        cout << " won the game.\n";
    }
    else {
        cout<<" rounds the game is over.\n";
        cout<<"Players: ";
        for(int i = 0; i < winners.size(); i++){
            players[winners[0]].first->coutName();
            cout<<", ";
        }
        cout<<"won the game.\n";
    }

    // Deleted all attributes connected to this game.
    for (const auto& pair : players) {
        pair.first->endGame(game_id);
    }
}
