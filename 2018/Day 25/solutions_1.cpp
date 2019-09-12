#include "Constellation.h"
#include "Vec4.h"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

int Constellation::n = 0;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

void initialize(vector<Vec4 *> &vecs) {
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    int cont[4];
    string token;
    for (int i = 0; getline(ss, token, ','); i++) {
      cont[i] = stoi(token);
    }
    Vec4 *vec = new Vec4(cont[0], cont[1], cont[2], cont[3]);
    vecs.push_back(vec);
  }
}

void destroy(vector<Vec4 *> vecs, unordered_set<Constellation *> &consts) {
  for (auto v : vecs) {
    delete v;
  }
  for (auto c : consts) {
    delete c;
  }
}

void find_consts(unsigned int i, vector<Vec4 *> &vecs,
                 unordered_set<Constellation *> &consts) {
  Vec4 *v = vecs[i];
  for (unsigned int j = i + 1; j < vecs.size(); j++) {
    if (v->dist(*vecs[j]) <= 3) {
      if (vecs[j]->c == NULL) {
        vecs[j]->c = v->c;
        v->c->vecs.push_back(vecs[j]);
      } else if (v->c != vecs[j]->c) {
        Constellation *c1 = v->c;
        Constellation *c2 = vecs[j]->c;
        for (auto tmp : c2->vecs) {
          tmp->c = c1;
          c1->vecs.push_back(tmp);
        }
        consts.erase(consts.find(c2));
        delete c2;
      }
    }
  }
}

int main() {
  auto start = chrono::high_resolution_clock::now();

  vector<Vec4 *> vecs;
  initialize(vecs);
  unordered_set<Constellation *> consts;

  for (unsigned int i = 0; i < vecs.size(); i++) {
    if (vecs[i]->c == NULL) {
      Constellation *c = new Constellation(vecs[i]);
      vecs[i]->c = c;
      consts.insert(c);
    }
    find_consts(i, vecs, consts);
  }

  cout << "Constellations: " << Constellation::n << endl;

  destroy(vecs, consts);

  display_time(start);
  return 0;
}
