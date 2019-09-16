#include "Vak.h"
#include <cstdlib>

using namespace std;

bool Vak::isBlocked() { return val != '.'; }

int Vak::man_dist(const Vak &v) {
  return abs(pos.first - v.pos.first) + abs(pos.second - v.pos.second);
}