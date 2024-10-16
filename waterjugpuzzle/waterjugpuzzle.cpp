/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Daniel Detore, Anthony Santilli
 * Date        : 10/19/2024
 * Description : Complete the water jug puzzle given capacities and goal state.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void solve(int capacity[], int goal[]){
    cout << "No solution." << endl;
}


int main(int argc, char * const argv[]) {
    if (argc != 7){
        cout << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }

    int capacity[3] = {0};
    int goal[3] = {0};
    
    // input handling
    // check all capacities for validity
    for (int i = 0; i < 3; i++){
        stringstream iss;
        iss.clear();
        iss.str(argv[i+1]);
        if (!(iss >> capacity[i]) || capacity[i] <= 0) {
            cout << "Error: Invalid capacity '" << argv[i+1] << "' for jug " << (char)(65+i) << "." << endl;
            return 1;
        }
    }
    // check all goals for validity
    for (int i = 0; i < 3; i++){
        stringstream iss;
        iss.clear();
        iss.str(argv[i+4]);
        if (!(iss >> goal[i]) || goal[i] < 0) {
            cout << "Error: Invalid goal '" << argv[i+4] << "' for jug " << (char)(65+i) << "." << endl;
            return 1;
        }
    }
    // check that goals are possible per jug
    for (int i = 0; i < 3; i++){
        if (goal[i] > capacity[i]){
            cout << "Error: Goal cannot exceed capacity of jug " << (char)(65+i) << "." << endl;
            return 1;
        }
    }
    // check that goals are possible given capacity of C
    if(goal[0] + goal[1] + goal[2] != capacity[2]){
        cout << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    // actual solving
    solve(capacity, goal);

    

    return 0;

}
