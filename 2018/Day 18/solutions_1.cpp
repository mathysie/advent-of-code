#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

char get_index(const vector<char> &v, int x, int y) {
  int N = (int)sqrt(v.size());
  if (x < 0 || y < 0 || x >= N || y >= N) {
    return 0;
  }

  return v[y + N * x];
}

vector<char> read_input() {
  vector<char> input;
  ifstream file("input.txt");
  string line;

  while (getline(file, line)) {
    for (auto c : line) {
      input.push_back(c);
    }
  }

  return input;
}

void run_iteration(vector<char> &area) {
  vector<char> copy = area;
  int N = (int)sqrt(copy.size());
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (get_index(copy, i, j) == '.') {
        int trees = 0;
        trees += get_index(copy, i - 1, j - 1) == '|';
        trees += get_index(copy, i - 1, j) == '|';
        trees += get_index(copy, i - 1, j + 1) == '|';
        trees += get_index(copy, i, j - 1) == '|';
        trees += get_index(copy, i, j + 1) == '|';
        trees += get_index(copy, i + 1, j - 1) == '|';
        trees += get_index(copy, i + 1, j) == '|';
        trees += get_index(copy, i + 1, j + 1) == '|';

        if (trees >= 3) {
          area[j + N * i] = '|';
        }
      } else if (get_index(copy, i, j) == '|') {
        int lumbers = 0;
        lumbers += get_index(copy, i - 1, j - 1) == '#';
        lumbers += get_index(copy, i - 1, j) == '#';
        lumbers += get_index(copy, i - 1, j + 1) == '#';
        lumbers += get_index(copy, i, j - 1) == '#';
        lumbers += get_index(copy, i, j + 1) == '#';
        lumbers += get_index(copy, i + 1, j - 1) == '#';
        lumbers += get_index(copy, i + 1, j) == '#';
        lumbers += get_index(copy, i + 1, j + 1) == '#';

        if (lumbers >= 3) {
          area[j + N * i] = '#';
        }
      } else if (get_index(copy, i, j) == '#') {
        int lumbers = 0;
        int trees = 0;

        trees += get_index(copy, i - 1, j - 1) == '|';
        trees += get_index(copy, i - 1, j) == '|';
        trees += get_index(copy, i - 1, j + 1) == '|';
        trees += get_index(copy, i, j - 1) == '|';
        trees += get_index(copy, i, j + 1) == '|';
        trees += get_index(copy, i + 1, j - 1) == '|';
        trees += get_index(copy, i + 1, j) == '|';
        trees += get_index(copy, i + 1, j + 1) == '|';

        lumbers += get_index(copy, i - 1, j - 1) == '#';
        lumbers += get_index(copy, i - 1, j) == '#';
        lumbers += get_index(copy, i - 1, j + 1) == '#';
        lumbers += get_index(copy, i, j - 1) == '#';
        lumbers += get_index(copy, i, j + 1) == '#';
        lumbers += get_index(copy, i + 1, j - 1) == '#';
        lumbers += get_index(copy, i + 1, j) == '#';
        lumbers += get_index(copy, i + 1, j + 1) == '#';

        if (lumbers == 0 || trees == 0) {
          area[j + N * i] = '.';
        }
      }
    }
  }
}

void run_area(vector<char> &area) {
  for (int i = 0; i < 10; i++) {
    run_iteration(area);
  }
}

int resource_value(const vector<char> &area) {
  int trees = 0;
  int lumbers = 0;

  for (auto c : area) {
    trees += c == '|';
    lumbers += c == '#';
  }

  return trees * lumbers;
}

int main() {
  vector<char> input = read_input();
  run_area(input);
  cout << resource_value(input) << endl;

  return 0;
}
