#include <iostream>
#include <exception>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

// The Survey class provides functionality to add values, calculate statistics such as
// average, quartiles, and standard deviation, and connect surveys to combine data sets.
// It handles cases where the survey is empty and ensures proper error handling.

class Survey {
    public:
        // Default constructor
        Survey(): value() {};

        Survey(unsigned int _number_): value(_number_){};

        // Basic desctructor
        ~Survey() = default;

        // Copy constructor
        Survey(const Survey& u) = default;

        // Add new value (double) to Survey
        void add(double _value_){
            value.push_back(_value_);
        }

        // Return size of Survey
        int numSurvey() const{
            return value.size();
        }

        // Return average of elements in Survey
        double avg() const;


        // Return proper quartile: quartile(3);
        double quartile(int _number_) const;


        // Return standard deviation
        double std_dev() const;


        // Connects Survey p to Survey
        Survey& connect_surveys(const Survey& p){
            value.insert(value.end(), p.value.begin(), p.value.end());
            return *this;
        }

    private:
        // Vector for value that represents the set of measurements
        vector<double> value;
};

double Survey::avg() const{
    if(value.empty()){
        throw logic_error("Survey is empty, can't find average value");
    }
    //sum := sum of all elements in Survey
    double sum = 0.0;
    for(double i: value){
        sum += i;
    }

    return sum / value.size();
}

double Survey::quartile(int _number_) const{
    if(value.empty()){
        throw logic_error("Survey cannot be an empty set in quartile()");
    }

    // Make a copy of the vector before sorting
    vector<double> sortedValues = value;
    sort(sortedValues.begin(), sortedValues.end());

    // n := size of the vector
    size_t n = sortedValues.size();

    switch(_number_){
    case 2:
        return n % 2 == 0 ? (sortedValues[n - 1] + sortedValues[n]) / 2 : sortedValues[n - 1];
    case 1:
    {
        // mid := possition of middle element - last element of left half of array
        int mid = n / 2 - 1;
        return mid % 2 == 0 ? (sortedValues[mid - 1] + sortedValues[mid]) / 2 : sortedValues[mid - 1];
    }
    case 3:
    {
        int mid = n % 2 == 0 ? n / 2 : n / 2 + 1;
        return (n - mid) % 2 == 0 ? (sortedValues[(n + mid) / 2 - 1] + sortedValues[(n + mid) / 2]) / 2 : sortedValues[(n + mid) / 2];
    }
    case 4:
        return sortedValues[n - 1];
    default:
        throw logic_error("Value for quartile() must be in the {1, 2, 3, 4} set");
    }
}

double Survey::std_dev() const{
    if(value.empty()){
        throw logic_error("Survey cannot be an empty set in set_dev()");
    }

    // x:= avg value
    double x = avg();

    double sum = 0;
    for(double i : value){
        sum += (i - x) * (i - x);
    }

    sum /= (value.size() - 1);

    return sqrt(sum);
}


int main(){
    // Create instances of Survey
    Survey survey1;
    Survey survey2;
    Survey survey3;

    // Add values to surveys
    survey1.add(10.5);
    survey1.add(15.2);
    survey1.add(20.8);

    survey2.add(25.1);
    survey2.add(30.7);
    survey2.add(35.4);

    // Connect surveys
    survey1.connect_surveys(survey2);

    // Display the size of the combined survey
    cout << "Combined survey size: " << survey1.numSurvey() << "\n";

    // Calculate and display the average of values in the combined survey
    cout << "Average value in the combined survey: " << survey1.avg() << "\n";

    // Calculate and display the first quartile of values in the combined survey
    cout << "First quartile in the combined survey: " << survey1.quartile(1) << "\n";

    // Calculate and display the third quartile of values in the combined survey
    cout << "Third quartile in the combined survey: " << survey1.quartile(3) << "\n";

    // Calculate and display the standard deviation of values in the combined survey
    cout << "Standard deviation in the combined survey: " << survey1.std_dev() << "\n";

    cout<<"\n";

    // Calculate and display the average of values in the second survey
    cout << "Average value in the second survey: " << survey2.avg() << "\n";

    // Calculate and display the first quartile of values in the second survey
    cout << "First quartile in the second survey: " << survey2.quartile(1) << "\n";

    // Calculate and display the third quartile of values in the second survey
    cout << "Third quartile in the second survey: " << survey2.quartile(3) << "\n";

    // Calculate and display the standard deviation of values in the second survey
    cout << "Standard deviation in the second survey: " << survey2.std_dev() << "\n";

    return 0;
}
