#include <iostream>
#include <exception>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

class Fraction {
	public:
		Fraction(): numerator(0), denominator(1) {};

		Fraction(int _numerator_, int _denominator_): numerator(_numerator_) {
                if(_denominator_ == 0){
                    //exception
                    throw logic_error("U can't divide by 0");
                }
                else{
                    denominator = _denominator_;
                }
			};

			//basic destructor
			~Fraction() = default;

			//copy contructor
			Fraction(const Fraction& u) = default;
			Fraction& operator=(const Fraction& u) = default;

			//getter to numerator
			int getNumerator() const {
				return numerator;
			}

			//setter
			void setNumerator(int _numerator) {
				numerator = _numerator;
			}

			void print_fract();

			Fraction add(const Fraction& u) const {
				return(Fraction(numerator*u.denominator + u.numerator*denominator,
						denominator*u.denominator));
			}

			//add +=
			Fraction& add_assing(const Fraction& u) {
				numerator = numerator*u.denominator + u.numerator*denominator;
				denominator = denominator*u.denominator;
				return *this;
			}
			//reverse of the fraction
			Fraction& rev(){
			int tempt = numerator;
			numerator = denominator;
			denominator = tempt;
			}
	private:
		int numerator;
		int denominator;
		void reduce();

};

void Fraction::print_fract() {
    reduce();
	cout<<numerator<<"/"<<denominator<<"\n";
}

void Fraction::reduce() {
    int gcd = __gcd(numerator, denominator);
    numerator = numerator/gcd;
    denominator = denominator/gcd;
}


int main(){

	Fraction u1(9,6);
	u1.print_fract();
	u1.rev();
	u1.print_fract();


return 0;
}
