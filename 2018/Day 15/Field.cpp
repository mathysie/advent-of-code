#include "Field.h"
#include <iostream>

void Field::print() {
  for (auto v : veld) {
    for (auto c : v) {
      cout << c;
    }
    cout << "\n";
  }
  cout << endl;
}
