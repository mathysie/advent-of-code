#include "Field.h"
#include "Unit.h"
#include <climits>
#include <iostream>
#include <set>

struct cell {
  Vak *vak;
  int f, g, h;

  cell() { f = g = h = INT_MAX; }
  int calc_h(Vak *t) { return vak->man_dist(*t); }
  int calc_f() { return g + h; };
};

void update_cell(const cell &orig, cell &cur, Vak *t, int &fnew, int &gnew,
                 int &hnew, set<pair<int, pair<int, int>>> &openList,
                 const vector<vector<bool>> &closedList) {
  int i = cur.vak->pos.first, j = cur.vak->pos.second;
  if (closedList[i][j] == false && !cur.vak->isBlocked()) {
    gnew = orig.g + 1;
    hnew = cur.calc_h(t);
    fnew = gnew + hnew;

    if (cur.f == INT_MAX || cur.f > fnew) {
      cur.f = fnew;
      cur.g = gnew;
      cur.h = hnew;

      openList.insert(make_pair(fnew, make_pair(i, j)));
    }
  }
}

int Field::distance(Vak *s, Vak *t, int dmax) const {
  if (*s == *t) {
    return 0;
  }
  unsigned long rows = veld.size(), cols = veld[0].size();
  vector<vector<bool>> closedList(rows, vector<bool>(cols, false));

  cell cells[rows][cols];
  for (unsigned int i = 0; i < rows; i++) {
    for (unsigned int j = 0; j < cols; j++) {
      cells[i][j].vak = veld[i][j];
    }
  }

  cells[s->pos.first][s->pos.second].f = 0;
  cells[s->pos.first][s->pos.second].g = 0;
  cells[s->pos.first][s->pos.second].h = 0;

  set<pair<int, pair<int, int>>> openList;
  openList.insert(make_pair(0, s->pos));

  while (!openList.empty()) {
    pair<int, pair<int, int>> p = *openList.begin();
    if (p.first >= dmax) {
      return INT_MAX;
    }

    openList.erase(openList.begin());
    int i = p.second.first, j = p.second.second;
    closedList[i][j] = true;

    int fnew, gnew, hnew;
    if (cells[i - 1][j].vak == t) {
      return cells[i][j].g + 1;
    } else {
      update_cell(cells[i][j], cells[i - 1][j], t, fnew, gnew, hnew, openList,
                  closedList);
    }
    if (cells[i + 1][j].vak == t) {
      return cells[i][j].g + 1;
    } else {
      update_cell(cells[i][j], cells[i + 1][j], t, fnew, gnew, hnew, openList,
                  closedList);
    }
    if (cells[i][j - 1].vak == t) {
      return cells[i][j].g + 1;
    } else {
      update_cell(cells[i][j], cells[i][j - 1], t, fnew, gnew, hnew, openList,
                  closedList);
    }
    if (cells[i][j + 1].vak == t) {
      return cells[i][j].g + 1;
    } else {
      update_cell(cells[i][j], cells[i][j + 1], t, fnew, gnew, hnew, openList,
                  closedList);
    }
  }

  return INT_MAX;
}

void Field::print() {
  for (unsigned int i = 0; i < veld.size(); i++) {
    cout << i << ":\t";
    vector<Unit*> units;
    for (auto vak : veld[i]) {
      cout << vak->val;
      if (vak->val == 'E' || vak->val == 'G') {
        units.push_back(vak->unit);
      }
    }
    cout << "   ";
    for (auto u: units) {
      cout << (u->isElf ? 'E' : 'G') << "(" << u->hp << "), ";
    }
    cout << "\n";
  }
  cout << endl;
}
