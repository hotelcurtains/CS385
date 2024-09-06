/*******************************************************************************
 * Filename: maxtwo.cpp
 * Author  : Daniel Detore
 * Version : 1.0
 * Date    : September 5, 2024
 * Description: Computes the max of two command-line arguments.
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

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

  iss.str(argv[1]);
  if (!(iss >> n)){
    cerr << "Error: first command line argument must be int" << endl;
    return 1;
  }

  iss.clear(); 
  iss.str(argv[2]); 
  if (!(iss >> m)){ 
    cerr << "Error: second command line argument must be int" << endl;
    return 1;
  }

  cout << "max(" << n << ", " << m << ") is " << max(n,m) << endl;

  return 0;
}

int max(int n, int m){
  if (n > m) return n;
  else return m;
}