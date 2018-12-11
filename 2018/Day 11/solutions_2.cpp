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
  double power = ((x + 10) * y + serial) * (x + 10) % 1000;
  modf(power / 100, &power);
  power -= 5;

  return (int)power;
}

array<array<int, 300>, 300> build_grid(int serial) {
  array<array<int, 300>, 300> grid;
  for (int y = 0; y < 300; y++) {
    array<int, 300> line;
    for (int x = 0; x < 300; x++) {
      line[x] = power_cell(x + 1, y + 1, serial);
    }
    grid[y] = line;
  }

  return grid;
}

void largest_square(const array<array<int, 300>, 300> &grid) {
  int max_power = 0;
  int max_x;
  int max_y;
  int max_size;

  for (int size = 1; size <= 300; size++) {
    for (int x = 1; x <= 300 - size + 1; x++) {
      for (int y = 1; y <= 300 - size + 1; y++) {
        int power = 0;

        for (int i = 0; i < size; i++) {
          for (int j = 0; j < size; j++) {
            power += grid[y - 1 + j][x - 1 + i];
          }
        }

        if (power > max_power) {
          max_power = power;
          max_x = x;
          max_y = y;
          max_size = size;
        }
      }
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
