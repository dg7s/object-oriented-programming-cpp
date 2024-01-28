#include "square.h"
#include <iostream>
#include <unordered_map>
using namespace std;


// Hashmap which convert input format of player class name to enum square_name. For instance: S -> start_square.
unordered_map <char, square_name> player_hashmap = {
        {'S', square_name::start_square},
        {'D', square_name::end_square},
        {'.', square_name::empty_square},
        {'R', square_name::regeneration_square},
        {'P', square_name::move_to_square},
        {'O', square_name::waiting_square}

};
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// NotEnd class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool NotEnd::hypotheticalEnd(int &square_index, const int game_id) const {return true;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HypotheticalActionIsNull class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool HypotheticalActionIsNull::hypotheticalAction(Player *player, const int game_id) const {return false;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ActionIsNull class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ActionIsNull::action(Player *player, int &square_index, const int game_id) const {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Start class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Start::name() const {cout<<"Start";}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Empty class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Empty::name() const {cout<<"Empty";}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void End::name() const {cout<<"End";}
void End::action(Player *player, int &square_index, const int game_id) const {}
bool End::hypotheticalEnd(int &square_index, const int game_id) const {return true;}
bool End::hypotheticalAction(Player *player, const int game_id) const {return false;}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Regeneration class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Regeneration::name() const {cout<<"Regenerate";}
bool Regeneration::hypotheticalAction(Player *player,const int game_id) const {
    if(player->doKTOr_level(game_id) == 13) return false;
    return true;
}
void Regeneration::action(Player *player, int &square_index, const int game_id) const {
    // Method print put all the information.
    player->regenerate(game_id);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Waiting class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Initialize the same time for all doKTOr levels.
Waiting::Waiting(int time) {
    for(int i =0; i < 5; i++){
        time_to_wait.push_back(time);
    }
}
// For each doKTOr level initialize appropriate time.
Waiting::Waiting(const vector<int> &k) {
    // Check if vector k has size 5.
    if(k.size() != 5) throw logic_error("Wrong data for Waiting Square constructor.");
    for(int element : k){
        time_to_wait.push_back(element);
    }
}
void Waiting::name() const {cout<<"Wait";}
void Waiting::action(Player *player, int &square_index,const int game_id) const {
    // We give player vector with information how long he had to wait.
    int doKTOr_level = player->doKTOr_level(game_id);
    int time = time_to_wait[ (doKTOr_level - 9) ];

    // Method wait print out information.
    player->wait(game_id,time);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MoveTo class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MoveTo::MoveTo(int k): jump_length(k) {}
void MoveTo::name() const {cout<<"Move To";}
void MoveTo::action(Player *player, int &square_index,const int game_id) const {
    square_index = (square_index + jump_length);
    cout<<"\n Player jumped "<<jump_length<<" squares.\n";
}