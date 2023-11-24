#include <iostream>
#include <exception>

using namespace std;

//Implement a Time class whose objects represent hours and minutes

class Time {
    public:
        Time(): hour(0), minute(0) {};

        Time(uint8_t _hour_, uint8_t _minute_){
            if(_hour_ < 0 ||  _hour_  > 24){
                throw("Error: Hour variable must be >= 0 and <= 24");
            }else
            if(_minute_ < 0 || _minute_ > 60){
                throw("Error: Minute variable must be >= 0 and <= 60");
            }
            hour = _hour_;
            minute = _minute_;
        };
        //destructor
        ~Time()=default;

        //copy constructor
        Time(const Time& t) = default;
        Time& operator=(const Time& t) = default;

        //getter
        uint8_t getHour() const {
            return hour;
        }
        uint8_t getMinute() const {
            return minute;
        }


        void print24(); // prints the time in 24 format

        void print12(); // print the time in 12 format

        Time& add(int extra_hours, int extra_minutes); // advances the time by a given number of hours and minutes

        int how_long(const Time& c); //returns the number of minutes untill the given time

    private:
        uint8_t hour;
        uint8_t minute;
        void reduce();

};

void Time::print24(){ //Format 05:02
    cout<<hour/10<<hour%10<<":"<<minute/10<<minute%10<<"\n";
}

void Time::print12(){ //Format 01:39 PM
    if(hour>12){
        cout<<(hour-12)/10<<(hour-12)%10<<":"<<minute/10<<minute%10<<" PM"<<"\n";
    }
    else{
        cout<<hour/10<<hour%10<<":"<<minute/10<<minute%10<<" AM"<<"\n";
    }
}

Time& Time::add(int extra_hours, int extra_minutes){
    hour = ((hour + extra_hours) + (minute + extra_minutes)/60)%24;
    minute = (minute + extra_minutes)%60;

    return *this;
}

int Time::how_long(const Time& c){
    int x = c.hour*60 + c.minute - hour*60 - minute;

    if(x < 0) return (24*60 + x);
    return x;
}

int main(){
    Time t(16,58);
    t.print24();
    t.print12();
    t.add(2312,32642);
    t.print24();
    Time u(16,00);
    cout<<t.how_long(u);

return 0;
}
