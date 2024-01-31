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

enum class player_decision {normal_move, end_game, find_regenerate_square, wait};


class Player {
    protected:
        string player_name;
        // In vector below we keep game_id and information about doKOTr level and time player need to wait
        std::vector <std::pair<int,int>> playerAttribute;
        // Hash map
        std::unordered_map<int, size_t> gameIndexMap;
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

        void endGame(int game_id);
        void regenerate(int game_id);
        void wait(int game_id, int time_to_wait);
        bool needToWait(int game_id);

        void joinNewGame(int game_id);

        // Getters.
        int doKTOr_level(int index_game_id);

        // Print out methods
        void coutStatus(int game_id);
        void const coutName();
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

// These two subclasses: ConstPoints, ConstPointsCommon
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
};

class Traditional : public NormalMoveCommon {
    public:
        explicit Traditional(string _player_name): NormalMoveCommon(std::move(_player_name)){};

};

// If he has a bad luck (4 times in a row he rolled a one) he choose Common dice
// instead of Deteriorating dice.
class Wary : public Player {
    private:
        int badLuck; // The number of turns in which a player rolled a one.
        bool fieldsToRegenerationSquare; // True if there is a regeneration field in the next six fields.

    public:
        explicit Wary(string _player_name);
        dice_name chooseDice() override;
        player_decision playerDecision(int game_id, int rolled_number) override;
};

class Experimental : public Deteriorating {
    public:
        explicit Experimental(string _player_name): Deteriorating(std::move(_player_name)){};
        player_decision playerDecision(int game_id, int rolled_number) override;
};

#endif // PLAYER_H
