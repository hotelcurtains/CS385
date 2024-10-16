/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Daniel Detore, Anthony Santilli
 * Date        : 10/19/2024
 * Description : Complete the water jug puzzle given capacities and goal state.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    // for the root with no parent node
    State(int _a, int _b, int _c, string _directions) :
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }

    // for all other nodes with parent nodes
    State(int _a, int _b, int _c, State *_parent) : 
        a{_a}, b{_b}, c{_c}, parent{_parent}, parent{_parent} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }

    // lets us check aimply if the states are the same
    bool operator== (const Struct &o) {
        return (a == o.a && b == o.b && c == o.c);
    }
};

// returns true if vector contains a, returns false otherwise.
bool in(State a, vector<State> vector){
    for (const auto &state : vector){
        if (a = state) return true;
    }
    return false;
}

void solve(int capacity[], int goal[]){

    State win(goal[0], goal[1], goal[2], "__");

    vector<State> seen;

    queue<State> q;
    q.push(State(capacity[0], capacity[1], capacity[2], "Initial state."));

    while(!(q.empty())){
        State current = q.front();
        q.pop();
        if (current == win){
            cout << current << endl; //return backtracked solution
        }
        if (in(current, seen)){
            continue;
        }
        seen.push_back(current);
        // try the 6 ways to pour water, pushing new States to the queue
        if(current.c != 0 && current.a != capacity[0]){ // C -> A
            //q.push(State());
        }
        if(){ // B -> A

        }
        if(){ // C -> B

        }
        if(){// A -> B

        }
        if(){ // B -> C

        }
        if(){ // A -> C

        }


    }
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
