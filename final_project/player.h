#ifndef PLAYER_H
#define PLAYER_H

#include <unordered_map>
#include <utility>
#include <vector>
#include "square.h"
#include "dice.h"
#include "board.h"

class Square;
class Dice;
class Board;
enum class square_name;
enum class player_decision {normal_move, end_game, find_regenerate_square, wait};

struct PlayerAttribute {
    unsigned int waitingTime; // Should be greater than 0.
    uint8_t doKTOrLevel; // Should be from 9 to 13.
};


class Player {
    protected:
        string player_name;
        // Hash map
        std::unordered_map<int, PlayerAttribute> gameIndexMap;
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
        virtual dice_name chooseDiceWithFuture(vector<square_name> &future) {return chooseDice();};

        void endGame(int game_id);
        void regenerate(int game_id);
        void wait(int game_id, int time_to_wait);
        bool needToWait(int game_id);
        virtual bool needToKnowFuture() = 0;
        void joinNewGame(int game_id);

        // Getters.
        int doKTOr_level(int index_game_id);

        friend std::ostream& operator<<(std::ostream& os, const Player& p){
            os << "Player " << p.player_name;
        }

        // Print out methods
        void coutStatus(int game_id);
        void coutName();
};

// Choose only common dice.
class Common : public Player{
    public:
        explicit Common(string _player_name): Player(std::move(_player_name)){};
        dice_name chooseDice() override;
};

// Choose only deteriorating dice.
class Deteriorating : public Player{
    public:
            explicit Deteriorating(string _player_name): Player(std::move(_player_name)){};
            dice_name chooseDice() override;
};

// These two subclasses: NormalMove, NormalMoveCommon
// move by the number from the roll() method.
class NormalMove : public  Player{
    public:
        explicit NormalMove(string _player_name): Player(std::move(_player_name)){};
        player_decision playerDecision(int game_id, int rolled_number) override;
};

class NormalMoveCommon : public  Common{
    public:
        explicit NormalMoveCommon(string _player_name): Common(std::move(_player_name)){};
        player_decision playerDecision(int game_id, int rolled_number) override;

};

// Final subclasses used during the game.

class Random : public NormalMove {
    public:
        explicit Random(string _player_name): NormalMove(std::move(_player_name)){};
        dice_name chooseDice() override;
        bool needToKnowFuture() override;
};

class Traditional : public NormalMoveCommon {
    public:
        explicit Traditional(string _player_name): NormalMoveCommon(std::move(_player_name)){};
        bool needToKnowFuture() override;

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
        bool needToKnowFuture() override;
        dice_name chooseDiceWithFuture(vector<square_name> &future) override;
};

class Experimental : public Deteriorating {
    public:
        explicit Experimental(string _player_name): Deteriorating(std::move(_player_name)){};
        player_decision playerDecision(int game_id, int rolled_number) override;
        bool needToKnowFuture() override;
};

class Blank : public Player{
    public:
        explicit Blank(string _player_name): Player(std::move(_player_name)){};
        dice_name chooseDice() override;
        player_decision playerDecision(int game_id, int rolled_number) override;
        bool needToKnowFuture() override;
        dice_name chooseDiceWithFuture(vector<square_name> &future) override;
};

#endif // PLAYER_H
