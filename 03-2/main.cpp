#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned long ul;

struct V2D {
  ul x;
  ul y;
};

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
    for(ul i = 0; i < line.size(); i++) {
      if(line[i] == '.') {
        row.push_back(true);
      } else if(line[i] == '#') {
        row.push_back(false);
      }
    }

    grid.push_back(row);
  }

  const ul slope_count = 5;
  V2D slopes[slope_count] = {{1,1}, {3,1}, {5,1}, {7,1}, {1,2}};
  ul total = 1;
  for(ul j = 0; j < slope_count; j++) {

    V2D slope = slopes[j];
    ul tree_count = 0;

    ul x = 0;
    ul y = 0;

    for(y = 0; y < grid.size(); y+=slope.y) {
      if(!grid[y][x]) {
        tree_count++;
      }
      x += slope.x;
      x = x % grid[0].size();
    }

    total *= tree_count;
  }

  cout << total << endl;
}
