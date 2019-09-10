#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum types {
  radiation = 0b1,
  bludgeoning = 0b10,
  slashing = 0b100,
  cold = 0b1000,
  fire = 0b10000
};

types parse(string type) {
  if (type == "radiation")
    return radiation;
  if (type == "bludgeoning")
    return bludgeoning;
  if (type == "slashing")
    return slashing;
  if (type == "cold")
    return cold;
  if (type == "fire")
    return fire;
}

int parse_elements(string elements) {
  int elems = 0;
  stringstream ss(elements);
  string token;

  while (getline(ss, token, ',')) {
    if (token[0] == ' ') {
      token.erase(0, 1);
    }
    elems |= (int)parse(token);
  }

  return elems;
}

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

void create_team(ifstream &file, const regex &pattern,
                 list<vector<int>> &team) {
  string line;

  while (getline(file, line) && !line.empty()) {
    cmatch match;
    regex_search(line.c_str(), match, pattern);

    vector<int> group{
        stoi(match[1].str()),  stoi(match[2].str()), 0, 0, stoi(match[7].str()),
        parse(match[8].str()), stoi(match[9].str()), 0};
    if (!match[3].str().empty()) {
      group[2] = parse_elements(match[3].str());
    } else if (!match[5].str().empty()) {
      group[2] = parse_elements(match[5].str());
    }
    if (!match[4].str().empty()) {
      group[3] = parse_elements(match[4].str());
    } else if (!match[6].str().empty()) {
      group[3] = parse_elements(match[6].str());
    }

    team.push_back(group);
  }
}

// Group info: Aantal, HP, weak, immune, AP, element, initiative, target
pair<list<vector<int>>, list<vector<int>>> read_input() {
  ifstream file("inputtest.txt");
  string line;
  pair<list<vector<int>>, list<vector<int>>> teams;
  regex pattern("([0-9]+) units each with ([0-9]+) hit points(?: \\((?:(?:weak "
                "to ([a-z, ]+))|(?:immune to ([a-z, ]+)))(?:; (?:(?:weak to "
                "([a-z, ]+))|(?:immune to ([a-z, ]+))))?\\))? with an attack "
                "that does ([0-9]+) ([a-z]+) damage at initiative ([0-9]+)");

  getline(file, line);
  list<vector<int>> immune;
  create_team(file, pattern, immune);
  getline(file, line);
  list<vector<int>> infection;
  create_team(file, pattern, infection);

  return make_pair(immune, infection);
}

bool sort_op(const vector<int> &x, const vector<int> &y) {
  if (x[0] * x[4] == y[0] * [4])
    return x[6] < y[6];
  return x[0] * x[4] < y[0] * y[4];
}

void fight(pair<list<vector<int>>, list<vector<int>>> &teams) {
  while (teams.first.size() != 0 && teams.first.size() != 0) {
    // Target phase
    teams.first.sort(sort_ep);
    
  }
}

int main() {
  auto start = chrono::high_resolution_clock::now();
  pair<list<vector<int>>, list<vector<int>>> teams = read_input();

  fight(teams);

  cout << teams.first.size() << " " << teams.second.size() << endl;

  display_time(start);
  return 0;
}
