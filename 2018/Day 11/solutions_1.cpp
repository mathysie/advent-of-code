#include <array>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

int read_input() {
  ifstream file("input.txt");
  string line;

  getline(file, line);

  return stoi(line);
}

int power_cell(int x, int y, int serial) {
  return ((x + 10) * y + serial) * (x + 10) % 1000 / 100 - 5;
}

array<array<int, 300>, 300> build_grid(int serial) {
  array<array<int, 300>, 300> grid;

  for (int y = 0; y < 300; y++) {
    array<int, 300> line;

    for (int x = 0; x < 300; x++) {
      if (y == 0) {
        if (x == 0) {
          line[x] = power_cell(x + 1, y + 1, serial);
        } else {
          line[x] = line[x - 1] + power_cell(x + 1, y + 1, serial);
        }
      } else {
        if (x == 0) {
          line[x] = grid[y - 1][x] + power_cell(x + 1, y + 1, serial);
        } else {
          line[x] = grid[y - 1][x] + line[x - 1] - grid[y - 1][x - 1] +
                    power_cell(x + 1, y + 1, serial);
        }
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
      int power;

      if (x == 1 && y == 1) {
        power = grid[0][0];
      } else if (x == 1) {
        power = grid[y + 1][x + 1] - grid[y - 2][x + 1];
      } else if (y == 1) {
        power = grid[y + 1][x + 1] - grid[y + 1][x - 2];
      } else {
        power = grid[y + 1][x + 1] - grid[y + 1][x - 2] - grid[y - 2][x + 1] +
                grid[y - 2][x - 2];
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
