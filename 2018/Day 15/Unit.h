#ifndef UNIT_H
#define UNIT_H

#include "Field.h"
#include <utility>
#include <vector>

using namespace std;

class Elf;

class Field;

class Goblin;

class Unit {
  int ap;

public:
  int hp;
  pair<unsigned int, unsigned int> pos;

  virtual void turn(vector<Elf *> &, Field &) = 0;
  virtual void turn(vector<Goblin *> &, Field &) = 0;

  Unit(unsigned int x, unsigned int y) : ap(3), hp(200) {
    pos = make_pair(x, y);
  };
  virtual ~Unit(){};
};

#endif