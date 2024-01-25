#ifndef DICE_H
#define DICE_H
#include <iostream>

using namespace std;

enum class dice_name {common, defective, deteriorating};

class Dice {
public:
    // Constructor
    Dice() = default;
    // Basic destructor.
    virtual ~Dice() = default;

    // Copy constructor and assignment operator are deleted.
    Dice(const Dice& k) = delete;
    Dice& operator=(const Dice&) = delete;

    // Methods:
    virtual int diceRoll() = 0; // Virtual method to throw a dice.
};

class CommonDice : public Dice {
public:
    int diceRoll() override;
};

class DefectiveDice : public Dice {
public:
    int diceRoll() override;
};

class DeterioratingDice : public Dice {
private:
    int number; // Which number will deteriorate.
    float prob; // Probability of number above.
public:
    // Constructors. In second one we decide which number will
    // deteriorate (Only 1 and 6 are possible). Useful for testing.
    DeterioratingDice();
    explicit DeterioratingDice(int n);
    int diceRoll() override;
    void deteriorating();
};

void test_dice();

#endif // DICE_H

