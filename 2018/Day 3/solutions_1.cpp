#include <array>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

const int N = 1000;

array<array<char, N>, N> create_fabric() {
  array<array<char, N>, N> fabric;

  for (int i = 0; i < N; i++) {
    array<char, N> slice;
    slice.fill('.');
    fabric[i] = slice;
  }

  return fabric;
}

array<array<char, N>, N> fill_fabric(array<array<char, N>, N> fabric,
                                     string line) {
  int xpos, ypos, x, y;
  sscanf(line.c_str(), "#%*d @ %d,%d: %dx%d", &xpos, &ypos, &x, &y);

  for (int i = xpos; i < xpos + x; i++) {
    for (int j = ypos; j < ypos + y; j++) {
      if (fabric[i][j] == '.') {
        fabric[i][j] = '#';
      } else if (fabric[i][j] == '#') {
        fabric[i][j] = '&';
      }
    }
  }

  return fabric;
}

int count_overlap(array<array<char, N>, N> fabric) {
  int overlap = 0;

  for (unsigned int i = 0; i < fabric.size(); i++) {
    for (unsigned int j = 0; j < fabric[i].size(); j++) {
      if (fabric[i][j] == '&') {
        overlap++;
      }
    }
  }

  return overlap;
}

int main() {
  string line;
  ifstream file("input.txt");
  array<array<char, N>, N> fabric = create_fabric();

  while (getline(file, line)) {
    fabric = fill_fabric(fabric, line);
  }

  file.close();

  cout << count_overlap(fabric) << endl;

  return 0;
}
