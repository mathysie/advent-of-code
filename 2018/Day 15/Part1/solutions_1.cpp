#include "Field.h"
#include "Unit.h"
#include "Vak.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

void initialize(Field &field, list<Unit *> &units) {
  ifstream file("input.txt");
  string line;
  for (unsigned int row = 0; getline(file, line); row++) {
    vector<Vak *> rij;
    for (unsigned int col = 0; col < line.size(); col++) {
      Vak *vak = new Vak(line[col], row, col);
      rij.push_back(vak);
      if (line[col] == 'E') {
        Unit *elf = new Unit(row, col, true);
        units.push_back(elf);
        vak->unit = elf;
      } else if (line[col] == 'G') {
        Unit *goblin = new Unit(row, col, false);
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

void clean(list<Unit* >&units) {
  for (auto it = units.begin(); it != units.end(); it++) {
    if ((*it)->hp <= 0) {
      auto it2 = it;
      it--;
      delete *it2;
      units.erase(it2);
    }
  }
}

bool isElf(Unit *const &u) { return u->isElf; }

void round(Field &field, list<Unit *> &units, bool & finish) {
  units.sort([](Unit *&u, Unit *&v) { return *u < *v; });
  unordered_set<Unit *> elves;
  unordered_set<Unit *> goblins;
  for (auto u : units) {
    if (u->isElf) {
      elves.insert(u);
    } else {
      goblins.insert(u);
    }
  }

  for (auto u : units) {
    if (u->hp <= 0) {
      continue;
    }
    if (elves.size() == 0 || goblins.size() == 0) {
      finish = true;
      clean(units);
      return;
    }
    if (u->isElf) {
      u->turn(goblins, field);
    } else {
      u->turn(elves, field);
    }
  }

  clean(units);
}

int count_hp(list<Unit *> units) {
  int hp = 0;
  for (auto u : units) {
    hp += u->hp;
  }

  return hp;
}

int main() {
  auto start = chrono::high_resolution_clock::now();

  Field field;
  list<Unit *> units;

  initialize(field, units);

  int count = 0;
  bool finish = false;
  while (!finish) {
    round(field, units, finish);
    if (!finish) {
      count++;
    }
  }

  int hp = count_hp(units);
  cout << "Afgelopen op ronde: " << count << ".\n";
  cout << "HP is " << hp << ".\n";
  cout << "Resultaat: " << count * hp << ".\n";

  destroy(field, units);

  display_time(start);
  return 0;
}
