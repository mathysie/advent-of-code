#include "Elf.h"
#include "Field.h"
#include "Goblin.h"
#include "Unit.h"
#include "Vak.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

void initialize(Field &field, list<Unit *> &units) {
  ifstream file("inputtest.txt");
  string line;
  for (unsigned int row = 0; getline(file, line); row++) {
    vector<Vak *> rij;
    for (unsigned int col = 0; col < line.size(); col++) {
      Vak *vak = new Vak(line[col], row, col);
      rij.push_back(vak);
      if (line[col] == 'E') {
        Unit *elf = new Elf(row, col, true);
        units.push_back(elf);
        vak->unit = elf;
      } else if (line[col] == 'G') {
        Goblin *goblin = new Goblin(row, col, false);
        units.push_back(goblin);
        vak->unit = goblin;
      }
    }

    field.veld.push_back(rij);
  }
}

void destroy(Field &field, list<Unit *> &units) {
  for (auto r : field.veld) {
    for (auto c : r) {
      delete c;
    }
  }
  for (auto u : units) {
    delete u;
  }
}

bool isElf(Unit *const &u) { return u->isElf; }

void round(Field &field, list<Unit *> &units) {
  units.sort([](Unit *&u, Unit *&v) { return *u < *v; });
  vector<Unit *> elves(Elf::n, NULL);
  vector<Unit *> goblins(Goblin::n, NULL);
  partition_copy(units.begin(), units.end(), elves.begin(), goblins.begin(),
                 isElf);
  for (auto u : units) {
    if (u->isElf) {
      u->turn(goblins, field);
    } else {
      u->turn(elves, field);
    }
  }
}

int Elf::n = 0;
int Goblin::n = 0;

int main() {
  auto start = chrono::high_resolution_clock::now();

  Field field;
  list<Unit *> units;

  initialize(field, units);

  field.print();

  for (int i = 0; i < 3; i++) {
    round(field, units);
    field.print();
  }

  destroy(field, units);

  display_time(start);
  return 0;
}
