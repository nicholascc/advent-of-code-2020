#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long ul;

int main() {
  ifstream input ("in.txt");
  int valid_count = 0;
  while(!input.eof()) {
    int min;
    char _c;
    int max;
    char c;
    input >> min >> _c >> max >> c;
    string pass;
    getline(input, pass);

    int count = 0;
    for(int i = 0; i < pass.size(); i++) {
      if(pass[i] == c) count++;
    }

    if(count >= min && count <= max) {
      valid_count++;
    }
  }

  cout << valid_count << endl;
}
