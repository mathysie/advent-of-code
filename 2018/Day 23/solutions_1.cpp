#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  cout << duration.count() << " microseconds" << endl;
}

void read_input(vector<array<int, 4>> &bots) {
  ifstream file("input.txt");
  string line;

  while (getline(file, line)) {
    int x, y, z, r;
    sscanf(line.c_str(), "pos=<%d,%d,%d>, r=%d", &x, &y, &z, &r);
    bots.push_back(array<int, 4>{x, y, z, r});
  }

  file.close();
}

bool radius(const array<int, 4> &x, const array<int, 4> &y) {
  return x[3] < y[3];
}

int manhattan_dist(const array<int, 4> &x, const array<int, 4> &y) {
  return abs(x[0] - y[0]) + abs(x[1] - y[1]) + abs(x[2] - y[2]);
}

long bots_in_range(const vector<array<int, 4>> &bots) {
  array<int, 4> strongest = *max_element(bots.begin(), bots.end(), radius);

  return count_if(bots.begin(), bots.end(),
                  [strongest](const array<int, 4> &x) {
                    return manhattan_dist(x, strongest) <= strongest[3];
                  });
}

int main() {
  auto start = chrono::high_resolution_clock::now();

  vector<array<int, 4>> bots;
  read_input(bots);

  cout << bots_in_range(bots) << endl;

  display_time(start);
  return 0;
}
