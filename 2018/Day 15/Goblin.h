#ifndef GOBLIN_H
#define GOBLIN_H

#include "Unit.h"

using namespace std;

class Goblin : public Unit {
public:
  static int n;
  Goblin(int x, int y) : Unit(x, y) { n++; };
  ~Goblin() { n--; };
};

#endif