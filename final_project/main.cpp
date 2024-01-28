#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
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
    cout<<"playerNumber"<<playerNumber<<"\n";


    // Load the players into a vector.
    vector<Player*> players;
    for(int i = 0; i < playerNumber; i++){
        char playerType;
        string playerName;
        cout<<"Petla "<<i<<"\n";
        input >> playerType;
        input.ignore();

        getline(input, playerName);
        cout<<"Gracz typu: "<<playerName<<"\n";
        Player* player;
        switch (playerType) {
            case 'L':
                player = new Random(playerName);
                break;
            case 'T':
                player = new Traditional(playerName);
                break;
            case 'E':
                player = new Experimental(playerName);
                break;
            case 'R':
                player = new Wary(playerName);
                break;
            default:
                throw logic_error("Incorrect player type.");
        }

        // Add player to the vector.
        players.push_back(player);
    }

    // Load the number of squares.
    unsigned int squareNumber;
    input >> squareNumber;
    cout<<"SquareNumber"<<squareNumber<<"\n";

    // Index of square Start
    int start_index;

    vector<Square*> squares;

    // Some parameters that need to be checked for every game.
    int number_of_start = 0;
    int number_of_end = 0;
    int number_of_regeneration = 0;

    // Load the squares.
    for(int i = 0; i < squareNumber; i++){
        cout<<"Petla "<<i<<"\n";
        char squareType;
        input >> squareType;

        Square* square;
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
                    int number;
                    input >> number;
                    square = new MoveTo(number);
                    break;
                case 'O':
                    int time;
                    input >> time;
                    if(time <= 0) throw logic_error("Incorrect parameters for square.");
                    square = new Waiting(time);
                    break;
                default:
                    throw logic_error("Incorrect square type.");
            }

            squares.push_back(square);
    }
    if(number_of_start != 1 || number_of_regeneration >= 4 || number_of_end == 0) {
        throw logic_error("Incorrect number of squares.");
    }

    int _maxPlayerNumber = (squareNumber / 4 > 0) ? (squareNumber / 4) : 1;

    // Create a board
    Board* board = new Board(squares, _maxPlayerNumber, start_index);

    // Create dices.
    CommonDice* common = new CommonDice();
    DefectiveDice* defective = new DefectiveDice();
    DeterioratingDice* deteriorating = new DeterioratingDice();

    // Create a game.
    Game game(board, players, common, deteriorating, defective, game_id);

    game.startGame();

    // Change game_id for next game.
    game_id++;

    // Cleanup: Destruct players
    for (Player* player : players) {
        delete player;
    }

    // Cleanup: Destruct squares
    for (Square* square : squares) {
        delete square;
    }

    // Cleanup: Destruct board
    delete board;

    // Cleanup: Destruct dices
    delete common;
    delete defective;
    delete deteriorating;

    // Close the file.
    input.close();

    } catch (const exception& e) {
        cerr << e.what() << "\n";
        return 1;
    } catch (const out_of_range& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}


return 0;
}
