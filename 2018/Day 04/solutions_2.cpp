#include <forward_list>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <string>

using namespace std;

forward_list<string> read_input() {
  forward_list<string> input;
  ifstream file("input.txt");
  string line;

  while (getline(file, line)) {
    input.push_front(line);
  }

  input.sort();

  return input;
}

map<int, array<int, 60>> fill_timetable(const forward_list<string> &input) {
  map<int, array<int, 60>> guards;
  int guard;
  int begin;
  regex pattern("Guard #([0-9]+)|([0-9]{2})] falls|([0-9]{2})] wakes");
  cmatch m;

  for (auto it = input.begin(); it != input.end(); it++) {
    regex_search(it->c_str(), m, pattern);

    if (it->find("Guard") != string::npos) {
      guard = stoi(m.str(1));
    } else if (it->find("falls") != string::npos) {
      begin = stoi(m.str(2));
    } else if (it->find("wakes") != string::npos) {
      int eind = stoi(m.str(3));

      if (guards.find(guard) == guards.end()) {
        array<int, 60> minutes;
        minutes.fill(0);
        guards.insert(pair<int, array<int, 60>>(guard, minutes));
      }

      for (int i = begin; i < eind; i++)
        guards[guard][i]++;
    }
  }

  return guards;
}

int laziest_guard_id(const forward_list<string> &input) {
  map<int, array<int, 60>> guards = fill_timetable(input);
  int laziest_id;
  int laziest_minutes = 0;
  int laziest_minute;

  // Finding max of array withing map of arrays with max_element is difficult,
  // thus we'll just iterate over every pair.
  for (auto it = guards.begin(); it != guards.end(); it++) {
    for (int i = 0; i < 60; i++) {
      if (it->second[i] > laziest_minutes) {
        laziest_id = it->first;
        laziest_minute = i;
        laziest_minutes = it->second[i];
      }
    }
  }

  return laziest_id * laziest_minute;
}

int main() {
  forward_list<string> input = read_input();
  int guard_id = laziest_guard_id(input);

  cout << guard_id << endl;

  return 0;
}
