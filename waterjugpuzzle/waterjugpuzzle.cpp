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
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // for all other nodes with parent nodes
    State(int _a, int _b, int _c, string _directions, State *_parent) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{_parent} {
            if (directions.find("Pour 1 gallons from") != string::npos) {
                directions.erase(13, 1);
            }
        }

    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        if (directions == "No solution."){
            oss << "No solution.";
        } else{
            oss << directions << " (" << a << ", " << b << ", " << c << ")";
        }
        return oss.str();
        
    }

    // lets us check aimply if the states are the same
    bool operator== (const State &o) {
        return (a == o.a && b == o.b && c == o.c);
    }
};

// returns true if vector contains a, returns false otherwise.
bool in(State a, vector<State> vector){
    for (const auto &state : vector){
        if (a == (state)) return true;
    }
    return false;
}

string traceback(State* input){
    if ((*input).parent == nullptr){
        return (*input).to_string();
    } else return traceback((*input).parent)+"\n"+(*input).to_string();
}

void solve(int capacity[], int goal[]){

    vector<State> seen;
    vector<State*> all_pointers;

    State* output = new State(0, 0, 0, "No solution.");
    all_pointers.push_back(output);

    State win(goal[0], goal[1], goal[2], "__");
    

    queue<State*> q;
    State* initial = new State(0, 0, capacity[2], "Initial state.");
    q.push(initial);
    all_pointers.push_back(initial);


    while(!(q.empty())){
        State* current = q.front();
        q.pop();
        if ((*current) == win){
            output = current;
            break;
        }
        if (in((*current), seen)){
            continue;
        }
        seen.push_back((*current));
        //all_pointers.push_back(current);
        // try the 6 ways to pour water, pushing new States to the queue
        if((*current).c != 0 && (*current).a != capacity[0]){ // C -> A
            int empty_space = capacity[0] - (*current).a;
            ostringstream oss;

            if (empty_space <= (*current).c){
                oss << "Pour " << empty_space << " gallons from C to A.";
                string direction = oss.str();
                State* add = new State(capacity[0], (*current).b, (*current).c - empty_space, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            }
            else {
                oss << "Pour " << (*current).c << " gallons from C to A.";
                string direction = oss.str();
                State* add = new State((*current).a + (*current).c, (*current).b, 0, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            };
        }
        if((*current).b != 0 && (*current).a != capacity[0]){ // B -> A
            int empty_space = capacity[0] - (*current).a;
            ostringstream oss;

            if (empty_space <= (*current).b){
                oss << "Pour " << empty_space << " gallons from B to A.";
                string direction = oss.str();
                State* add = new State(capacity[0], (*current).b - empty_space, (*current).c, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            }
            else {
                oss << "Pour " << (*current).b << " gallons from B to A.";
                string direction = oss.str();
                State* add = new State((*current).a + (*current).b, 0, (*current).c, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            };
        }
        if((*current).c != 0 && (*current).b != capacity[1]){ // C -> B
            int empty_space = capacity[1] - (*current).b;
            ostringstream oss;

            if (empty_space <= (*current).c){
                oss << "Pour " << empty_space << " gallons from C to B.";
                string direction = oss.str();
                State* add = new State((*current).a, capacity[1], (*current).c - empty_space, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            }
            else {
                oss << "Pour " << (*current).c << " gallons from C to B.";
                string direction = oss.str();
                State* add = new State((*current).a, (*current).b + (*current).c, 0, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            };
        }
        if((*current).a != 0 && (*current).b != capacity[1]){// A -> B
            int empty_space = capacity[1] - (*current).b;
            ostringstream oss;
            
            if (empty_space <= (*current).b){
                oss << "Pour " << empty_space << " gallons from A to B.";
                string direction = oss.str();
                State* add = new State((*current).a - empty_space, capacity[1], (*current).c, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            }
            else {
                oss << "Pour " << (*current).a << " gallons from A to B.";
                string direction = oss.str();
                State* add = new State(0, (*current).b + (*current).a, (*current).c, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            };
        }
        if((*current).b != 0 && (*current).c != capacity[2]){ // B -> C
            int empty_space = capacity[2] - (*current).c;
            ostringstream oss;
            

            if (empty_space <= (*current).b){
                oss << "Pour " << empty_space << " gallons from B to C.";
                string direction = oss.str();
                State* add = new State((*current).a, (*current).b - empty_space, capacity[2], direction, current);
                q.push(add);
                all_pointers.push_back(add);
            }
            else {
                oss << "Pour " << (*current).b << " gallons from B to C.";
                string direction = oss.str();
                State* add = new State((*current).a , 0, (*current).c + (*current).b, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            };
        }
        if((*current).a != 0 && (*current).c != capacity[2]){ // A -> C
            int empty_space = capacity[2] - (*current).c;
            ostringstream oss;
            

            if (empty_space <= (*current).b){
                oss << "Pour " << empty_space << " gallons from A to C.";
                string direction = oss.str();
                State* add = new State((*current).a - empty_space, (*current).b , capacity[2], direction, current);
                q.push(add);
                all_pointers.push_back(add);
            }
            else {
                oss << "Pour " << (*current).a << " gallons from A to C.";
                string direction = oss.str();
                State* add = new State(0, (*current).b, (*current).c + (*current).a, direction, current);
                q.push(add);
                all_pointers.push_back(add);
            };
        }
        
    }

    cout << traceback(output) << endl;


    for(State* pointer : all_pointers){
        delete pointer;
        pointer = NULL;
    }

    return;
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
