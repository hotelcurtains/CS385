/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Daniel Detore
 * Date        : 9/28/2024
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

// Returns true if all characters in string are lowercase
// letters in the English alphabet; false otherwise.
bool is_all_lowercase(const string &s) {
    int i = 0;
    // while we're not looking at the null terminator...
    while (s[i] != 0){
        // if s[i] is outside of this range of ASCII characaters, 
        // s[i] is not a lowercase letter, so we return false.
        if (s[i] < 'a' || 'z' < s[i] ) return 0;
        i++;
    }
    // if we get here then we never saw an uppercase letter.
    return 1;
}

// Returns true if all letters in string are unique, that is
// no duplicates are found; false otherwise.
bool all_unique_letters(const string &s) {
    // You MUST use only single unsigned integers and work with bitwise
    // and bitshifting operators only.  Using any other kind of solution
    // will automatically result in a grade of ZERO for the whole assignment.

    unsigned int vector = 0;

    int i = 0;
    while (s[i] != 0){
        unsigned int setter = 1 << (s[i] - 'a');
        if ((vector & setter) > 0) return 0;
        vector = vector | setter;
        i++;
    }

    return 1;
}

// Reads and parses command line arguments.
// Calls other functions to produce correct output.
int main(int argc, char * const argv[]) {

    if(argc != 2) {
        cout << "Usage: ./unique <string>" << endl;
        return 1;
    } else if (!is_all_lowercase(argv[1])) {
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    } else if (all_unique_letters(argv[1])){
        cout << "All letters are unique." << endl;
    } else {
        cout << "Duplicate letters found." << endl;
    }
    
    return 0;
}
