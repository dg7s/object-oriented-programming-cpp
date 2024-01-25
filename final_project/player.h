#ifndef PLAYER_H
#define PLAYER_H
#include "square.h"
#include "dice.h"
#include "board.h"

enum class player_decision {normal_move, end_game, find_regenerate_square, wait};


class Player {
    protected:
        string player_name;
        // In vector below we keep information about doKOTr level and time player need to wait
        vector <pair<int,int>> playerAttribute;
    public:
        // Constructor
        Player(string _player_name);
        // Basic destructor.
        virtual ~Player() = default;

        // Copy constructor and Assigment operator is deleted.
        Player(const Player& u) = delete;
        Player& operator=(const Player&) = delete;

        // Methods:
        virtual player_decision playerDecision(int game_id) = 0;
        void moveTo(Square*); // Set new place.
        virtual int roll(Dice*);
        virtual bool playerAction(int k) = 0; // Make a move.
        //virtual int choosePoints(int k) = 0; // Decide how far he wants to move.
        virtual dice_name chooseDice() = 0; // Choose dice to roll.

        // Print out methods
        void coutName();
        void coutPlace();
};

// Choose only common dice.
class Common : public Player{
    public:
        dice_name chooseDice() override;
};

// Choose only deteriorating dice.
class Deteriorating : public Player{
public:
        dice_name chooseDice() override;
};

// These two subclasses: ConstPoints, ConstPointsCommon
// move by the number from the roll() method.
class NormalMove : public  Player{
    public:
        player_decision playerDecision(int k) override;
};

class NormalMoveCommon : public  Common{
public:
    player_decision playerDecision(int k) override;

};

// Final subclasses used during the game.

class Random : public NormalMove {
    public:
        dice_name chooseDice() override;
        bool playerAction(int k) override;

};

class Traditional : public NormalMoveCommon {
    public:
        bool playerAction(int k) override;
};

// If he has a bad luck (4 times in a row he rolled a one) he choose Common dice
// instead of Deteriorating dice.
class Wary : public Player {
    private:
        int badLuck; // The number of turns in which a player rolled a one.

    public:
        Wary();
        dice_name chooseDice() override;
        player_decision playerDecision(int game_id) override;
        bool playerAction(int k) override;
};

class Experimental : public Deteriorating {
    public:
        player_decision playerDecision(int game_id) override;
        bool playerAction(int k) override;
};

#endif // PLAYER_H
