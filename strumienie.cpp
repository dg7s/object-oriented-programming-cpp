#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

int main(int argc, char **argv) {
    vector<int> liczby;
    ifstream f(argv[1]);
    int a;
    // string s;
    // wczytanie linijki
    // while (getline(f, s))) {
    //wczytywanie kolejnych liczb
    while (f >> a) {
        liczby.push_back(a+10);
    }
    ofstream of(argv[2]);
    for (auto v: liczby) {
        of << v <<" ";
    }
    of <<"\n";

    int i = atoi(argv[3]);
    cout <<i <<"\n";

}
