#ifndef ELF_H
#define ELF_H

#include "Field.h"
#include "Goblin.h"
#include "Unit.h"
#include "Vak.h"
#include <vector>

using namespace std;

class Field;

class Goblin;

class Unit;

class Vak;

class Elf : virtual public Unit {
  vector<Vak*> find_targets(const vector<Goblin *> &, const Field &);
  Vak* find_closest(const vector<Goblin *> &, const Field &);
  pair<int, int> find_dest(Vak *, const Field &);
  void move(const vector<Goblin *> &, Field &);

public:
  static int n;

  void turn(vector<Elf *> &, Field &){};
  void turn(vector<Goblin *> &, Field &);

  Elf(int x, int y) : Unit(x, y) { n++; };
  ~Elf() { n--; };
};

#endif