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

void largest_square(int serial) {
  int max_power = 0;
  int max_x;
  int max_y;

  for (int x = 1; x <= 298; x++) {
    for (int y = 1; y <= 298; y++) {
      int power = 0;
      
      for (int i = 0; i <3; i++) {
        for (int j = 0; j < 3; j++) {
          power += power_cell(x+i, y+j, serial);
        }
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

  largest_square(input);

  return 0;
}
