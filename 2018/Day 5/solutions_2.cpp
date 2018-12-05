#include <fstream>
#include <iostream>
#include <list>
#include <locale>

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

  while (true) {
    if (it2 == chain.end())
      return;

    if (abs(*it - *it2) == 32) {
      auto it_temp = it;
      auto it_temp2 = it2;

      if (it == chain.begin()) {
        it++, it++, it2++, it2++;
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

int min_length(list<char> input) {
  unsigned int min = -1;

  for (char c = 'a'; c <= 'z'; c++) {
    list<char> copy = input;
    copy.remove(c);
    copy.remove((char)toupper(c));

    do_reactions(copy);

    if (copy.size() < min) {
      min = copy.size();
    }
  }

  return min;
}

int main() {
  list<char> input = read_input();

  cout << min_length(input) << endl;

  return 0;
}
