#include <fstream>
#include <iostream>
#include <set>

using namespace std;

int tel_twees(multiset<char> chars) {
  for (char c = 'a'; c <= 'z'; c++) {
    if (chars.count(c) == 2) {
      return 1;
    }
  }

  return 0;
}

int tel_dries(multiset<char> chars) {
  for (char c = 'a'; c <= 'z'; c++) {
    if (chars.count(c) == 3) {
      return 1;
    }
  }

  return 0;
}

int main() {
  string line;
  ifstream file("input.txt");
  int twees = 0;
  int dries = 0;

  while (getline(file, line)) {
    multiset<char> chars = {};

    for (char &c : line) {
      chars.insert(c);
    }

    twees += tel_twees(chars);
    dries += tel_dries(chars);
  }

  cout << "Checksum " << twees * dries << endl;

  return 0;
}