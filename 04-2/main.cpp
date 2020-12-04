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

bool validate_range(string num, int min, int max) {
  int n = atoi(num.c_str());
  if(n < min || n > max)
    return false;
  return true;
}

bool validate_number_with_digit_count(string field, int count) {
  if(field.size() != count)
    return false;

  for(int i = 0; i < count; i++) {
    if(!isdigit(field[i])) {
      return false;
    }
  }
  return true;
}

bool validate_year_field(string field, int min, int max) {
  return validate_number_with_digit_count(field, 4) && validate_range(field, min, max);
}

bool validate(string field, string label) {
  // can't do a switch statement on a string, this is it translated to if-else
  if(label == "byr") {
    return validate_year_field(field, 1920, 2002);
  } else if(label == "iyr") {
    return validate_year_field(field, 2010, 2020);
  } else if(label == "eyr") {
    return validate_year_field(field, 2020, 2030);
  } else if(label == "hgt") {
    if(field[field.size()-2] == 'c' && field[field.size()-1] == 'm') {
      return validate_range(field, 150, 193);
    } else if(field[field.size()-2] == 'i' && field[field.size()-1] == 'n') {
      return validate_range(field, 59, 76);
    } else {
      return false;
    }
  } else if(label == "hcl") {
    if(field.size() != 7 || field[0] != '#') return false;

    for(int i = 1; i < 7; i++) {
      if(!isalpha(field[i]) && !isdigit(field[i])) {
        return false;
      }
    }
    return true;
  } else if(label == "ecl") {
    return field == "amb" ||
           field == "blu" ||
           field == "brn" ||
           field == "gry" ||
           field == "grn" ||
           field == "hzl" ||
           field == "oth";
  } else if(label == "pid") {
    return validate_number_with_digit_count(field, 9);
  } else if(label == "cid") {
    return true;
  } else {
    cout << "UNRECOGNIZED LABEL: " << label << endl;
    return false;
  }
}

int main() {
  ifstream input ("in.txt");


  State state = NONE;
  string label = "";
  string field = "";

  vector<string> labels_seen;
  int endlines_seen = 0;
  bool is_valid = true;

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
        if(!isspace(c)) {
          field.push_back(c);
        } else {
          state = NONE;
          labels_seen.push_back(label);

          // validation step 1 - ensure that the field is valid.
          if(!validate(field, label)) {
            //cout << "INVALID " << label << ":" << field << endl;
            is_valid = false;
          }

          label = "";
          field = "";
          endlines_seen = c == '\n' ? 1 : 0;
        }
        break;
    }

    if(endlines_seen > 1) { // done with one record (passport)!
      // make sure that all labels were used - validation step 2
      vector<string> necessary_labels = {"byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"}; // we don't include "cid" because it's optional.
      if(is_valid) { // so far
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
      }

      endlines_seen = 0;
      labels_seen = vector<string>();
      if(is_valid) {
        valid_count++;
      }
      is_valid = true;
    }
  }

  cout << valid_count << endl;
}
