#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> read_input() {
  string line;
  ifstream file("input.txt");
  vector<vector<char>> lines = {};

  while (getline(file, line)) {
    vector<char> chars = {};

    for (char &c : line) {
      chars.push_back(c);
    }

    lines.push_back(chars);
  }

  return lines;
}

vector<char> compute_id(vector<vector<char>> lines) {
  for (unsigned int i = 0; i < lines.size(); i++) {
    for (unsigned int j = i + 1; j < lines.size(); j++) {
      int count = 0;
      int index;
      for (unsigned int k = 0; k < lines[i].size(); k++) {
        if (lines[i][k] != lines[j][k]) {
          count++;
          index = k;
        }
      }
      if (count == 1) {
        vector<char> output = lines[i];
        output.erase(output.begin() + index);

        return output;
      }
    }
  }

  return vector<char>{};
}

int main() {
  vector<vector<char>> lines = read_input();
  vector<char> box_id = compute_id(lines);

  if (!box_id.empty()) {
    for (char c : box_id)
    cout << c;
    cout << endl;
  } else {
    cout << "Geen box_id gevonden.";
  }

  return 0;
}