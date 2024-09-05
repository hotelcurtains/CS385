/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Daniel Detore
 * Version : 1.0
 * Date    : September 5, 2024
 * Description: Computes the square root of a command-line argument.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

/* https://github.com/hspahic-cs/Stevens-IT/blob/3e11c00d56837fa4774b66849e91a63dbb5e9e34/CS385-TA%20-%20Algorithms/Algorithms/sqrt/sqrt.cpp */
#include <iomanip>
#include <limits>
#include <iostream>
using namespace std;


double sqrt(double num, double epsilon = 0.0000001){
    if (num < 0)
        return numeric_limits<double>::quiet_NaN();
    else if (num == 0 || num == 1)
        return num;
    else {
        double next_guess = num;
        double last_guess;
        while(abs(next_guess - last_guess) > epsilon){
		    last_guess = next_guess;
		    next_guess = (next_guess + num / next_guess) * 0.5;
	    }
        return next_guess;
    }
}

int main(void){
    double num;
    double epsilon;

    cin >> num >> epsilon;

    cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
    
}

