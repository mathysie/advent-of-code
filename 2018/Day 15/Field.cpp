#include "Field.h"
#include <iostream>

void Field::print() {
  for (unsigned int i = 0; i < veld.size(); i++) {
    cout << i << ":\t";
    for (auto vak : veld[i]) {
      cout << vak->val;
    }
    cout << "\n";
  }
  cout << endl;
}
