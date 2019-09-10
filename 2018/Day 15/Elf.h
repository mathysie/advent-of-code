#ifndef ELF_H
#define ELF_H

#include "Goblin.h"
#include "Unit.h"
#include <vector>

using namespace std;

class Goblin;

class Unit;

class Elf : public Unit {
public:
  static int n;

  void turn(vector<Elf *> &) {};
  void turn(vector<Goblin *> &) {};

  Elf(int x, int y) : Unit(x, y) { n++; };
  ~Elf() { n--; };
};

#endif