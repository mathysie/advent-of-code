#include "Elf.h"
#include "Field.h"
#include "Goblin.h"
#include "Unit.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

void initialize(Field &field, vector<Unit *> &elves, vector<Unit *> &goblins) {
  ifstream file("input.txt");
  string line;
  int row = 0;
  while (getline(file, line)) {
    field.veld.push_back(line);
    for (unsigned int col = 0; col < line.size(); col++) {
      if (line[col] == 'E') {
        Unit *elf = new Elf(row, col);
        elves.push_back(elf);
      } else if (line[col] == 'G') {
        Unit *goblin = new Goblin(row, col);
        goblins.push_back(goblin);
      }
    }

    row++;
  }
}

void destroy(vector<Unit *> &elves, vector<Unit *> &goblins) {
  for (auto e : elves) {
    delete e;
  }
  for (auto g : goblins) {
    delete g;
  }
}

void round(const Field &field, vector<Unit *> &elves, vector<Unit *> &goblins) {
  for (unsigned int i = 0; i < field.veld.size(); i++) {
    for (unsigned int j = 0; j < field.veld[0].size(); j++) {
      if (field.veld[i][j] == '.' || field.veld[i][j] == '#') {
        continue;
      }
    }
  }
}

int Elf::n = 0;
int Goblin::n = 0;

int main() {
  auto start = chrono::high_resolution_clock::now();

  Field field;
  vector<Unit *> elves;
  vector<Unit *> goblins;

  initialize(field, elves, goblins);

  for (int i = 0; i < 10; i++) {
    round(field, elves, goblins);

    // field.print();
  }

  destroy(elves, goblins);

  display_time(start);
  return 0;
}
