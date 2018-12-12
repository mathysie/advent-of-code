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
  grid[0][0] = power_cell(1, 1, serial);

  for (int x = 1; x < 300; x++) {
    grid[0][x] = power_cell(x + 1, 1, serial) + grid[0][x - 1];
  }

  for (int y = 1; y < 300; y++) {
    grid[y][0] = power_cell(1, y + 1, serial) + grid[y - 1][0];

    for (int x = 1; x < 300; x++) {
      grid[y][x] = power_cell(x + 1, y + 1, serial) + grid[y - 1][x] +
                   grid[y][x - 1] - grid[y - 1][x - 1];
    }
  }

  return grid;
}

void update_max_power(int &max_power, int power, int &max_x, int x,
                      int &max_y, int y) {
  max_power = power;
  max_x = x;
  max_y = y;
}

int *best_square(const array<array<int, 300>, 300> &grid, int size) {
  int max_power = grid[size - 1][size - 1];
  int max_x = 1;
  int max_y = 1;

  for (int x = 2; x <= 300 - size + 1; x++) {
    int power = grid[size - 1][x - 2 + size] - grid[size - 1][x - 2];
    if (power > max_power) {
      update_max_power(max_power, power, max_x, x, max_y, 1);
    }
  }

  for (int y = 2; y <= 300 - size + 1; y++) {
    int power = grid[y - 2 + size][size - 1] - grid[y - 2][size - 1];
    if (power > max_power) {
      update_max_power(max_power, power, max_x, 1, max_y, y);
    }
  }

  for (int x = 2; x <= 300 - size + 1; x++) {
    for (int y = 2; y <= 300 - size + 1; y++) {
      int power = grid[y - 2 + size][x - 2 + size] - grid[y - 2 + size][x - 2] -
                  grid[y - 2][x - 2 + size] + grid[y - 2][x - 2];

      if (power > max_power) {
        update_max_power(max_power, power, max_x, x, max_y, y);
      }
    }
  }

  static int res[3];
  res[0] = max_power, res[1] = max_x, res[2] = max_y;

  return res;
}

void largest_square(const array<array<int, 300>, 300> &grid) {
  int max_size;
  int max_x;
  int max_y;
  int max_power = 0;

  for (int size = 1; size <= 300; size++) {
    int* res = best_square(grid, size);
    if (res[0] > max_power) {
      update_max_power(max_power, res[0], max_x, res[1], max_y, res[2]);
      max_size = size;
    }
  }

  cout << max_x << "," << max_y << "," << max_size << endl;
}

int main() {
  int input = read_input();
  array<array<int, 300>, 300> grid = build_grid(input);

  largest_square(grid);

  return 0;
}
