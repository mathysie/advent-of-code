#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int sum(unordered_map<char, unordered_set<char>> map) {
  int counter = 0;
  for (auto pair : map) {
    counter += pair.second.size();
  }

  return counter;
}

unordered_map<char, unordered_set<char>> read_input() {
  unordered_map<char, unordered_set<char>> input;
  string line;
  ifstream file("input.txt");

  while (getline(file, line)) {
    char x;
    char y;
    sscanf(line.c_str(), "Step %s must be finished before step %s can begin.",
           &x, &y);
    if (input.find(x) == input.end()) {
      unordered_set<char> z;
      z.insert(y);
      input.insert(make_pair(x, z));
    } else {
      input[x].insert(y);
    }
  }

  unordered_map<char, unordered_set<char>> copy = {};
  while (sum(copy) != sum(input)) {
    copy = input;
    for (auto pair : input) {
      for (auto c : pair.second) {
        if (input.find(c) != input.end()) {
          input[pair.first].insert(input[c].begin(), input[c].end());
        }
      }
    }
  }

  return input;
}

list<char>
initialize_queue(const unordered_map<char, unordered_set<char>> &paths) {
  list<char> queue;
  for (auto pair : paths) {
    if (find(queue.begin(), queue.end(), pair.first) == queue.end()) {
      queue.push_back(pair.first);
    }
    for (auto c : pair.second) {
      if (find(queue.begin(), queue.end(), c) == queue.end()) {
        queue.push_back(c);
      }
    }
  }

  return queue;
}

list<char> build_queue(const unordered_map<char, unordered_set<char>> &paths) {
  list<char> queue = initialize_queue(paths);

  queue.sort([paths](char x, char y) {
    if (paths.find(x) != paths.end() &&
        paths.at(x).find(y) != paths.at(x).end()) {
      return true;
    } else if (paths.find(y) != paths.end() &&
               paths.at(y).find(x) != paths.at(y).end()) {
      return false;
    }

    return x < y;
  });

  return queue;
}

int main() {
  unordered_map<char, unordered_set<char>> input = read_input();
  list<char> queue = build_queue(input);

  for (auto pair : input) {
    cout << pair.first << ":";
    for (auto i : pair.second)
      cout << " " << i;
    cout << endl;
  }

  for (auto c : queue)
    cout << c;
  cout << endl;

  return 0;
}
