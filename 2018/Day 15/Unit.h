#ifndef UNIT_H
#define UNIT_H

#include <utility>

using namespace std;

class Unit {
  int hp;
  int ap;

public:
  pair<int, int> pos;
  Unit(int x, int y) : hp(200), ap(3) { pos = make_pair(x, y); };
};

#endif