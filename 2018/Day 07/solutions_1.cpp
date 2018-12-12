#include <fstream>
#include <iostream>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

unordered_map<char, unordered_set<char>> read_input() {
  unordered_map<char, unordered_set<char>> input;
  string line;
  ifstream file("input.txt");

  while (getline(file, line)) {
    char x;
    char y;
    sscanf(line.c_str(), "Step %s must be finished before step %s can begin.",
           &x, &y);
    if (input.find(y) == input.end()) {
      unordered_set<char> z;
      z.insert(x);
      input.insert(make_pair(y, z));
    } else {
      input[y].insert(x);
    }
    if (input.find(x) == input.end()) {
      input.insert(make_pair(x, unordered_set<char>{}));
    }
  }

  return input;
}

string create_order(unordered_map<char, unordered_set<char>> depends) {
  set<char> free;
  string res = "";
  while (depends.size() != 0) {
    // Voeg vrije waarden toe.
    for (auto it = depends.begin(); it != depends.end(); it++) {
      if (it->second.size() == 0) {
        free.insert(it->first);
      }
    }
    // Verwijder vrije waarden uit depends.
    for (auto c : free) {
      if (depends.find(c) != depends.end()) {
        depends.erase(c);
      }
    }

    char x = *(free.begin());
    res += x;
    free.erase(free.begin());
    for (auto pair : depends) {
      if (pair.second.find(x) != pair.second.end()) {
        depends[pair.first].erase(x);
      }
    }
  }

  return res;
}

int main() {
  unordered_map<char, unordered_set<char>> input = read_input();
  string steps = create_order(input);

  cout << steps << endl;

  return 0;
}
