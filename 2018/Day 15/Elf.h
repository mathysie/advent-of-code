#ifndef ELF_H
#define ELF_H

#include "Unit.h"

class Unit;

class Elf : public Unit {
public:
  static int n;

  Elf(unsigned int x, unsigned int y, char c) : Unit(x, y, c) { n++; };
  ~Elf() { n--; };
};

#endif