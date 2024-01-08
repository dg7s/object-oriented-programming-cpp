#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Kostka {
protected:

public:
    virtual int rzut() = 0; // Virtual method to throw a dice
};

class ZwyklaKostka : public Kostka {
public:
    int rzut() override {
        return rand() % 6 + 1;
    }
};

class ZuzywajacaSieKostka : public Kostka {

};

class WadliwaKostka : public Kostka {


};





int main(){

return 0;
}
