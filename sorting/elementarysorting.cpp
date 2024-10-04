#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
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


void bubble_sort(int array[], const int length) {
    for(int i = 0; i < length - 1; i++) {
        for(int j = 0; j < length - 1 - i; j++) {
            if(array[j + 1] < array[j]) {
               swap(array, j, j + 1);
            }
        }
    }
}

void bubble_sort_opt(int array[], const int length) {
    int unsorted = length;
    while(unsorted > 1) {
        int s = 0;
        for(int j = 1; j < unsorted; j++) {
            if(array[j] < array[j - 1]) {
                swap(array, j - 1, j);
                s = j;
            }
        }
        unsorted = s;
        print_array(array, length);
    }
}

void selection_sort(int array[], const int length) {
    for(int i = 0; i < length - 1; i++) {
        int min_j = i;
        for(int j = i + 1; j < length; j++) {
            if(array[j] < array[min_j]) {
                min_j = j;
            }
        }
        if(min_j != i) {
            swap(array, i, min_j);
        }
        print_array(array, length);
    }
}

void insertion_sort(int array[], const int length) {
    for(int i = 1; i < length; i++) {
        int j, current = array[i];
        for(j = i - 1; j >= 0 && array[j] > current; j--) {
            array[j + 1] = array[j];
        }
        array[j + 1] = current;
        print_array(array, length);
    }
}

int main() {
    cout << "bubble sort optimized:" << endl;
    int array1[] = {78,15,23,2,97,85};
    bubble_sort_opt(array1,6);


    cout << "selection sort:" << endl;
    int array2[] = {78,15,23,2,97,85};
    selection_sort(array2,6);

    cout << "insertion sort:" << endl;
    int array3[] = {78,15,23,2,97,85};
    insertion_sort(array3,6);
    
    return 0;
}
