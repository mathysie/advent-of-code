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
  void move(vector<Elf *> &, const Field &);

public:
  static int n;

  void turn(vector<Elf *> &, const Field &);
  void turn(vector<Goblin *> &, const Field &){};

  Goblin(int x, int y) : Unit(x, y) { n++; };
  ~Goblin() { n--; };
};

#endif