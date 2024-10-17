void shaker_sort(int array[], const int length) {
     int max_index = length, min_index = 1;
     bool sorted;
     do {
          sorted = true;
          for (int i = min_index; i < max_index; i++) {
               if (array[i - 1] > array[i]) {
                    swap(array, i - 1, i);
                    sorted = false;
               }
          }
          max_index--;
          if (sorted) break;
          for (int i = max_index - 1; i >= min_index; i--) {
               if (array[i - 1] > array[i]) {
                    swap(array, i - 1, i);
                    sorted = false;
               }
          }
          min_index++;
        print_array(array);
     } while (!sorted);
}

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

int main(){
    int array[] = {2, 1, 9, 7, 6};
    shaker_sort(array, 5);

}