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

## Pointer
a pointer stores a memory address of something 
```c++
int x = 5;
int *z = &x;
```
- now z is pointing to x which contains 5.
  - when declaring z the `*` is the pointer type.
- z and x have different addresses
- calling `&z` accesses the address of z, which the computer assigns
- calling `z` accesses the address of **x**, which we stored in it
- calling `*z` accesses the *value* of **x**
  - the star here is the *dereference* operator.
- if we try
  ```c++
  z+=3000;
  ```
  - now z points to some other memory address, 3000 addresses after x, likely random garbage. 
  - the compiler will let you do this. do not do this.
- if a pointer is pointing to a bad place, you will get a `Segmentation fault` or it might just keep running with garbage data
- if you do get a segmentation fault, running `gdb ./[program]` then `run` tells you what line of code causes the error
  - though it will tell you when the garbage is accessed, not when it becomes garbage
  - will not work if you aren't getting a segmentation fault
  - you will need to quit gdb afterward
- when a function call happens, the variable with which it was called (say x) and the variable that is passed to it (say k) will be at different addresses.
  - i.e. any changes that happen to k in the function will not happen to x
  - this is *pass by value*
  - k is destroyed at the end of the function
  - this works the same as python, java, etc
- what if we want to modify `x` in main from the function?
  - we *pass by pointer* instead
  - the function definition takes pointer `*k` so we can pass `f(x&)`
  - now `f`'s code can effect `x` while calling it `*k`
- we also have *pass by reference* in C++
  - define the function with `&k` so you don't need to call the function with the address every time
  - only uses one memory address; k is a reference to the *same* address as x
  - only for the programmer; the compiler rewrites it as pass by pointer for the computer

### Pointers with Dynamically Allocated Memory
- you can declare `int y[10]` with 10 spaces
  - you can call them by `y[i]`
- but if you don't know how many spaces you need, it needs to be declared dynamically
  ```c+++
  cout << "x is" << x << endl;
  int *values;
  values = new int[x];
  ```
  - `values` is only pointing to the first element of the array
    - the rest are stored sequentially after it
  - we can still call elements like in java as `value[i]` 
  - or we can call them like C as `*(values+i)`
- when passing the array to a function, you can pass it like an array or like a pointer
  - just define it in the way you want it
  - `int array[]` → use `array[i]`
  - `int *array` → use `*(values+i)`
- you will need to know the length when iterating
  - there is no `.length` and going past the end will rarely cause a segmentation fault
- when you are done with the array memory you must delete it
  - java and python just do it for you. c++ does not
  - for each `new` there must be a `delete` somewhere
  - i.e. `values = new int[x];` → `delete [] values;`
    - usually done right before `return 0;` at the end
  - after the `delete`, the pointer will be dangling (pointing to nothing/garbage)
  - you can reassign `values` to point to something else if you want

## Classes
- declared like java
- everything under the `public:` header is a public member/method
  - everything under `private:` is private
  - does not have brackets
- constructor with initializer list lest you set everything without a bunch of code
  - put a semicolon after constructor header then list `instance_variable{input}`
  - then `{ }` to because the code block is required even if it is empty
- methods that do not modify member (instance) variables should be declared `const` after the header
  - `void print() const { ... }`
  - NOT like static methods
  - the only requirement is that they do not mutate a member
- class definitions end with semicolons
  - `class Student { ... };`
- local declaration to the stack: `MyPoint point1(x,y,z);`
  - this variable disappears at the end of the method
- declaration to the heap: `MyPoint *point4 = new MyPoint(x,y,z);`
  - similar to java except `point4` is a *pointer* to an anonymous `new MyPoint`
  - the `new` object will stick around until it is actively deleted with `delete point4;`
    - no square brackets because it's just an object, not an array
    - can give it the pointer because it will delete what's at that address, but NOT the content of `point4`
    - `point4` will now point to something that does not exist
    - you should be cleaning up garbage as you go (as you stop using it), not waiting until the very end
- you can use a class an an interface
  - define the class's members and methods with no code blocks/values, then put all of the code for it in a different file

## Vectors
- like an ArrayList
- requires `#include <vector>`
- declare like `vector<MyPoints> points;`
- then use `points.push_back(point1);` to put objects in it
- can access elements like `points[1]`
- we also have `points.size()`, but it returns a `size_t` type
  - `size_t` is effectively the type that can hold the largest possible integer
  - it prints like a regular integer

