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
    int* scratch = new int[length];
    long count = mergesort(array, scratch, 0, length-1);
    delete [] scratch;
    return count;
}

static long merge(int array[], int scratch[], int low, int mid, int high){ 
    int i1 = low, i2 = mid, i=low;
    long count = 0;
    while (i1 < mid && i2 <= high){
        if (array[i1] <= array[i2]){
            scratch[i] = array[i1];
            i++;
            i1++;
        }
        else{
            scratch[i] = array[i2];
            i++;
            i2++;
            count += mid - i1;
        }
    }
    while (i1 < mid){
        scratch[i] = array[i1];
        i++;
        i1++;
    }
    while (i2 <= high){
        scratch[i] = array[i2];
        i++;
        i2++;
    }
    for (int j = 0; j <= high; j++){
        array[j] = scratch[j];
    }
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0;
    if (low < high){
        int mid = low + (high-low)/2;
        count += mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);
        count += merge(array, scratch, low, mid + 1, high);
    }
    return count;
}



int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    if (argc < 1 || 2 < argc) {
        cout << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    } 
    char ok[] = "slow";
    if (argc == 2 && strcmp(argv[1], ok) != 0){
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
        cout << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    // TODO: produce output

    cout << "Number of inversions ";

    if(argc == 2){
        cout << "(slow): " << count_inversions_slow(&values[0], index) << endl;
    } else{
        cout << "(fast): " << count_inversions_fast(&values[0], index) << endl;
    }

    return 0;
}
