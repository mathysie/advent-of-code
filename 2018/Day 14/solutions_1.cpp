#include <fstream>
#include <iostream>
#include <list>

using namespace std;

unsigned int read_input() {
  ifstream file("input.txt");
  unsigned int x;
  file >> x;

  return x;
}

void advance(list<int>::iterator &it, int steps, list<int> &recipes) {
  for (int i = 0; i < steps; i++) {
    it++;
    if (it == recipes.end()) {
      it = recipes.begin();
    }
  }
}

list<int> make_recipes(unsigned int amount) {
  list<int> recipes = {3, 7};
  auto it1 = recipes.begin();
  auto it2 = recipes.begin();
  it2++;

  while (recipes.size() < amount + 10) {
    int sum = *it1 + *it2;
    if (sum >= 10) {
      recipes.push_back(1);
    }
    recipes.push_back(sum % 10);

    advance(it1, *it1 + 1, recipes);
    advance(it2, *it2 + 1, recipes);
  }

  return recipes;
}

int main() {
  unsigned int input = read_input();
  list<int> recipes = make_recipes(input);

  auto it = recipes.begin();
  advance(it, input);
  for (int i = 0; i < 10; i++) {
    cout << *it;
    it++;
  }
  cout << endl;

  return 0;
}
