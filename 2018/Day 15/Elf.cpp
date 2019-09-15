#include "Elf.h"
#include <algorithm>
#include <climits>
#include <exception>
#include <iostream>

vector<Vak *> Elf::find_targets(const vector<Goblin *> &goblins,
                                const Field &field) {
  vector<Vak *> tmp;
  for (auto g : goblins) {
    int i = g->pos.first, j = g->pos.second;
    if (field.veld[i - 1][j]->val == '.') {
      tmp.push_back(field.veld[i - 1][j]);
    }
    if (field.veld[i][j - 1]->val == '.') {
      tmp.push_back(field.veld[i][j - 1]);
    }
    if (field.veld[i + 1][j]->val == '.') {
      tmp.push_back(field.veld[i + 1][j]);
    }
    if (field.veld[i][j + 1]->val == '.') {
      tmp.push_back(field.veld[i][j + 1]);
    }
  }

  return tmp;
}

Vak *Elf::find_closest(const vector<Goblin *> &goblins, const Field &field) {
  vector<Vak *> candidates = find_targets(goblins, field);
  int dmax = INT_MAX;
  Vak *gmax = NULL;

  Vak *s = field.veld[pos.first][pos.second];
  for (auto g : candidates) {
    int d = field.distance(s, g, dmax);
    if (d < dmax) {
      dmax = d;
      gmax = g;
    }
  }

  return gmax;
}

pair<int, int> Elf::find_dest(Vak *t, const Field &field) {
  pair<int, int> dest;
  int dmax = INT_MAX;
  int i = pos.first, j = pos.second;
  if (!field.veld[i - 1][j]->isBlocked()) {
    int d = field.distance(field.veld[i - 1][j], t, dmax);
    if (d < dmax) {
      dmax = d;
      dest = make_pair(i - 1, j);
    }
  }
  if (!field.veld[i][j - 1]->isBlocked()) {
    int d = field.distance(field.veld[i][j - 1], t, dmax);
    if (d < dmax) {
      dmax = d;
      dest = make_pair(i - 1, j);
    }
  }
  if (!field.veld[i][j + 1]->isBlocked()) {
    int d = field.distance(field.veld[i][j + 1], t, dmax);
    if (d < dmax) {
      dmax = d;
      dest = make_pair(i - 1, j);
    }
  }
  if (!field.veld[i + 1][j]->isBlocked()) {
    int d = field.distance(field.veld[i + 1][j], t, dmax);
    if (d < dmax) {
      dmax = d;
      dest = make_pair(i - 1, j);
    }
  }

  return dest;
};

void Elf::move(const vector<Goblin *> &goblins, Field &field) {
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

  Vak *t = find_closest(goblins, field);
  if (t != NULL) {
    field.veld[pos.first][pos.second]->val = '.';
    field.veld[pos.first][pos.second]->unit = NULL;
    pos = find_dest(t, field);
    field.veld[pos.first][pos.second]->val = 'E';
    field.veld[pos.first][pos.second]->unit = this;
  }
}

void Elf::turn(vector<Goblin *> &goblins, Field &field) {
  this->move(goblins, field);
}
