#ifndef GOBLIN_H
#define GOBLIN_H

#include "Elf.h"
#include "Field.h"
#include "Unit.h"
#include <vector>

using namespace std;

class Elf;

class Field;

class Unit;

class Goblin : public Unit {
  vector<pair<int, int>> find_targets(const vector<Elf *> &, const Field &);
  void move(vector<Elf *> &, Field &);

public:
  static int n;

  void turn(vector<Elf *> &, Field &);
  void turn(vector<Goblin *> &, Field &){};

  Goblin(int x, int y) : Unit(x, y) { n++; };
  ~Goblin() { n--; };
};

#endif