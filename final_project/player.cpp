#include "player.h"
#include <random>
#include <chrono>
#include <vector>

using namespace std;

//~~~~~~~~~~~~~~~
// Random
//~~~~~~~~~~~~~~~
default_random_engine generator_player(std::chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution_player(0,2);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Base class methods (Players)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Player::Player(string _player_name): player_name(std::move(_player_name)) {}

void const Player::coutName() {
    cout<<player_name;
}

void Player::coutStatus(int game_id) {

    cout<<"Player ";
    cout<<player_name;
    cout<<" ";
    cout<<doKTOr_level(game_id);
    cout<<"\n";
}
int Player::roll(Dice* dice) {
    return dice->diceRoll();
}
int Player::doKTOr_level(int game_id) {
    cout<<"doKTOr_level: ";

    return playerAttribute[gameIndexMap.at(game_id)].first;
}
void Player::joinNewGame(int game_id) {
    cout<<"joinNewGame\n";
    playerAttribute.push_back(std::make_pair(9, 0));
    cout<<game_id;
    gameIndexMap[game_id] = playerAttribute.size() - 1;
}
void Player::endGame(int game_id) {
    // Delete attribute connected with finished game.
    playerAttribute.erase(playerAttribute.begin() + gameIndexMap.at(game_id));
    // Delete hash.
    gameIndexMap.erase(game_id);
}

bool Player::needToWait(int game_id) {
    size_t index_game_id = gameIndexMap.at(game_id);
    if(playerAttribute[index_game_id].second == 0) return false;
    cout<<"Player need to wait with wait_time = "<<playerAttribute[index_game_id].second;
    playerAttribute[gameIndexMap.at(game_id)].second--;
    cout<<"\n";
    return true;
}


void Player::wait(int game_id, int time_to_wait) {
    // Time to wait +2.
    playerAttribute[gameIndexMap.at(game_id)].second += time_to_wait;
    cout<<"\n Player "<<player_name<<" need to wait "<<time_to_wait<<" turns.";
}
void Player::regenerate(int game_id) {
    // Time to wait +2.
    playerAttribute[gameIndexMap.at(game_id)]  .second += 2;
    // Regenerate:
    playerAttribute[gameIndexMap.at(game_id)].first++;

    // Print out information.
    cout<<"\n Player "<<player_name<<" are regenerating and need to wait 2 turns.\n";
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Common class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dice_name Common::chooseDice(){
    return dice_name::common;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Deteriorating class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dice_name Deteriorating::chooseDice() {
    return dice_name::deteriorating;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NormalMove class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision NormalMove::playerDecision(int game_id, int rolled_number) {
    // Check if doKTOr level is equal to 13.
    if(playerAttribute[game_id].first == 13){
        return player_decision::end_game;
    }
    else return player_decision::normal_move;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NormalMoveCommon class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision NormalMoveCommon::playerDecision(int game_id, int rolled_number) {
    // Check if doKTOr level is equal to 13.
    if(playerAttribute[game_id].first == 13){
        return player_decision::end_game;
    }
    else return player_decision::normal_move;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Random class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dice_name Random::chooseDice() {
    int k = distribution_player(generator_player);
    cout<<"Player ";
    cout<<player_name;
    cout<<"choose dice: ";
    switch (k) {
        case 0:
            cout<<"common\n";
            return dice_name::common;
        case 1:
            cout<<"deteriorating\n";
            return dice_name::deteriorating;
        case 2:
            cout<<"defective\n";
            return dice_name::defective;
    }
    throw logic_error("Error.");
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Wary class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wary::Wary(string _player_name): Player(std::move(_player_name)) {
    badLuck = 0;
}
dice_name Wary::chooseDice() {
    // Check if there is a regeneration field in the next six fields
    if(fieldsToRegenerationSquare) return  dice_name::defective;

    if(badLuck == 4) return dice_name::common;

    return dice_name::deteriorating;

}
player_decision Wary::playerDecision(int game_id, int rolled_number) {
    // Check if doKTOr level is equal to 13.
    if(playerAttribute[game_id].first == 13) {
        return player_decision::end_game;
    }
    else if(rolled_number == 6) {
        return player_decision::find_regenerate_square;
    } else return player_decision::normal_move;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Experimental class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision Experimental::playerDecision(int game_id, int rolled_number) {
     // Check if doKTOr level is equal to 13.
    if(playerAttribute[game_id].first == 13) {
        return player_decision::end_game;
    }
    else if(rolled_number == 6){
        return player_decision::find_regenerate_square;
    } else {
        return player_decision::normal_move;
    }
}