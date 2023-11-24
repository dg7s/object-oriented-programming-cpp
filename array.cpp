#include <iostream>
#include <algorithm>
#include <array>

using namespace std;


// Task 2: Write a function that mirrors a subarray in the range p to k.

int arr_lustro[6] = {0,1,2,3,4,5};

void lustro1(int tab[], int p, int k)
{
    k--;
    for(; p<k; p++,k--)
    {
        int pom =tab[p];
        tab[p] = tab[k];
        tab[k] = pom;
    }
}

void lustro2(int* tab, int p, int k)
{
    k--;
    for(; p<k; p++,k--)
    {
        int pom = *(tab + p);
        *(tab+p) = *(tab+k);
        *(tab+k) = pom;
    }
}


void lustro3(int* p, int* k)
{
    k--;
    for(; p<k; p++, k--)
    {
        int pom = *p;
        *p = *k;
        *k = pom;
    }

}

void lustro4(int tab[], int p, int k)
{
    k--;
    for(; p<k; p++,k--)
    {
        swap(tab[p], tab[k]);
    }
}

// Task 3 (using <array> library)

array<int,10> arithmetic = {1,3,5,7,9,11,13,15,17,19};
array<int,10> not_arithmetic = {1,3,5,7,9,11,13,14,17,19};

bool is_arithmetic_sequence(const array<int, 10>& arr)  //const is used here to prevent the compiler from making a copy of the array
{
    if(arr.size() > 0)
    {
        int pom = arr[1] - arr[0];

        for(int i=1; i < arr.size(); i++)
        {
            if(arr[i] - arr[i-1] != pom) return false;
        }
        return true;
    }

    return false;
}

array<int,10> sum1 = {0,5,1,10,0,2,6,10,10, 9}; // unique_sum = 23

int sum_uniqe_elemnts(array<int,10>& arr)
{
    sort(arr.begin(), arr.end());

    int sum = 0;
    int repeated_elem = arr.front() - 1; // keep the last element that was repeated during iteration.

    for(int i=0; i<arr.size()-1; i++) // Comparing all elements despite the last one.
    {

        if(arr[i] != repeated_elem && arr[i] != arr[i+1])
        {
            sum += arr[i];
        }
        else
        {
            repeated_elem = arr[i];
        }
    }

    if(arr.back() != repeated_elem) sum += arr.back(); // Checking if last element is uniqe.

    return sum;
}

int main()
{

// Visualization of task 2.

//lustro1(arr_lustro, 1,5);
//lustro2(arr_lustro, 1,5);
//lustro3(&arr_lustro[1], &arr_lustro[5]);
//lustro4(arr_lustro, 1, 5);

//for(int i=0; i<6; i++){
//    cout<<arr_lustro[i]<<" ";
//}

// Visualization of task 3

    cout<<"Arithmetic sequence: "<<is_arithmetic_sequence(arithmetic)<<", "<<"not arithmetic sequence: "<<is_arithmetic_sequence(not_arithmetic)<<"\n";

    cout<<sum_uniqe_elemnts(sum1);
    return 0;
}
