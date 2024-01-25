#include "square.h"
#include <iostream>
#include <unordered_map>
using namespace std;


// Hashmap which convert input format of player class name to enum square_name. For instance: S -> start_square
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
bool NotEnd::hypotheticalEnd(int &square_index) const {return true;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// HypotheticalActionIsNull class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool HypotheticalActionIsNull::hypotheticalAction(Player *player, int &square_index) const {return false;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ActionIsNull class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void ActionIsNull::action(Player *player, int &square_index) const {return;}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Start class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Start::name() const {cout<<"Start";}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Empty class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Empty::name() const {}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// End class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void End::name() const {}
void End::action(Player *player, int &square_index) const { return;}
bool End::hypotheticalEnd(int &square_index) const {return true;}
bool End::hypotheticalAction(Player *player, int &square_index) const {return false;}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Regeneration class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Regeneration::name() const {}
bool Regeneration::hypotheticalAction(Player *player, int &square_index) const {}
void Regeneration::action(Player *player, int &square_index) const {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Waiting class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void Waiting::name() const {}
void Waiting::action(Player *player, int &square_index) const {}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// MoveTo class methods
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
MoveTo::MoveTo(int k): square_number(k) {}

void MoveTo::name() const {}
void MoveTo::action(Player *player, int &square_index) const {}