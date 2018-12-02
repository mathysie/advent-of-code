#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

void part1() {
  string line;
  ifstream file("input.txt");
  int twees = 0;
  int dries = 0;

  while (getline(file, line)) {
    multiset<char> chars = {};
    for (char &c : line) {
      chars.insert(c);
    }

    bool twee = false;
    bool drie = false;
    for (char c = 'a'; c <= 'z'; c++) {
      if (chars.count(c) == 2 && !twee) {
        twees++;
        twee = true;
      } else if (chars.count(c) == 3 && !drie) {
        dries++;
        drie = true;
      }
    }
  }

  cout << "Checksum " << twees * dries << endl;

  return;
}

int main() {
  part1();

  return 0;
}