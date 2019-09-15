#include "Elf.h"
#include <algorithm>
#include <climits>
#include <iostream>

forward_list<Vak *> Unit::find_targets(const vector<Unit *> &units,
                                       const Field &field) {
  forward_list<Vak *> tmp;
  for (auto u : units) {
    int i = u->pos.first, j = u->pos.second;
    if (field.veld[i - 1][j]->val == '.') {
      tmp.push_front(field.veld[i - 1][j]);
    }
    if (field.veld[i][j - 1]->val == '.') {
      tmp.push_front(field.veld[i][j - 1]);
    }
    if (field.veld[i + 1][j]->val == '.') {
      tmp.push_front(field.veld[i + 1][j]);
    }
    if (field.veld[i][j + 1]->val == '.') {
      tmp.push_front(field.veld[i][j + 1]);
    }
  }

  tmp.sort([](Vak *&v, Vak *&w) { return *v < *w; });
  return tmp;
}

Vak *Unit::find_closest(const vector<Unit *> &units, const Field &field) {
  forward_list<Vak *> candidates = find_targets(units, field);
  int dmax = INT_MAX;
  Vak *umax = NULL;

  Vak *s = field.veld[pos.first][pos.second];
  for (auto u : candidates) {
    if (s->man_dist(*u) > dmax) {
      continue;
    }
    int d = field.distance(s, u, dmax);
    if (d < dmax) {
      dmax = d;
      umax = u;
    }
  }

  return umax;
}

pair<int, int> Unit::find_dest(Vak *t, const Field &field) {
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
      dest = make_pair(i, j - 1);
    }
  }
  if (!field.veld[i][j + 1]->isBlocked()) {
    int d = field.distance(field.veld[i][j + 1], t, dmax);
    if (d < dmax) {
      dmax = d;
      dest = make_pair(i, j + 1);
    }
  }
  if (!field.veld[i + 1][j]->isBlocked()) {
    int d = field.distance(field.veld[i + 1][j], t, dmax);
    if (d < dmax) {
      dmax = d;
      dest = make_pair(i + 1, j);
    }
  }

  return dest;
};

void Unit::move(const vector<Unit *> &units, Field &field) {
  char c[4] = {
      field.veld[pos.first - 1][pos.second]->val,
      field.veld[pos.first][pos.second - 1]->val,
      field.veld[pos.first + 1][pos.second]->val,
      field.veld[pos.first][pos.second + 1]->val,
  };

  char d = isElf ? 'G' : 'E';
  if (any_of(c, c + 4, [d](char c) { return c == d; }) ||
      none_of(c, c + 4, [](char c) { return c == '.'; })) {
    return;
  }

  Vak *t = find_closest(units, field);
  if (t != NULL) {
    field.veld[pos.first][pos.second]->val = '.';
    field.veld[pos.first][pos.second]->unit = NULL;
    pos = find_dest(t, field);
    field.veld[pos.first][pos.second]->val = isElf ? 'E' : 'G';
    field.veld[pos.first][pos.second]->unit = this;
  }
}

void Unit::turn(vector<Unit *> &units, Field &field) {
  this->move(units, field);
}
