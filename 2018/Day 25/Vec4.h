#ifndef VEC4_H
#define VEC4_H

#include "Constellation.h"
#include <cstddef>

class Constellation;

class Vec4 {
public:
  int x, y, z, w;
  Constellation *c;
  int dist(const Vec4 &);
  void print () const;

  Vec4(int a, int b, int c, int d) : c(NULL) {
    x = a, y = b, z = c, w = d;
  };
};

#endif
