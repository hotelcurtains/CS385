#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cstdlib> // Needed for rand() and srand()
#include <chrono>
using namespace std;

static void swap(int array[], const int a, const int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

static void print_array(int array[], const int length){
    cout << "[ ";
    for (int i = 0; i < length-1; i++){
        cout << array[i] << ", ";
    }
    cout << array[length-1] << " ]" << endl;
}

static bool is_sorted(int array[], const int length){
    for (int i = 0; i < length-1; i++){
        if (array[i] > array[i+1]) return false;
    }
    return true;
}

// input: an array and its length
// output: print the sorted array
void coinflipsort(int array[], const int length){
    int swaps = 0;
    while (!is_sorted(array), length){
        for (int i = 0; i < length-1; i++)
            int swap = rand() % 2;
            swaps += swap;
            if (swap == 1) swap(array, i, i+1);
    }
    print_array(array, length);
    cout << "Swaps: " << swaps << endl;
}

int main(int argc, char * const argv[]) {
    int array[] = {78,15,23,2,97,85};
        
    auto start = high_resolution_clock::now();

    coinflipsort(array,6);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time: " << duration.count() << " microseconds" << endl;
}