#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <set>

using namespace std;

set<string> read_input() {
  set<string> input;
  ifstream file("input.txt");
  string line;

  while (getline(file, line)) {
    input.insert(line);
  }

  return input;
}

map<int, vector<int>> fill_timetable(set<string> input) {
  map<int, vector<int>> guards;
  int guard;
  regex pattern_begin("Guard #([0-9]+)");
  regex pattern_sleep("([0-9]{2})] falls asleep");
  regex pattern_wake("([0-9]{2})] wakes up");
  cmatch m;

  for (set<string>::iterator it = input.begin(); it != input.end(); it++) {
    if (regex_search((*it).c_str(), m, pattern_begin)) {
      guard = stoi(m.str(1));
    } else {
      int begin, eind;

      regex_search((*it).c_str(), m, pattern_sleep);
      begin = stoi(m.str(1));
      it++;
      regex_search((*it).c_str(), m, pattern_wake);
      eind = stoi(m.str(1));

      if (guards.find(guard) == guards.end()) {
        vector<int> minutes(60);
        fill(minutes.begin(), minutes.end(), 0);
        guards.insert(pair<int, vector<int>>(guard, minutes));
      }

      for (int i = begin; i < eind; i++)
        guards[guard][i]++;
    }
  }

  return guards;
}

int laziest_guard_id(set<string> input) {
  map<int, vector<int>> guards = fill_timetable(input);
  int laziest_id;
  int laziest_minutes = 0;

  for (map<int, vector<int>>::iterator it = guards.begin(); it != guards.end();
       it++) {
    int counter = 0;
    for (int i = 0; i < 60; i++) {
      counter += it->second[i];
    }
    if (counter > laziest_minutes) {
      laziest_id = it->first;
      laziest_minutes = counter;
    }
  }

  int laziest_minute;
  int times = 0;
  for (int i = 0; i < 60; i++) {
    if (guards[laziest_id][i] > times) {
      laziest_minute = i;
      times = guards[laziest_id][i];
    }
  }

  return laziest_id * laziest_minute;
}

int main() {
  set<string> input = read_input();
  int guard_id = laziest_guard_id(input);

  cout << guard_id << endl;

  return 0;
}
