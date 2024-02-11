#include "player.h"
#include <random>
#include <chrono>
#include <vector>
#include <limits>


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

void Player::coutName() {
    cout<<player_name;
}

void Player::coutStatus(int game_id) {
    cout<< *this;
    cout<<", doKTOr level: ";
    cout<<doKTOr_level(game_id);
}
int Player::roll(Dice* dice) {
    return dice->diceRoll();
}
int Player::doKTOr_level(int game_id) {
    return gameIndexMap[game_id].doKTOrLevel;
}
void Player::joinNewGame(int game_id) {
    PlayerAttribute object{};
    object.doKTOrLevel = 9;
    object.waitingTime = 0;
    gameIndexMap[game_id] = object;
}
void Player::endGame(int game_id) {
    // Delete hash.
    gameIndexMap.erase(game_id);
}

bool Player::needToWait(int game_id) {
    if(gameIndexMap[game_id].waitingTime == 0) return false;
    cout<<"Player need to wait with wait_time = "<<gameIndexMap[game_id].waitingTime;
    gameIndexMap[game_id].waitingTime--;
    cout<<"\n";
    return true;
}


void Player::wait(int game_id, int time_to_wait) {
    // Time to wait +2.
    gameIndexMap[game_id].waitingTime += time_to_wait;
    cout<<"\n"<< *this <<" need to wait "<<time_to_wait<<" turns.\n";
}
void Player::regenerate(int game_id) {
    // Time to wait +2.
    gameIndexMap[game_id].waitingTime += 2;
    // Regenerate:
    gameIndexMap[game_id].doKTOrLevel++;

    // Print out information.
    cout<<"\n"<< *this <<" are regenerating and need to wait 2 turns.\n";
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
    if(gameIndexMap[game_id].doKTOrLevel == 13){
        return player_decision::end_game;
    }
    else return player_decision::normal_move;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NormalMoveCommon class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision NormalMoveCommon::playerDecision(int game_id, int rolled_number) {
    // Check if doKTOr level is equal to 13.
    if(gameIndexMap[game_id].doKTOrLevel == 13){
        return player_decision::end_game;
    }
    else return player_decision::normal_move;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Traditional class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool Traditional::needToKnowFuture() {return false;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Random class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
dice_name Random::chooseDice() {
    int k = distribution_player(generator_player);
    cout<<player_name;
    cout<<" choose dice: ";
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
}
bool Random::needToKnowFuture() {return false;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Wary class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Wary::Wary(string _player_name): Player(std::move(_player_name)) {
    badLuck = 0;
}
dice_name Wary::chooseDiceWithFuture(vector<square_name> &future) {
    // Check if in the next 6 fields are a Regenerate square;
    for (const auto& element : future) {
        if (element == square_name::regeneration_square) return dice_name::defective;
    }
    return chooseDice();
}

dice_name Wary::chooseDice() {
    if(badLuck == 4) return dice_name::common;

    return dice_name::deteriorating;

}
player_decision Wary::playerDecision(int game_id, int rolled_number) {
    // Check if doKTOr level is equal to 13.
    if(gameIndexMap[game_id].doKTOrLevel == 13) {
        return player_decision::end_game;
    }
    else if(rolled_number == 6) {
        return player_decision::find_regenerate_square;
    } else return player_decision::normal_move;
}
bool Wary::needToKnowFuture() {return true;}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Experimental class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision Experimental::playerDecision(int game_id, int rolled_number) {
     // Check if doKTOr level is equal to 13.
    if(gameIndexMap[game_id].doKTOrLevel == 13) {
        return player_decision::end_game;
    }
    else if(rolled_number == 6){
        return player_decision::find_regenerate_square;
    } else {
        return player_decision::normal_move;
    }
}
bool Experimental::needToKnowFuture() {return false;}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Blank class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
player_decision Blank::playerDecision(int game_id, int rolled_number) {
    // Check if doKTOr level is equal to 13.
    if(gameIndexMap[game_id].doKTOrLevel == 13) {
        return player_decision::end_game;
    }
    else if(rolled_number == 6){
        cout << "\nDo you want to stop at the nearest regeneration field if it's on the way?\n";
        cout << "Type Y/N: ";
        char answer;
        cin >> answer;
        if (answer == 'Y') {
            cout<<"I am looking for a field of regeneration.\n";
            return player_decision::find_regenerate_square;
        } else {
            cout<<"I move six squares.\n";
            return player_decision::normal_move;
        }
    } else {
        return player_decision::normal_move;
    }
}
bool Blank::needToKnowFuture() {return true;}
dice_name Blank::chooseDiceWithFuture(vector<square_name> &future) {
    cout<<"The next six fields: ";
    for (const auto& element : future) {
        switch(element) {
            case square_name::regeneration_square:
                cout<<" R ";
                break;
            case square_name::start_square:
                cout<<" S ";
                break;
            case square_name::end_square:
                cout<<" D ";
                break;
            case square_name::empty_square:
                cout<<" . ";
                break;
            case square_name::move_to_square:
                cout<<" P ";
                break;
            case square_name::waiting_square:
                cout<<" O ";
                break;
        }
    }
    cout<<"\n";
    this->chooseDice();
}
dice_name Blank::chooseDice() {
    cout<<"Choose a Dice to roll:\n";
    cout<<"Type 1 to choose common dice.\n";
    cout<<"Type 2 to choose defective dice.\n";
    cout<<"Type 3 to choose deteriorating dice.\n";

    int dice_number;

    if (!(cin >> dice_number)) {
        cout << "Incorrect input. Please enter a valid number.\n";
        cin.clear();  // Resets error flag.
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore end line.
        return this->chooseDice();
    }

    switch(dice_number) {
        case 1:
            return dice_name::common;
        case 2:
            return dice_name::defective;
        case 3:
            return dice_name::deteriorating;
        default:
            cout << "Incorrect dice name.\n";
            return this->chooseDice();
    }
}