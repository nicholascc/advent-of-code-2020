#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long ul;

int main() {
  ifstream input ("in.txt");
  vector<int> all_nums;
  while(!input.eof()) {
    int n;
    input >> n;
    all_nums.push_back(n);
  }

  // There are very few numbers <= 1010 in the dataset (mine had only 3!)
  // but you need to have at least 1 number <= 1010 in
  // a pair that sums to 2020.
  // This means that we can solve this problem significantly
  // faster than we might otherwise (it probably doesn't matter
  // all that much, however).

  // A similar property holds with a triple - the only possible combinations that
  // sum to 2020 are 2 small nums + 1 big num
  //         or just 3 small nums.
  vector<int> big_nums; // greater than 1010
  vector<int> small_nums; // less than or equal to 1010

  for(ul i = 0; i < all_nums.size(); i++) {
    if(all_nums[i] <= 1000) {
      small_nums.push_back(all_nums[i]);
    } else {
      big_nums.push_back(all_nums[i]);
    }
  }


  for(ul i = 0; i < small_nums.size(); i++) {
    int n1 = small_nums[i];

    for(ul j = 0; j < small_nums.size(); j++) {
      int n2 = small_nums[j];

      for(ul k = 0; k < all_nums.size(); k++) {
        int n3 = all_nums[k];
        if(n1 + n2 + n3 == 2020) {
          cout << "Result: " << n1*n2*n3 << endl;
          cout << "Numbers: " << n1 << " " << n2 << " " << n3 << endl;
        }
      }
    }
  }
}
