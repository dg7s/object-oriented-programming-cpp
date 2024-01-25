#include "dice.h"
#include <iostream>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

//~~~~~~~~~~~~~~~
// Random
//~~~~~~~~~~~~~~~
default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
uniform_int_distribution<int> distribution(1,6);
uniform_int_distribution<int> distribution2(0,1);
uniform_int_distribution<int> distribution100(0,99);


// Common dice.
int CommonDice::diceRoll(){
    return distribution(generator); // Answer in {1,2,3,4,5,6}.
}

// Return 1 with prob 4/6 and 6 with prob 2/6.
int DefectiveDice::diceRoll(){
    int r = distribution(generator);

    if(r < 5) return 1;
    else return 6;
}

DeterioratingDice::DeterioratingDice(){
    // We draw a number that will deteriorate. 0 means "1",
    // 1 means "6".
    if(distribution2(generator) % 2 == 0) number = 1; // 1 will deteriorating.
    else number = 6; // 6 will deteriorating.

    // At the start all numbers {1,2,3,4,5,6} have the same prob 1/6.
    prob = 1.0 / 6.0;
}

DeterioratingDice::DeterioratingDice(int n){
    assert(n==1 || n==6);
    number = n;

    // At the start all numbers {1,2,3,4,5,6} have the same prob 1/6.
    prob = 1.0 / 6.0;
}

void DeterioratingDice::deteriorating(){
    prob += (0.5 - prob) / 2.0;
}

int DeterioratingDice::diceRoll(){
    double r = distribution100(generator);

    if(r < (prob * 100) ){
        int k = number;
        deteriorating(); // Number is deteriorating.
        return k;
    } else{
        return (distribution(generator) + number - 1) % 6 + 1; // This formula ensures that the result is different from number.
    }
}

void test_dice () {
    cout<<"Creating 3 different dices. \n";
    CommonDice c;
    DeterioratingDice d;
    DefectiveDice f;

    // Variables that will count how many times we roll properly number.
    int number1=0 ,number2=0 ,number3=0 ,number4=0 ,number5=0 ,number6=0;

    cout<<"100 rolls: \n";
    for(int i = 0; i < 100; i++){
        int k = d.diceRoll();
        cout<<k<<" ";
        switch (k) {
            case 1:
                number1++;
                break;
            case 2:
                number2++;
                break;
            case 3:
                number3++;
                break;
            case 4:
                number4++;
                break;
            case 5:
                number5++;
                break;
            case 6:
                number6++;
                break;
            default:
                cout<<"\n"<< k<<"wrong value"<<"\n";

        }
    }
    cout<<"\n";
    cout<<"The number 1 appeared "<< number1<<" times.\n";
    cout<<"The number 2 appeared "<< number2<<" times.\n";
    cout<<"The number 3 appeared "<< number3<<" times.\n";
    cout<<"The number 4 appeared "<< number4<<" times.\n";
    cout<<"The number 5 appeared "<< number5<<" times.\n";
    cout<<"The number 6 appeared "<< number6<<" times.\n";

}
