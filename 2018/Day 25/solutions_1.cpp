#include "Constellation.h"
#include "Vec4.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

void initialize(vector<Vec4> &vecs) {
  ifstream file("input.txt");
  string line;
  while (getline(file, line)) {
    stringstream ss(line);
    int cont[4];
    string token;
    for (int i = 0; getline(ss, token, ','); i++) {
      cont[i] = stoi(token);
    }
    Vec4 vec{cont[0], cont[1], cont[2], cont[3]};
    vecs.push_back(vec);
  }
}

void find_consts(unsigned int i, const vector<Vec4> &vecs,
                 vector<Constellation> &consts) {
  Vec4 v = vecs[i];
  for (unsigned int j = i + 1; j < vecs.size(); j++) {
    if (v.dist(vecs[j]) <= 3) {
      Constellation c;
      if (v.c == NULL && vecs[j].c == NULL) {
        v.c = &c;
        vecs[j].c = &c;
        c.vecs.push_back(&c);
        c.vecs.push_back(&vecs[j]);
      } else if (v.c != NULL && vecs[j].c == NULL) {
        vecs[j].c = v.c;
        v.c->vecs.push_back(&vecs[j]);
      } else if (v.c == NULL && vecs[j].c != NULL) {
        v.c = vecs[j].c;
        vecs[j].c->vecs.push_back(&v);
      } else {
        // Merge twee sterrenbeelden
      }

    }
  }
}

int main() {
  auto start = chrono::high_resolution_clock::now();

  vector<Vec4> vecs;
  initialize(vecs);
  vector<Constellation> consts;

  for (unsigned int i = 0; i < vecs.size(); i++) {
    find_consts(i, vecs, consts);
  }

  cout << endl;

  display_time(start);
  return 0;
}
