#include "Elf.h"
#include <algorithm>
#include <iostream>

vector<pair<int, int>> Elf::find_targets(const vector<Goblin *> &goblins,
                                         const Field &field) {
  vector<pair<int, int>> tmp;
  for (auto g : goblins) {
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

void Elf::find_closest(vector<Goblin *> &goblins, const Field &field) {
  vector<pair<int, int>> candidates = find_targets(goblins, field);

  // Insert Dijkstra
}

void Elf::move(vector<Goblin *> &goblins, const Field &field) {
  char c[4] = {
      field.veld[pos.first - 1][pos.second]->val,
      field.veld[pos.first][pos.second - 1]->val,
      field.veld[pos.first + 1][pos.second]->val,
      field.veld[pos.first][pos.second + 1]->val,
  };

  if (any_of(c, c + 4, [](char c) { return c == 'G'; }) ||
      none_of(c, c + 4, [](char c) { return c == '.'; })) {
    cout << "Elf " << pos.first << " " << pos.second << " did not move.\n";
    return;
  }

  vector<pair<int, int>> targets = find_closest(goblins, field);
}

void Elf::turn(vector<Goblin *> &goblins, const Field &field) {
  this->move(goblins, field);
}