### regular for loop
```c++
for (size_t i = 0; i < points.size(); i++) {
  points[i].print_coords();
}
```

### for-each loop
```c++
vector<MyPoints> points;
for (const auto &point : points){
  ...
}
```
- `point` is the loop variable
  - it is a reference;
  - we do this instead of copying the element from the array into the loop every time
- `const` tells the compiler to throw an error if we try to change the elements
- `auto` automatically gets the type of the elements in the vector

### iterator loop
```c++
for (auto it = points.cbegin(); it != points.cend(); it++){
  it->print_coords(); // equivalent to (*it).print_coords();
}
```
- `it` is our iterator
- we use `auto` here because the type of the iterator is ugly
- `it++` magically makes the iterator move to the next element
- `->` calls the method with the object the iterator points at

# Algorithms
- an algorithm is a sequence of unambiguous instructions for solving a problem
- its inputs must be specified carefully
- the same algorithm can be implemented different ways
- multiple algorithms might solve the same problem
![how we make an algorithm](image.png)
- sieve - taking a list an removing items that do not fit some criteria
- sum of integers `[1,n]` = n(n+1)/2

# Asymptotic Notation / Rates of Growth
- every function is its own upper bound and lower bound
- you can remove any lower-degree term from the final notation
  - i.e. O(5n² + n) → (n²)
  - this is now asymptotic notation
    - the asymptote is the same even if it's off from the actual function
- when calculating time
  - we can call the time needed for one command c₁
  - and overhead time for initializing loop variables and returning output c₂ both
  - for a loop that runs n times, this makes the whole function n * c₁ + c₂
  - we remove all this when finding asymptotic notation though
    - we care about how it grows, not how long it actually takes

## Big O
- O(1) is the best possible rate, as ther is nothing lower
- O is the asymptotic upper bound of the function
  - i.e. when n is infinitely large
- any line "under" O(n) is technically part of it
  - e.g. 10n +5 is in O(n²)

## Big Omega
- Ω() is the asymptotic lower bound
- anything above Ω() is part of it
  - e.g. n³ is in Ω(n²)

## Big Theta
- Θ(n) includes both O(n) and Ω(n)
- gives us an *asymptotically tight bound* on running time
- e.g. for Θ(n), there are some k₁, k₂ where k₂n > n > k₁n for large values of n
  - ![running time bounded by two linear functions](c14a48f24cae3fd563cb3627ee2a74f56c0bcef6.png)
  - we're not too worried about small values of n
- the same thing applies for any other random function of n
  - ![random running time bounded by itself scaled](2bdc25c7eda8486d05b8031c5a63535684ecb5a1.png)
- 


## Theorem
![alt text](image-1.png) for Ω use min()

### Limit Rule for Growth Rate Comparison
![alt text](image-2.png)
- we will rarely find that the limit DNE
  - still, the fact that it can happen makes this way less general than other ways
- recall L'Hopital's rule
  - ![L'Hopital's rule](image-3.png)
- also consider sterling's formula
  ![Sterling's formula](image-4.png)
  - larger n → better approximation of n!

## Problem Sizes
let's say we have 1 hour of computation time = 3.6*10⁹ microseconds. 
if 
  - we have an algorithm with f(n) = log₂(n)
    - log₂(n) = 3.6\*10⁹ ⇛ n = 2^(3.6\*10⁹) which is a lot of possible calculations
    - note that lg(n) == log₂(n)
  - we have f(n) = n
    - n = 3.6\*10⁹
- some rules about logs and more in [this handout](/notes/Guidelines%20for%20Asymptotic%20Analysis.pdf)
- all logs grow at the same rate no matter the base

# Check that all characters in string are unique
- set up an unsigned int = 0 and use it as a vector
```
         hgfedcba
vector = 00000000
```
- now we can have a setter shift a 1 into the correct place
  - say we read a g:
  ```c++
  setter = 1 << ('g' - 'a')
  ```
  ```
           hgfedcba
  setter = 01000000
  ```
- do a bitwise `&` between them
  - if it = 0, we have never seen the character before
  - if it is > 0, the character is a duplicate
- now we must remember that we have seen this character (here 'g')
- now we bitwise or `|` the setter and vector to remember all seen characters
  - and put the result into vector
  - e.g. vector = 01000000 ⇛ we've only seen 'g'
  - vector = 11000000 ⇛ we've seen 'gh' in any order