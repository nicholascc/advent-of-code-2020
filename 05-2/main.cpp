#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

typedef unsigned long ul;

enum State {
  NONE,
  LABEL,
  FIELD,
};

int main() {
  ifstream input ("in.txt");

  const int SEAT_COUNT = 1024;
  bool seat_exists[SEAT_COUNT] = { false };

  while(!input.eof()) {
    string pass;
    getline(input, pass);

    if(pass.size() < 6) { // to weed out empty lines
      continue;
    }

    int i = 0;
    int row;
    int column;
    {
      int current_row_lower_bound = 0;
      int row_lower_bound_increase = 64;
      for(; i < 7; i++) {
        if(pass[i] == 'B') {
          current_row_lower_bound += row_lower_bound_increase;
        }
        row_lower_bound_increase /= 2;
      }

      row = current_row_lower_bound;
    }

    {
      int current_col_lower_bound = 0;
      int col_lower_bound_increase = 4;
      for(; i < 10; i++) {
        if(pass[i] == 'R') {
          current_col_lower_bound += col_lower_bound_increase;
        }
        col_lower_bound_increase /= 2;
      }

      column = current_col_lower_bound;
    }

    int id = row*8 + column;

    seat_exists[id] = true;
  }

  for(int i = 0; i < SEAT_COUNT; i++) {
    if(seat_exists[i]) continue;
    if(!seat_exists[i-1]) continue;
    if(!seat_exists[i+1]) continue;
    cout << i << endl;
    break;
  }
}
