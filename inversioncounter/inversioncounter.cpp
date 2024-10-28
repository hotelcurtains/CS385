/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Daniel Detore
 * Version     : 1.0
 * Date        : 11/2/2024
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time using two nested loops.
 */
long count_inversions_slow(int array[], int length) {
    long total = 0;
    for (int i = 0; i < length; i++){
        for (int j = i+1; j < length; j++){
            if (array[i] > array[j]) total++;
        }
    }
    return total;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    return 0;
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc < 1 || 2 < argc) {
        cout << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    } 
    if (strcmp(argv[1], "slow")){
        cout << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if (values.empty()) {
        cout << "Sequence of integers not received." << endl;
        return 1;
    }
    // TODO: produce output

    cout << "Number of inversions ";

    if(argc == 2){
        cout << "(slow): " << count_inversions_slow(&values[0], index) << endl;
    }

    return 0;
}
