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

struct Wrapper{
    State *point;

    Wrapper(int _a, int _b, int _c, string _directions){
        point = new State(_a, _b, _c, _directions);
    }

    // for all other nodes with parent nodes
    Wrapper(int _a, int _b, int _c, string _directions, State *_parent){
        point = new State(_a, _b, _c, _directions, _parent);
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

    Wrapper output(0, 0, 0, "No solution.");
    State win(goal[0], goal[1], goal[2], "__");

    vector<State> seen;

    queue<Wrapper> q;
    q.push(Wrapper(0, 0, capacity[2], "Initial state."));
    
    while(!(q.empty())){
        
        Wrapper current(0, 0, 0, "No solution.");
        current = q.front();
        q.pop();
        if ((*current.point) == win){
            output = current;
            break;
        }
        if (in((*current.point), seen)){
            continue;
        }
        seen.push_back((*current.point));
        // try the 6 ways to pour water, pushing new States to the queue
        if((*current.point).c != 0 && (*current.point).a != capacity[0]){ // C -> A
            int empty_space = capacity[0] - (*current.point).a;
            ostringstream oss;

            if (empty_space <= (*current.point).c){
                oss << "Pour " << empty_space << " gallons from C to A.";
                string direction = oss.str();
                q.push(Wrapper(capacity[0], (*current.point).b, (*current.point).c - empty_space, direction, current.point));
            }
            else {
                oss << "Pour " << (*current.point).c << " gallons from C to A.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a + (*current.point).c, (*current.point).b, 0, direction, current.point));
            };
        }
        if((*current.point).b != 0 && (*current.point).a != capacity[0]){ // B -> A
            int empty_space = capacity[0] - (*current.point).a;
            ostringstream oss;

            if (empty_space <= (*current.point).b){
                oss << "Pour " << empty_space << " gallons from B to A.";
                string direction = oss.str();
                q.push(Wrapper(capacity[0], (*current.point).b - empty_space, (*current.point).c, direction, current.point));
            }
            else {
                oss << "Pour " << (*current.point).b << " gallons from B to A.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a + (*current.point).b, 0, (*current.point).c, direction, current.point));
            };
        }
        if((*current.point).c != 0 && (*current.point).b != capacity[1]){ // C -> B
            int empty_space = capacity[1] - (*current.point).b;
            ostringstream oss;

            if (empty_space <= (*current.point).c){
                oss << "Pour " << empty_space << " gallons from C to B.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a, capacity[1], (*current.point).c - empty_space, direction, current.point));
            }
            else {
                oss << "Pour " << (*current.point).c << " gallons from C to B.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a, (*current.point).b + (*current.point).c, 0, direction, current.point));
            };
        }
        if((*current.point).a != 0 && (*current.point).b != capacity[1]){// A -> B
            int empty_space = capacity[1] - (*current.point).b;
            ostringstream oss;
            
            if (empty_space <= (*current.point).b){
                oss << "Pour " << empty_space << " gallons from A to B.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a - empty_space, capacity[1], (*current.point).c, direction, current.point));
            }
            else {
                oss << "Pour " << (*current.point).a << " gallons from A to B.";
                string direction = oss.str();
                q.push(Wrapper(0, (*current.point).b + (*current.point).a, (*current.point).c, direction, current.point));
            };
        }
        if((*current.point).b != 0 && (*current.point).c != capacity[2]){ // B -> C
            int empty_space = capacity[2] - (*current.point).c;
            ostringstream oss;
            

            if (empty_space <= (*current.point).b){
                oss << "Pour " << empty_space << " gallons from B to C.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a, (*current.point).b - empty_space, capacity[2], direction, current.point));
            }
            else {
                oss << "Pour " << (*current.point).b << " gallons from B to C.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a , 0, (*current.point).c + (*current.point).b, direction, current.point));
            };
        }
        if((*current.point).a != 0 && (*current.point).c != capacity[2]){ // A -> C
            int empty_space = capacity[2] - (*current.point).c;
            ostringstream oss;
            

            if (empty_space <= (*current.point).b){
                oss << "Pour " << empty_space << " gallons from A to C.";
                string direction = oss.str();
                q.push(Wrapper((*current.point).a - empty_space, (*current.point).b , capacity[2], direction, current.point));
            }
            else {
                oss << "Pour " << (*current.point).a << " gallons from A to C.";
                string direction = oss.str();
                q.push(Wrapper(0, (*current.point).b, (*current.point).c + (*current.point).a, direction, current.point));
            };
        }
    }

    cout << traceback(output.point) << endl;

    
    while(!q.empty()){
        list.push_back(q.front());
        q.pop();
    }
    for(int i = 0; i < (int)list.size(); i++){
        delete list[i].point;
        list[i].point = NULL;
    }
    list.clear();

    
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
