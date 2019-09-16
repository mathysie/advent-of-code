#ifndef UNIT_H
#define UNIT_H

#include "Field.h"
#include "Vak.h"
#include <forward_list>
#include <utility>
#include <unordered_set>

using namespace std;

class Field;

class Vak;

class Unit {
  int ap;

  forward_list<Vak *> find_targets(const unordered_set<Unit *> &, const Field &);
  Vak *find_closest(const unordered_set<Unit *> &, const Field &);
  pair<int, int> find_dest(Vak *, const Field &);
  void move(const unordered_set<Unit *> &, Field &);
  Unit* aim(const Field &);
  void attack(unordered_set<Unit *> &, Field &);

public:
  void turn(unordered_set<Unit *> &, Field &);

  int hp;
  bool isElf;
  pair<unsigned int, unsigned int> pos;

  Unit(unsigned int x, unsigned int y, bool elf) : ap(3), hp(200) {
    pos = make_pair(x, y);
    isElf = elf;
  };
  virtual ~Unit(){};

  bool operator<(const Unit &u) {
    return pos.first < u.pos.first ||
           (pos.first == u.pos.first && pos.second < u.pos.second);
  }
};

#endif