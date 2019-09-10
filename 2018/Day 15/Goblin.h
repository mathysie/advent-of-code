#ifndef GOBLIN_H
#define GOBLIN_H

#include "Elf.h"
#include "Unit.h"
#include <vector>

using namespace std;

class Elf;

class Unit;

class Goblin : public Unit {
public:
  static int n;

  void turn(vector<Elf *> &) {};
  void turn(vector<Goblin *> &) {};

  Goblin(int x, int y) : Unit(x, y) { n++; };
  ~Goblin() { n--; };
};

#endif