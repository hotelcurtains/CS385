/*
Author: Daniel Detore
Combining bogosort and bubble sort to create a true evil.
*/

#include <sstream>  // for input handling
#include <cstdlib>  // Needed for rand() and srand()
#include <chrono>   // for function timing
#include <ctime>    // for seeding
#include <iostream> // for printing
using namespace std;
using namespace std::chrono;

static void swap(int array[], const int a, const int b) {
    int temp = array[a];
    array[a] = array[b];
    array[b] = temp;
}

/*
static void print_array(int array[], const int length){
    cout << "[";
    for (int i = 0; i < length-1; i++){
        cout << array[i] << ", ";
    }
    cout << array[length-1] << "]" << endl;
}
*/

static bool is_sorted(int array[], const int length){
    for (int i = 0; i < length-1; i++){
        if (array[i] > array[i+1]) return false;
    }
    return true;
}

// sort an array for a comically long time
// input: an array and its length
// output: print the sorted array
void coinflipsort(int array[], int length){
    int swaps = 0;
    while (!is_sorted(array, length)){
        for (int i = 0; i < length-1; i++){
            int r = rand() % 2;
            swaps += r;
            if (r == 1) swap(array, i, i+1);
        }
    }
    //print_array(array, length);
    cout << "Swaps: " << swaps << endl;
}

void bubble_sort(int array[], const int length) {
    int swaps = 0;
    for(int i = 0; i < length - 1; i++) {
        for(int j = 0; j < length - 1 - i; j++) {
            if(array[j + 1] < array[j]) {
               swaps++;
               swap(array, j, j + 1);
            }
        }
    }
    //print_array(array, length);
    cout << "Swaps: " << swaps << endl;
}

void bogo_sort(int array[], const int length) {
    int shuffles = 0;
    while(!is_sorted(array, length)){
        for (int i = 0; i < length; i++){ // shuffle
            shuffles++;
            swap(array, i, rand() % length);
        }
    }
    //print_array(array, length);
    cout << "Shuffles: " << shuffles << endl;
}

int main(int argc, char * const argv[]) {
    if(argc != 2){
        cout << "Usage: " << argv[0] << " <n>" << endl;
        return 1;
    }
    stringstream iss;
    iss.clear();
    iss.str(argv[1]);
    int n;
    if(!(iss >> n) or (n < 0)){
        cout << "n must be a positive integer" << endl;
        return 1;
    }
    if(n>=12) cout << "Please hold..." << endl;

    srand(time(0));

    int* array = new int[n];
    int* array2 = new int[n];
    int* array3 = new int[n];
    for (int i = 0; i < n; i++){
        int k = (int)rand();
        array[i] = k;
        array2[i] = k;
        array3[i] = k;
    }

    cout << "Bubble sort:" << endl;
    auto start = high_resolution_clock::now();
    bubble_sort(array2,n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Time: " << duration.count() << " microseconds" << endl;

    cout << "Coin-flip sort:" << endl;
    start = high_resolution_clock::now();
    coinflipsort(array,n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time: " << duration.count() << " microseconds" << endl;

    cout << "Bogosort:" << endl;
    start = high_resolution_clock::now();
    bogo_sort(array3,n);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Time: " << duration.count() << " microseconds" << endl;

    delete [] array;
}