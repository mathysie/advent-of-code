#include <array>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;

const int N = 1000;

array<array<int, N>, N> *create_fabric() {
  array<array<int, N>, N> *fabric = new array<array<int, N>, N>;

  for (int i = 0; i < N; i++) {
    array<int, N> slice;
    slice.fill(0);
    (*fabric)[i] = slice;
  }

  return fabric;
}

array<array<int, N>, N> *fill_fabric(array<array<int, N>, N> *fabric,
                                     string line) {
  int id, xpos, ypos, x, y;
  sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id, &xpos, &ypos, &x, &y);

  for (int i = xpos; i < xpos + x; i++) {
    for (int j = ypos; j < ypos + y; j++) {
      (*fabric)[i][j]++;
    }
  }

  return fabric;
}

bool detect_no_claim(array<array<int, N>, N> *fabric, string line) {
  int id, xpos, ypos, x, y;
  sscanf(line.c_str(), "#%d @ %d,%d: %dx%d", &id, &xpos, &ypos, &x, &y);

  for (int i = xpos; i < xpos + x; i++) {
    for (int j = ypos; j < ypos + y; j++) {
      if ((*fabric)[i][j] != 1) {
        return false;
      }
    }
  }

  return true;
}

int main() {
  string line;
  ifstream file("input.txt");
  array<array<int, N>, N> *fabric = create_fabric();

  while (getline(file, line)) {
    fabric = fill_fabric(fabric, line);
  }

  file.close();
  file.open("input.txt");

  int id = 0;
  while (getline(file, line)) {
    if (detect_no_claim(fabric, line)) {
      sscanf(line.c_str(), "#%d", &id);
      break;
    }
  }

  delete fabric;

  file.close();
  if (id == 0) {
    cout << "Geen unieke id gevonden.\n";
  } else {
    cout << id << endl;
  }

  return 0;
}
