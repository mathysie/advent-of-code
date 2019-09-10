#ifndef FIELD_H
#define FIELD_H

#include "Vak.h"
#include <vector>

using namespace std;

struct Field {
  vector<vector<Vak *>> veld;
  void print();
};

#endif