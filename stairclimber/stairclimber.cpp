/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Daniel Detore
 * Date        : 10/5/2024
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    vector< vector<int> > ways;
    if (num_stairs <= 0) ways.push_back( {} );
    
    for (int i = 1; i < 4; i++){
        if (num_stairs >= i){
            vector< vector<int> > result = get_ways(num_stairs - i);
            // Prepending i to all the solutions in result:
            for (int j = 0; j < (int)result.size(); j++){
                result[j].insert(result[j].begin(), i);
                ways.push_back(result[j]);
            }
        }
    }
    return ways;
}

static void print_vector(vector<int> vector){
    int length = (int)vector.size();
    cout << "[";
    for (int i = 0; i < length-1; i++){
        cout << vector[i] << ", ";
    }
    cout << vector[length-1] << "]" << endl;
}

/* Returns how many digits are in an integer. */
int num_digits(int num) {
    int length = 0;
    while(num > 0){
        num /= 10;
        length++;
    }
    return length;
}

void display_ways(const vector< vector<int> > &ways) {
    // Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    int size = (int)(ways.size()),
        width = num_digits(size);

    for (int i = 0; i < size; i++){
        cout << setw(width) << i+1 << ". ";
        print_vector(ways[i]);
    }
}

int main(int argc, char * const argv[]) {
    if(argc != 2) {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }    

    int stairs = 0;
    istringstream iss;
    iss.clear();
    iss.str(argv[1]);
    if (!(iss >> stairs) || stairs < 0) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    vector< vector<int> > ways = get_ways(stairs);

    if (stairs == 1) cout << "1 way to climb 1 stair." << endl; 
    else cout << (int)ways.size() << " ways to climb " << stairs << " stairs." << endl;

    display_ways(ways);
    
    return 0;
}
