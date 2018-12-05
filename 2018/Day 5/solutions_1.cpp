#include <fstream>
#include <iostream>
#include <list>

using namespace std;

list<char> read_input() {
  string line;
  ifstream file("input.txt");
  list<char> input;

  while (getline(file, line)) {
    for (auto &c : line) {
      input.push_back(c);
    }
  }

  return input;
}

void do_reactions(list<char> &chain) {
  auto it = chain.begin();
  auto it2 = chain.begin();
  it2++;

  while (it2 != chain.end()) {
    if (abs(*it - *it2) == 32) {
      auto it_temp = it;
      auto it_temp2 = it2;

      if (it == chain.begin()) {
        advance(it, 2), advance(it2, 2);
      } else {
        it2++;
        it--;
      }
      chain.erase(it_temp);
      chain.erase(it_temp2);
    } else {
      it++;
      it2++;
    }
  }
}

int main() {
  list<char> input = read_input();
  do_reactions(input);

  cout << input.size() << endl;

  return 0;
}
