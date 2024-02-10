#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <memory>
#include "dice.h"
#include "game.h"
#include "square.h"
#include "player.h"

int game_id = 0;

using namespace std;


int main(int argc, char** argv){
    try {
        // Check if the correct number of command-line arguments is provided.
        if (argc != 2){
            throw invalid_argument("Incorrect number of command-line arguments");
        }
        // Open the input file.
        ifstream input(argv[1]);

        // Check if the file is successfully opened.
        if(!input.is_open()){
            throw runtime_error("Error with opening a file.");
        }

        // Load the number of players.
        unsigned int playerNumber;
        input >> playerNumber;

        // Load the players into a vector.
        // vector<Player *> players;
        vector<std::unique_ptr<Player>> players;
        for (int i = 0; i < playerNumber; i++) {
            char playerType;
            string playerName;
            input >> playerType;
            input.ignore();

            getline(input, playerName);
            //Player *player;
            unique_ptr<Player> playerPtr;
            switch (playerType) {
                case 'L':
                    playerPtr = make_unique<Random>(playerName);
                    break;
                case 'T':
                    playerPtr =make_unique<Traditional>(playerName);
                    break;
                case 'E':
                    playerPtr = make_unique<Experimental>(playerName);
                    break;
                case 'R':
                    playerPtr = make_unique<Wary>(playerName);
                    break;
                case 'B':
                    playerPtr = make_unique<Blank>(playerName);
                    break;
                default:
                    throw domain_error("Incorrect player type.");
            }

            // Add player to the vector.
            //players.push_back(player);
            players.push_back(std::move(playerPtr));
        }

        // Load the number of squares.
        unsigned int squareNumber;
        input >> squareNumber;

        // Index of square Start
        int start_index;

        vector<Square *> squares;

        // Some parameters that need to be checked for every game.
        int number_of_start = 0;
        int number_of_end = 0;
        int number_of_regeneration = 0;

        // Load the squares.
        for (int i = 0; i < squareNumber; i++) {
            char squareType;
            input >> squareType;

            Square *square;
            switch (squareType) {
                case 'S':
                    number_of_start++;
                    start_index = i;
                    square = new Start();
                    break;
                case 'D':
                    number_of_end++;
                    square = new End();
                    break;
                case '.':
                     square = new Empty();
                     break;
                case 'R':
                     number_of_regeneration++;
                     square = new Regeneration();
                     break;
                case 'P':
                     input.ignore();
                     int number;
                     input >> number;
                     square = new MoveTo(number);
                     break;
                case 'O':
                     input.ignore();
                     int time;
                     input >> time;
                     if (time <= 0) throw invalid_argument("Incorrect parameters for Time square.");
                     square = new Waiting(time);
                     break;
                default:
                    throw domain_error("Incorrect square type.");
            }

            squares.push_back(square);
        }

        if(number_of_start != 1) throw logic_error("Incorrect number of Start square.");

        if(number_of_regeneration >= 4) throw logic_error("Incorrect number of Regeneration square.");

        if(number_of_end == 0) throw logic_error("Incorrect number of End square.");

        int _maxPlayerNumber = (squareNumber / 3 > 0) ? (squareNumber / 3) : 1;

        // Create a board
        Board *board = new Board(squares, _maxPlayerNumber, start_index);

        // Create a game.
        Game game(board, players, game_id);

        game.startGame();

        // Change game_id for next game.
        game_id++;

        // Cleanup: Destruct players
        players.clear();

        // Cleanup: Destruct squares
        for (Square *square: squares) {
            delete square;
        }
        squares.clear();

        // Cleanup: Destruct board
        delete board;

        // Close the file.
        input.close();

    } catch (const exception& e) {
        cerr << e.what() << "\n";
        return 1;
    }
    return 0;
}