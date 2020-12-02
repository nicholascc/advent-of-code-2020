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
    int l1;
    char _c;
    int l2;
    char c;
    input >> l1 >> _c >> l2 >> c;
    string pass;
    getline(input, pass);

    if(pass.size() < 3) {
      break; // This if statement is here so that an empty line of input is ignored.
    }

    l1 = l1 - 1 + 2; // The "pass" string starts with two unincluded characters, so
    l2 = l2 - 1 + 2; // the locations must be increased by 2. Also, the input indexes
                     // the passwords starting at one so the locations must be
                     // decremented.

    if((pass[l1] == c && pass[l2] != c) || (pass[l1] != c && pass[l2] == c)) {
      valid_count++;
    }
  }

  cout << valid_count << endl;
}
