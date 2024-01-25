#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "dice.h"
#include "game.h"
#include "square.h"
#include "player.h"

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
    vector<Player*> players;
    for(int i = 0; i < playerNumber; i++){
        char playerType;
        string playerName;

        // Wczytaj dane gracza z pliku
        input >> playerType >> playerName;
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

        // Dodaj gracza do wektora
        players.push_back(player);
    }

    // Load the number of squares.
    unsigned int squareNumber;
    input >> squareNumber;

    // Load the squares.
    for(int i = 0; i < squareNumber; i++){
        // Some parameters that need to be checked for every game.
        int number_of_start, number_of_regeneration;

        // Index of square Start
        int start_index;
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
        if(number_of_start > 1 || number_of_start == 0 || number_of_regeneration >= 4)
            throw logic_error("Incorrect data.");

    }

    // Close the file.
    input.close();

    } catch (const exception& e) {
        cerr << e.what() << "\n";
        return 1;
    }


test_dice();

return 0;
}
