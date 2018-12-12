#include <array>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

int read_input() {
  ifstream file("input.txt");
  int x;
  file >> x;

  return x;
}

int power_cell(int x, int y, int serial) {
  return ((x + 10) * y + serial) * (x + 10) % 1000 / 100 - 5;
}

array<array<int, 300>, 300> build_grid(int serial) {
  array<array<int, 300>, 300> grid;

  for (int y = 0; y < 300; y++) {
    array<int, 300> line;

    for (int x = 0; x < 300; x++) {
      line[x] = power_cell(x + 1, y + 1, serial);

      if (y != 0) {
        line[x] += grid[y - 1][x];
      }
      if (x != 0) {
        line[x] += line[x - 1];
      }
      if (x != 0 && y != 0) {
        line[x] -= grid[y - 1][x - 1];
      }
    }

    grid[y] = line;
  }

  return grid;
}

void largest_square(const array<array<int, 300>, 300> &grid) {
  int max_power = 0;
  int max_x;
  int max_y;

  for (int x = 1; x <= 298; x++) {
    for (int y = 1; y <= 298; y++) {
      int power = grid[y + 1][x + 1];

      if (x != 1) {
        power -= grid[y + 1][x - 2];
      }
      if (y != 1) {
        power -= grid[y - 2][x + 1];
      }
      if (x != 1 && y != 1) {
        power += grid[y - 2][x - 2];
      }

      if (power > max_power) {
        max_power = power;
        max_x = x;
        max_y = y;
      }
    }
  }

  cout << max_x << "," << max_y << endl;
}

int main() {
  int input = read_input();
  array<array<int, 300>, 300> grid = build_grid(input);

  largest_square(grid);

  return 0;
}
