#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include <vector>
#include "Vec4.h"

using namespace std;

class Vec4;

class Constellation {
public:
  vector<Vec4*> vecs;
  static int n;

  Constellation() {n++;};
  ~Constellation() {n--;};
};

#endif