#ifndef CONSTELLATION_H
#define CONSTELLATION_H

#include "Vec4.h"
#include <vector>

using namespace std;

class Vec4;

class Constellation {
public:
  vector<Vec4 *> vecs;
  static int n;

  Constellation(Vec4* v) { vecs.push_back(v), n++; };
  ~Constellation() { n--; };
};

#endif