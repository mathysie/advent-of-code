#include "Field.h"
#include <iostream>

void Field::print() {
  for (auto rij : veld) {
    for (auto vak : rij) {
      cout << vak->val;
    }
    cout << "\n";
  }
  cout << endl;
}
