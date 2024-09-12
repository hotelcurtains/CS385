/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Daniel Detore
 * Date        : September 18, 2024
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    cout << endl << "Number of primes found: " << num_primes_ << endl
         << "Primes up to " << limit_  << ":" << endl;


    const int max_prime_width = num_digits(max_prime_),
              primes_per_row = 80 / (max_prime_width + 1);

    if(primes_per_row < num_primes_) {
        int cursor = 1;

        for(int i = 2; i <= limit_; i++){
            if (is_prime_[i] && i != max_prime_) {
                if (cursor < primes_per_row){
                    cout << setw(max_prime_width) << i << " ";
                    cursor++;
                }
                else {
                    cout << setw(max_prime_width) << i << endl;
                    cursor = 1;
                }
            } else if (i == max_prime_) {
                cout << setw(max_prime_width) << i << endl;
            }
        }
    } else {
        for(int i = 2; i <= limit_; i++){
            if (is_prime_[i] && i != max_prime_) cout << i << " ";
            else if (i == max_prime_) cout << i << endl;
        }
    }
    cout << endl;
}

void PrimesSieve::sieve() {
    // is_prime_ is a list of integers [0, limit]
    // limit is as far as we check
    // we need to calculate num_primes_ and max_prime_
    for (int i = 2; i <= limit_; i++){
        is_prime_[i] = 1;
    }

    num_primes_ = limit_ - 1;
    for(int i = 2; i <= sqrt(limit_); i++){
        if(is_prime_[i]){
            for (int j = i*i; j <= limit_; j += i ){
                if (is_prime_[j] == 1) num_primes_--;
                is_prime_[j] = 0;
                
            }
        }
    }

    max_prime_  = limit_;
    while(is_prime_[max_prime_] != 1){
        max_prime_--;
    }
}

/* Returns how many digits are in an integer. */
int PrimesSieve::num_digits(int num) {
    int length = 0;
    while(num > 0){
        num /= 10;
        length++;
    }
    return length;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // code that uses the PrimesSieve class to produce the desired output.

    PrimesSieve sieve(limit);

    sieve.display_primes();

    return 0;
}
