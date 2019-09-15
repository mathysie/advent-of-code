#include "Elf.h"
#include "Field.h"
#include "Goblin.h"
#include "Unit.h"
#include "Vak.h"
#include <algorithm>
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

void initialize(Field &field, vector<Elf *> &elves, vector<Goblin *> &goblins) {
  ifstream file("input.txt");
  string line;
  for (unsigned int row = 0; getline(file, line); row++) {
    vector<Vak *> rij;
    for (unsigned int col = 0; col < line.size(); col++) {
      Vak *vak = new Vak(line[col], row, col);
      rij.push_back(vak);
      if (line[col] == 'E') {
        Elf *elf = new Elf(row, col);
        elves.push_back(elf);
        vak->unit = elf;
      } else if (line[col] == 'G') {
        Goblin *goblin = new Goblin(row, col);
        goblins.push_back(goblin);
        vak->unit = goblin;
      }
    }

    field.veld.push_back(rij);
  }
}

void destroy(Field &field, vector<Elf *> &elves, vector<Goblin *> &goblins) {
  for (auto r : field.veld) {
    for (auto c : r) {
      delete c;
    }
  }
  for (auto e : elves) {
    delete e;
  }
  for (auto g : goblins) {
    delete g;
  }
}

void round(Field &field, vector<Elf *> &elves,
           vector<Goblin *> &goblins) {
  for (unsigned int i = 0; i < field.veld.size(); i++) {
    for (unsigned int j = 0; j < field.veld[0].size(); j++) {
      if (field.veld[i][j]->unit == NULL) {
        continue;
      } else if (field.veld[i][j]->val == 'E') {
        Unit *elf = field.veld[i][j]->unit;
        elf->turn(goblins, field);
      } else if (field.veld[i][j]->val == 'G') {
        Unit *goblin = field.veld[i][j]->unit;
        goblin->turn(elves, field);
      }
    }
  }
}

int Elf::n = 0;
int Goblin::n = 0;

int main() {
  auto start = chrono::high_resolution_clock::now();

  Field field;
  vector<Elf *> elves;
  vector<Goblin *> goblins;

  initialize(field, elves, goblins);

  field.print();

  for (int i = 0; i < 4; i++) {
    round(field, elves, goblins);
    field.print();
  }

  destroy(field, elves, goblins);

  display_time(start);
  return 0;
}
