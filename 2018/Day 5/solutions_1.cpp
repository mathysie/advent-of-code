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

void do_reactions(list<char> &input) {
  auto it = input.begin();
  auto it2 = input.begin();
  it2++;

  while (true) {
    if (it2 == input.end())
      return;

    if (abs(*it - *it2) == 32) {
      auto it_temp = it;
      auto it_temp2 = it2;

      it2++;
      it--;
      input.erase(it_temp);
      input.erase(it_temp2);
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
