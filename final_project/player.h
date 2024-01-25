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
        explicit Player(string _player_name);
        // Basic destructor.
        virtual ~Player() = default;

        // Copy constructor and Assigment operator is deleted.
        Player(const Player& u) = delete;
        Player& operator=(const Player&) = delete;

        // Methods:
        virtual player_decision playerDecision(int game_id, int rolled_number) = 0;
        virtual int roll(Dice*);
        virtual dice_name chooseDice() = 0; // Choose dice to roll.
        void regenerate(int game_id);
        void wait(int game_id, int time_to_wait);
        bool needToWait(int game_id);

        // Getters.
        int doKTOr_level(int game_id);

        // Print out methods
        void coutName();
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
        player_decision playerDecision(int game_id, int rolled_number) override;
};

class NormalMoveCommon : public  Common{
public:
    player_decision playerDecision(int game_id, int rolled_number) override;

};

// Final subclasses used during the game.

class Random : public NormalMove {
    public:
        explicit Random(string _player_name);
        dice_name chooseDice() override;
};

class Traditional : public NormalMoveCommon {
    public:
        explicit Traditional(string _player_name);

};

// If he has a bad luck (4 times in a row he rolled a one) he choose Common dice
// instead of Deteriorating dice.
class Wary : public Player {
    private:
        int badLuck; // The number of turns in which a player rolled a one.

    public:
        explicit Wary(string _player_name);
        dice_name chooseDice() override;
        player_decision playerDecision(int game_id, int rolled_number) override;
};

class Experimental : public Deteriorating {
    public:
        explicit Experimental(string _player_name);
        player_decision playerDecision(int game_id, int rolled_number) override;
};

#endif // PLAYER_H
