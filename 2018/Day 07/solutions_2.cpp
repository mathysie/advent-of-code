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
    sscanf(line.c_str(), "Step %s must be finished before step %s can begin.", &x, &y);

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

bool workers_busy(vector<pair<char, int>> workers) {
  for (unsigned int i = 0; i < workers.size(); i++) {
    if (workers[i].first != '.') {
      return true;
    }
  }

  return false;
}

int work_time(unordered_map<char, unordered_set<char>> depends) {
  set<char> free;
  int N = 5;
  vector<pair<char, int>> workers = {{'.', 0}, {'.', 0}, {'.', 0}, {'.', 0}, {'.', 0}};
  int time = -1;

  do {
    time++;

    // Geef werknemers vrij als hun taak af is.
    for (int i = 0; i < N; i++) {
      if (workers[i].second + 1 <= time) {
        for (auto pair : depends) {
          if (pair.second.find(workers[i].first) != pair.second.end()) {
            depends[pair.first].erase(workers[i].first);
          }
        }
        workers[i].first = '.';
      }
    }

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

    // Geef werknemers die niets doen werk.
    if (free.size() != 0) {
      auto it_free = free.begin();
      for (int i = 0; i < N && it_free != free.end(); i++) {
        if (workers[i].first == '.') {
          workers[i].first = *(it_free);
          workers[i].second = *(it_free) + 60 - 'A' + time;
          it_free = free.erase(it_free);
        }
      }
    }
  } while (workers_busy(workers));

  return time;
}

int main() {
  unordered_map<char, unordered_set<char>> input = read_input();
  int seconds = work_time(input);

  cout << seconds << endl;

  return 0;
}
