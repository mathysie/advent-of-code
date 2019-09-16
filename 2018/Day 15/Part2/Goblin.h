#ifndef GOBLIN_H
#define GOBLIN_H

#include "Unit.h"

class Goblin : public Unit {
public:
  static int n;

  Goblin(unsigned int x, unsigned int y, char c) : Unit(x, y, c) { n++; };
  ~Goblin() { n--; };
};

#endif