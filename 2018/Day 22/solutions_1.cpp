#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

pair<int, int> read_input(int &depth) {
  ifstream file("input.txt");
  string line;

  getline(file, line);
  sscanf(line.c_str(), "depth: %d", &depth);

  int x, y;
  getline(file, line);
  sscanf(line.c_str(), "target: %d,%d", &x, &y);

  return make_pair(x, y);
}

vector<vector<int>> fill_cave(int depth, pair<int, int> target) {
  vector<vector<int>> cave (target.second+1);

  cave[0].push_back(depth % 20183);
  for(int x = 1; x <= target.first; x++) {
    cave[0].push_back((x * 16807 + depth) % 20183);
  }

  for (int y = 1; y <= target.second; y++) {
    cave[y].push_back((y * 48271 + depth) % 20183);
  }

  for (int y = 1; y <= target.second; y++) {
    for (int x = 1; x <= target.first; x++) {
      cave[y].push_back((cave[y-1][x] * cave[y][x-1] + depth) % 20183);
    }
  }

  cave[target.second][target.first] = depth % 20183;

  return cave;
}

int total_risk(int depth, pair<int, int> target) {
  vector<vector<int>> cave = fill_cave(depth, target);
  int risk = 0;

  for (auto rule : cave) {
    for (auto r : rule) {
      risk += r % 3;
    }
  }

  return risk;
}

int main() {
  int depth = 0;
  pair<int, int> target = read_input(depth);

  cout << total_risk(depth, target) << endl;

  return 0;
}
