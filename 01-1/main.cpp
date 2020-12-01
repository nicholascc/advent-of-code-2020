#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long ul;

int main() {
  ifstream input ("in.txt");
  vector<int> v;
  while(!input.eof()) {
    int n;
    input >> n;
    v.push_back(n);
  }

  vector<int> big_nums; // greater than 1000
  vector<int> small_nums; // less than or equal to 1000

  for(ul i = 0; i < v.size(); i++) {
    if(v[i] <= 1000) {
      small_nums.push_back(v[i]);
    } else {
      big_nums.push_back(v[i]);
    }
  }

  for(ul i = 0; i < small_nums.size(); i++) {
    int n1 = small_nums[i];
    for(ul j = 0; j < big_nums.size(); j++) {
      int n2 = big_nums[j];
      if(n1 + n2 == 2020) {
        cout << n1*n2 << endl;
      }
    }
  }
}
