#include "Elf.h"
#include <algorithm>
#include <climits>
#include <iostream>

forward_list<Vak *> Unit::find_targets(const unordered_set<Unit *> &units,
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

Vak *Unit::find_closest(const unordered_set<Unit *> &units,
                        const Field &field) {
  forward_list<Vak *> candidates = find_targets(units, field);
  int dmin = INT_MAX;
  Vak *umax = NULL;

  Vak *s = field.veld[pos.first][pos.second];
  for (auto u : candidates) {
    if (s->man_dist(*u) > dmin) {
      continue;
    }
    int d = field.distance(s, u, dmin);
    if (d < dmin) {
      dmin = d;
      umax = u;
    }
  }

  return umax;
}

pair<int, int> Unit::find_dest(Vak *t, const Field &field) {
  pair<int, int> dest;
  int dmin = INT_MAX;
  int i = pos.first, j = pos.second;
  if (!field.veld[i - 1][j]->isBlocked()) {
    int d = field.distance(field.veld[i - 1][j], t, dmin);
    if (d < dmin) {
      dmin = d;
      dest = make_pair(i - 1, j);
    }
  }
  if (!field.veld[i][j - 1]->isBlocked()) {
    int d = field.distance(field.veld[i][j - 1], t, dmin);
    if (d < dmin) {
      dmin = d;
      dest = make_pair(i, j - 1);
    }
  }
  if (!field.veld[i][j + 1]->isBlocked()) {
    int d = field.distance(field.veld[i][j + 1], t, dmin);
    if (d < dmin) {
      dmin = d;
      dest = make_pair(i, j + 1);
    }
  }
  if (!field.veld[i + 1][j]->isBlocked()) {
    int d = field.distance(field.veld[i + 1][j], t, dmin);
    if (d < dmin) {
      dmin = d;
      dest = make_pair(i + 1, j);
    }
  }

  return dest;
};

void Unit::move(const unordered_set<Unit *> &units, Field &field) {
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

Unit *Unit::aim(const Field &field) {
  Unit *target = NULL;
  char c = isElf ? 'G' : 'E';
  int hpmin = INT_MAX;
  int i = pos.first, j = pos.second;
  if (field.veld[i - 1][j]->val == c) {
    target = field.veld[i - 1][j]->unit;
    hpmin = target->hp;
  }
  if (field.veld[i][j - 1]->val == c &&
      hpmin > field.veld[i][j - 1]->unit->hp) {
    target = field.veld[i][j - 1]->unit;
    hpmin = target->hp;
  }
  if (field.veld[i][j + 1]->val == c &&
      hpmin > field.veld[i][j + 1]->unit->hp) {
    target = field.veld[i][j + 1]->unit;
    hpmin = target->hp;
  }
  if (field.veld[i + 1][j]->val == c &&
      hpmin > field.veld[i + 1][j]->unit->hp) {
    target = field.veld[i + 1][j]->unit;
    hpmin = target->hp;
  }

  return target;
}

void Unit::attack(unordered_set<Unit *> &units, Field &field) {
  Unit *attacked = aim(field);
  if (attacked == NULL) {
    return;
  }
  attacked->hp -= 3;
  if (attacked->hp <= 0) {
    field.veld[attacked->pos.first][attacked->pos.second]->val = '.';
    units.erase(units.find(attacked));
  }
}

void Unit::turn(unordered_set<Unit *> &units, Field &field) {
  move(units, field);
  attack(units, field);
}
