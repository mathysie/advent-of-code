#include "Goblin.h"
#include <algorithm>
#include <exception>
#include <iostream>

vector<pair<int, int>> Goblin::find_targets(const vector<Elf *> &elves,
                                            const Field &field) {
  vector<pair<int, int>> tmp;
  for (auto g : elves) {
    pair<int, int> pos = g->pos;
    if (field.veld[pos.first - 1][pos.second]->val == '.') {
      tmp.push_back(make_pair(pos.first - 1, pos.second));
    }
    if (field.veld[pos.first][pos.second - 1]->val == '.') {
      tmp.push_back(make_pair(pos.first, pos.second - 1));
    }
    if (field.veld[pos.first + 1][pos.second]->val == '.') {
      tmp.push_back(make_pair(pos.first + 1, pos.second));
    }
    if (field.veld[pos.first][pos.second + 1]->val == '.') {
      tmp.push_back(make_pair(pos.first, pos.second + 1));
    }
  }

  return tmp;
}

void Goblin::move(vector<Elf *> &elves, Field &field) {
  char c[4] = {
      field.veld[pos.first - 1][pos.second]->val,
      field.veld[pos.first][pos.second - 1]->val,
      field.veld[pos.first + 1][pos.second]->val,
      field.veld[pos.first][pos.second + 1]->val,
  };

  if (any_of(c, c + 4, [](char c) { return c == 'E'; }) ||
      none_of(c, c + 4, [](char c) { return c == '.'; })) {
    cout << "Goblin " << pos.first << " " << pos.second << " did not move.\n";
    return;
  }

  vector<pair<int, int>> targets = find_targets(elves, field);
}

void Goblin::turn(vector<Elf *> &elves, Field &field) {
  this->move(elves, field);
}
