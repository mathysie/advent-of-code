#ifndef ELF_H
#define ELF_H

#include "Field.h"
#include "Goblin.h"
#include "Unit.h"
#include <vector>

using namespace std;

class Field;

class Goblin;

class Unit;

class Elf : public Unit {
  vector<pair<int, int>> find_targets(const vector<Goblin *> &, const Field &);
  vector<pair<int, int>> find_targets(const vector<Goblin *> &, const Field &);
  void move(vector<Goblin *> &, const Field &);

public:
  static int n;

  void turn(vector<Elf *> &, const Field &){};
  void turn(vector<Goblin *> &, const Field &);

  Elf(int x, int y) : Unit(x, y) { n++; };
  ~Elf() { n--; };
};

#endif