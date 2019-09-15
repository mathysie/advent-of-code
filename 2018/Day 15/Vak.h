#ifndef VAK_H
#define VAK_H

#include "Unit.h"
#include <cstddef>

using namespace std;

class Unit;

class Vak {
public:
  char val;
  pair<int, int> pos;
  Unit *unit;

  bool isBlocked();

  Vak(char c, unsigned int i, unsigned int j) : unit(NULL) {
    val = c;
    pos = make_pair(i, j);
  };
  // Units worden elders opgeruimd.
  ~Vak() { unit = NULL; };
  // Geen move of copy instructies toestaan.
  Vak(const Vak &) = delete;
  Vak &operator=(const Vak &) = delete;
  Vak(Vak &&) = delete;
  Vak &operator=(Vak &&) = delete;
};

#endif