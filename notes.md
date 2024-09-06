2% penalty for each hour late


# C++
- java main method == int main(void){}
- smallest valid C++ file:
```c++
int main(void){
    return 0;
}
```

- when you have the makefile in the directory with the program, run `make` to make the program and then run the exe (no file extension)
- the test script will compile and test the cpp file automatically
- `System.out.print("hello world")` ↔ `std::cout << "hello world"`
  - adding `<< std::endl` brings the cursor it to the next line like `println`
- `import` ↔ `#include`
  - full file:
    ```c++
    #include <iostream>

    int main(void){
        std::cout << "hello world" << std::endl;
        return 0;
    }
    ```
- if we include `using namespace std;` we can remove `std::` and just use its methods
    ```c++
    #include <iostream>
    using namespace std;

    int main(void){
        cout << "hello world" << endl;
        return 0;
    }
    ```
- `cin >> name` gets input from the keyboard
  - to save it to a variable it must already be instantiated
    ```c++
    #include <iostream>
    using namespace std;

    int main(void){
        string name;
        cout << "hello world" << endl;
        cin >> name;
        cout << "my name is: " << name << endl;
        return 0;
    }
    ```

## Accepting input

- we want to see
```c++
$ ./maxtwo 23 57
57
```
so we use the header:
```c++
int main (int argc, char* argv[])
```
- `argv` is a list of strings; it contains the function call and all of the arguments you give it
  - i.e. `{"./maxtwo", "23", "57"}`
  - since `argv[0]` is the name of the program as the user called it, then we can just call `argv[0]` to remind them of it.
- first we need to check that the user gave the right amount of arguments
  - `argc` gives us the number of arguments
  - i.e. for the call we want, we check that `argc = 3`
```c++
#include <iostream>
using namespace std;
int main (int argc, char* argv[]){

  if (argc !=3){
    cerr << "Usage: " << argv[0] << "<int> <int>" << endl;
    return 1;
  }

  return 0;
}
```
- now we need to turn the strings into integers
- istringstream lets us read fro the input as if we are actively reading it from the keyboard
  - we need to include the sstream header to use it
```c++
#include <iostream>
#include <sstream>
using namespace std;
int main (int argc, char* argv[]){
  istringstream iss;
  int n;

  if (argc !=3){
    cerr << "Usage: " << argv[0] << " <int> <int>" << endl;
    return 1;
  }

  iss.str(argv[1]); /*iss now contains the first argument*/
  iss >> n; /*we read from iss to n. c++ already knows that we want it to be an integer.*/
  cout << n; /*we'll check if this worked or not.*/

  return 0;
}
```
- if we put in an argument that's not an int, our program will break:
```c++
$ ./maxtwo fghjkl 57
0
```
- because the conversion will return true/false if it succeeds/fails, we can add a control block as such:
```c++
#include <iostream>
#include <sstream>
using namespace std;
int main (int argc, char* argv[]){
  istringstream iss;
  int n, m;

  if (argc !=3){
    cerr << "Usage: " << argv[0] << " <int> <int>" << endl;
    return 1;
  }

  iss.str(argv[1]); /*iss now contains the first argument*/
  if (!iss >> n){ /*this line *always* does the conversion whether it fails or succeeds.*/
    cerr << "Error: first command line argument must be int" << endl;
    return 1; /*we have to quit the user out so we don't run the program with wrong inputs anyway.*/
  }

  iss.clear(); /*the istringstream needs to be cleared to remove residual data from the first argument. you could use a second one instead of reusing just one if you wanted.*/
  iss.str(argv[2]); /*iss now contains the second argument*/
  if (!iss >> m){ 
    cerr << "Error: second command line argument must be int" << endl;
    return 1;
  }

  cout << "max(" << n << ", " << m << ") is " << max(n,m) << endl;

  return 0;
}
/*and we've added the actual algorithm to finish.*/
int max(int n, int m){
  if (n > m) return n
  else return m
}
```

and now we will see the thing we want to see:
```
ubuntu@ubuntu:~/Documents/CS385/maxtwo$ ./maxtwo 23 57
max(57, 57) is 32762
```