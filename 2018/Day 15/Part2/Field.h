#ifndef FIELD_H
#define FIELD_H

#include "Vak.h"
#include <vector>

using namespace std;

class Vak;

class Field {
public:
  int distance(Vak *, Vak *, int) const;
  vector<vector<Vak *>> veld;
  void print();
};

#endif