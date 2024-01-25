#include "player.h"
#include "square.h"
#include <cstdlib>
#include <cassert>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Base class methods (Players)
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Player::Player(string _player_name): player_name(_player_name) {}


int Player::roll(Dice* dice) {
    return dice->diceRoll();
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
player_decision NormalMove::playerDecision(int game_id) {
    // Check if player need to wait.
    if(playerAttribute[game_id].second > 0){
        playerAttribute[game_id].second--;
        return player_decision::wait;
    }
    // Check if doKTOr level is equal to 13.
    else if(playerAttribute[game_id].first == 13){
        return player_decision::end_game;
    }
    else return player_decision::normal_move;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NormalMoveCommon class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision NormalMoveCommon::playerDecision(int game_id) {
    // Check if player need to wait.
    if(playerAttribute[game_id].second > 0){
        playerAttribute[game_id].second--;
        return player_decision::wait;
    }
        // Check if doKTOr level is equal to 13.
    else if(playerAttribute[game_id].first == 13){
        return player_decision::end_game;
    }
    else return player_decision::normal_move;
}



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Random class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dice_name Random::chooseDice() {
    int k = rand() % 3;
    switch (k) {
        case 0:
            return dice_name::common;
        case 1:
            return dice_name::deteriorating;
        case 2:
            return dice_name::defective;
        
    }
}
void Random::playerAction(int k){

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Traditional class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Traditional::playerAction() {

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Wary class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wary::Wary(): Player() {
    badLuck = 0;
}
dice_name Wary::chooseDice() {
    if(badLuck == 4) return dice_name::common;

    return dice_name::deteriorating;

}
player_decision Wary::playerDecision(int game_id) {
    // Check if player need to wait.
    if(playerAttribute[game_id].second > 0){
        playerAttribute[game_id].second--;
        return player_decision::wait;
    }
    // Check if doKTOr level is equal to 13.
    else if(playerAttribute[game_id].first == 13) {
        return player_decision::end_game;
    }
    else return player_decision::find_regenerate_square;
}
void Wary::playerAction(int k) {

}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Experimental class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision Experimental::playerDecision(int game_id) {
    // Check if player need to wait.
    if(playerAttribute[game_id].second > 0){
        playerAttribute[game_id].second--;
        return player_decision::wait;
    }
        // Check if doKTOr level is equal to 13.
    else if(playerAttribute[game_id].first == 13) {
        return player_decision::end_game;
    }
    else return player_decision::find_regenerate_square;
}

void Experimental::playerAction() {

}