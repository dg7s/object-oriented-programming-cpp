#include <iostream>
#include <list>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Square hierarchy.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Square {
    public:
        // Constructors.
        Square() = default;

        // Destructor.
        ~Square() = default;

        // Copy constructor and Assigment operator is deleted.
        Square(const Square& s) = delete;
        Square& operator=(const Square&) = delete;

        // Methods:
        virtual void action() const = 0; // Make action during player move
        virtual void name() const = 0; // Print out its' name.
};

// Square from where players start game. Only one per board. During game does nothing.
class Start : public Square {
    public:
        void action() const override;
        void name() const override;
};

// Nothing happens.
class Empty : public Square {
    public:
        void action() const override;
        void name() const override;
};

// Square where players end a game.
class End : public Square {
    public:
        void action() const override;
        void name() const override;
};

// DokTOr atribute increase.
class Regeneration : public Square {
    public:
        void action() const override;
        void name() const override;
};

// Player need to wait a few queues.
class Waiting : public Square {
    public:
        void action() const override;
        void name() const override;
};

// Move player to proper square.
class MoveTo : public Square {
    private:
        int square_number;
    public:
        MoveTo() = delete;
        MoveTo(int k);
        void action() const override;
        void name() const override;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Dice - hierarchy.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Dice {
    public:
        // Constructor
        Dice() = default;
        // Basic destructor.
        virtual ~Dice() = default;

        // Copy constructor and assigment operator are deleted.
        Dice(const Dice& k) = delete;
        Dice& operator=(const Dice&) = delete;

        // Methods:
        virtual int diceThrow() = 0; // Virtual method to throw a dice.
};

class CommonDice : public Dice {
    public:
        int diceThrow() override;
};

class DefectiveDice : public Dice {
    public:
        int diceThrow() override;
};

class ConsumableDice : public Dice {
    private:
        bool number; // 0 := (prob of 1 increase) , 1:= (prob of 6 increase).
        float prob; // Probability of number above.
    public:
        ConsumableDice();
        int diceThrow() override;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Player - hierarchy.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Player {
    protected:
        int DokTOr_level;
        int waiting_time;
        Square* place; // Pointer to proper place on the board.
    public:
        // Constructor
        Player() = delete;
        Player(int _DokTOr_level, int _waiting_time, Square* _place);

        // Basic destructor.
        virtual ~Player() = default;

        // Copy constructor and Assigment operator is deleted.
        Player(const Player& u) = delete;
        Player& operator=(const Player&) = delete;

        // Methods:
        virtual int playerThrow() = 0; // Return number of final move.
        virtual void playerAction() = 0; // Make a move.
};

// Method playerThrow() is equal number on dice.
class ConstAction : public Player {
    public:
        int playerThrow() override;
};

class Random : public ConstAction {
    public:
        void playerAction() override;
};

class Traditional : public ConstAction {
    public:
        void playerAction() override;
};

class Wary : public Player {
    private:
        int badLuck; // The number of turns in which a player rolled a one.

    public:
        Wary();
        int playerThrow() override;
        void playerAction() override;
};

class Experimetnal : public Player {
    public:
        int playerThrow() override;
        void playerAction() override;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Declaration of Game class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Game;


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Board class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Board {
    private:
        list<Square*> boardList; // Linked list of Squares. We need to create a cycle.
        Square* start; // Pointer to start square.
        int boardSize; // Number of squars.
        int maxPlayerNumber; // Max avaible number of players on the board.

    public:
        // Constructors
        Board() = delete;
        Board(int _boardSize);
        Board(list<Square*>);

        // Destructor
        ~Board() = default;

        // Copy constructor and Assigment operator is deleted.
        Board(const Board& b) = delete;
        Board& operator=(const Board&) = delete;

        // Methods
        void addSquare(Square* square); // Add to list next square if possible.

        // Getters
        Square* returnStart(); // Returns a pointer to Start Square.
        Square* playerSquare(Game*, Player*, int k); // Returns a pointer to a Square k away from the Player in the Game.
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Game class.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Game {
    private:
        int playersNumber; // Number of players in the game.
        int turnsNumber; // Number of already played turns.
        bool isStarted; // True - game is on, False := game hasn't started.
        Board* board; // Pointer to the board.
        Player** players; // Array of pointers to the players.

    public:
        // Constructors
        Game() = delete;
        Game(int _playersNumber, Board* _board);

        // Destructor
        ~Game();

        // Copy constructor and Assigment operator is deleted.
        Game(const Game& g) = delete;
        Game& operator=(const Game&) = delete;

        // Methods
        void addPlayer(Player* player); // Add player to the game. Possible only before start of the game.
        void tour(); // Make all moves in current tour.
        void finish(); // End the game and print out the results;
};

int main(){
return 0;
}
