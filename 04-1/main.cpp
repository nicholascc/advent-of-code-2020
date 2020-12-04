#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

typedef unsigned long ul;

enum State {
  NONE,
  LABEL,
  FIELD,
};

int main() {
  ifstream input ("in.txt");


  State state = NONE;
  string label = "";

  vector<string> labels_seen;
  int endlines_seen = 0;

  int valid_count = 0;

  while(!input.eof()) {
    char c;
    input >> noskipws >> c;

    switch(state) {
      case NONE:
        if(isalpha(c)) {
          state = LABEL;
          label.push_back(c);
        } else if(c == '\n') {
          endlines_seen++;
        }
        break;
      case LABEL:
        if(isalpha(c)) {
          label.push_back(c);
        } else if(c == ':') {
          state = FIELD;
        } else {
          cout << "ERROR: Unexpected character." << endl;
        }
        break;
      case FIELD:
        if(isspace(c)) {
          state = NONE;
          labels_seen.push_back(label);
          label = "";
          endlines_seen = c == '\n' ? 1 : 0;
        }
        break;
    }

    if(endlines_seen > 1) { // done with one record (passport)!

      vector<string> necessary_labels = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}; // we don't include "cid" because it's optional.
      bool is_valid = true;
      for(ul i = 0; i < necessary_labels.size(); i++) {
        bool has_seen = false;
        for(ul j = 0; j < labels_seen.size(); j++) {
          if(necessary_labels[i] == labels_seen[j]) {
            has_seen = true;
            break;
          }
        }
        if(!has_seen) {
          is_valid = false;
          break;
        }
      }

      endlines_seen = 0;
      labels_seen = vector<string>();

      if(is_valid) {
        valid_count++;
      }
    }
  }

  cout << valid_count << endl;
}
