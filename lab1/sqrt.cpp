/*******************************************************************************
 * Filename: sqrt.cpp
 * Author  : Daniel Detore
 * Version : 1.0
 * Date    : September 5, 2024
 * Description: Computes the square root of a command-line argument.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
using namespace std;

int main(void)
{
    double num;
    double epsilon = 0.0000001;
    cin >> num;
    cin >> epsilon;

    
    
}

double sqrt(double num, double epsilon){
    if (num <= 0)
        return numeric_limits<double>::quiet_NaN();
    else if (num == 0 || num == 1)
        return num;
    else
        return 0;
    return 0;
}