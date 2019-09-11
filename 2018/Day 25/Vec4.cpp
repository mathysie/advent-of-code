#include "Vec4.h"
#include <cstdlib>
#include <iostream>

using namespace std;

int Vec4::dist(const Vec4 &v) {
  return abs(v.x - x) + abs(v.y - y) + abs(v.z - z) + abs(v.w - w);
}

void Vec4::print() const {
  cout << x << '\t' << y << '\t' << z << '\t' << w << '\n';
}