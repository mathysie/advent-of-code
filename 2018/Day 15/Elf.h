#ifndef ELF_H
#define ELF_H

#include "Unit.h"

using namespace std;

class Elf : public Unit {
public:
  static int n;
  Elf(int x, int y) : Unit(x, y) { n++; };
  ~Elf() { n--; };
};

#endif