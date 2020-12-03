#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long ul;

int main() {
  ifstream input ("in.txt");
  
  vector<vector<bool>> grid;
  while(!input.eof()) {
    string line;
    getline(input, line);

    if(line.size() < 3) {
      break; // This if statement is here so that an empty line of input is ignored.
    }

    vector<bool> row;
    for(int i = 0; i < line.size(); i++) {
      if(line[i] == '.') {
        row.push_back(true);
      } else if(line[i] == '#') {
        row.push_back(false);
      }
    }

    grid.push_back(row);
  }

  int tree_count = 0;

  int x = 0;
  int y = 0;

  for(y = 0; y < grid.size(); y++) {
    if(!grid[y][x]) {
      tree_count++;
    }
    x += 3;
    x = x % grid[0].size();
  }

  cout << tree_count << endl;
}
