#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> read_input() {
  ifstream file("inputtest.txt");
  vector<int> x;
  string line;

  cin >> line;
  for (unsigned int i = 0; i < line.size(); i++) {
    x.push_back(line[i] - '0');
  }

  return x;
}

void advance_list(list<int>::iterator &it, int steps, list<int> &recipes) {
  for (int i = 0; i < steps; i++) {
    it++;
    if (it == recipes.end()) {
      it = recipes.begin();
    }
  }
}

long seq_index(list<int> recipes, vector<int> seq) {
  if (recipes.size() < seq.size() + 2) {
    return -1;
  }

  auto it = recipes.end();
  advance(it, -seq.size() - 2);
  auto pos = search(it, recipes.end(), seq.begin(), seq.end());

  if (pos != recipes.end()) {
    int counter = 0;
    while (pos != recipes.begin()) {
      pos--;
      counter++;
    }

    return counter;
  }

  return -1;
}

list<int> make_recipes(vector<int> seq) {
  list<int> recipes = {3, 7};
  auto it1 = recipes.begin();
  auto it2 = recipes.begin();
  it2++;

  int counter = 0;
  while (seq_index(recipes, seq) == -1) {
    if (counter % 1000 == 0) {
      cout << counter << endl;
    }
    int sum = *it1 + *it2;
    if (sum >= 10) {
      recipes.push_back(1);
    }
    recipes.push_back(sum % 10);

    advance_list(it1, *it1 + 1, recipes);
    advance_list(it2, *it2 + 1, recipes);
    counter++;
  }

  return recipes;
}

int main() {
  vector<int> input = read_input();
  list<int> recipes = make_recipes(input);

  cout << seq_index(recipes, input) << endl;

  return 0;
}
