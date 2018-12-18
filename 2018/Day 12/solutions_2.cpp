#include <algorithm>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>

using namespace std;

deque<bool> read_input(set<int> &spreads) {
  ifstream file("input.txt");
  string line;
  deque<bool> input;

  getline(file, line);
  for (unsigned int i = 15; i < line.size(); i++) {
    input.push_back(line[i] == '#');
  }

  getline(file, line);

  while (getline(file, line)) {
    if (line[9] == '#') {
      int sum = 0;
      for (int i = 0; i < 5; i++) {
        sum += (line[i] == '#') * (int)pow(2, i);
      }
      spreads.insert(sum);
    }
  }

  return input;
}

bool get(deque<bool> plants, int index) {
  return (index < 0 || index >= (int)plants.size()) ? 0 : plants[index];
}

void run_iteration(set<int> spreads, deque<bool> &plants, int &offset) {
  deque<bool> copy = plants;

  for (unsigned int i = 0; i < plants.size(); i++) {
    int sum = 0;
    for (int j = 0; j < 5; j++) {
      sum += get(plants, i + j - 2) * (int)pow(2, j);
    }
    copy[i] = spreads.find(sum) != spreads.end();
  }

  int pre1 = plants[0] * 8 + plants[1] * 16;
  int pre2 = plants[0] * 16;
  if (spreads.find(pre2) != spreads.end()) {
    copy.push_front(1);
    copy.push_front(spreads.find(pre1) != spreads.end());
    offset += 2;
  } else if (spreads.find(pre1) != spreads.end()) {
    copy.push_front(1);
    offset += 1;
  }

  unsigned long N = plants.size();
  int post1 = plants[N - 1] * 2 + plants[N - 2];
  int post2 = plants[N - 1];
  if (spreads.find(post2) != spreads.end()) {
    copy.push_back(spreads.find(post1) != spreads.end());
    copy.push_back(1);
  } else if (spreads.find(post1) != spreads.end()) {
    copy.push_back(1);
  }

  plants = copy;
}

long sum_generations(set<int> spreads, deque<bool> &plants) {
  int step = 0;
  int offset = 0;

  bool stop = false;
  while (!stop) {
    deque<bool> temp = plants;
    run_iteration(spreads, plants, offset);

    bool equal = true;
    for (unsigned int i = 0; i < temp.size(); i++) {
      if (temp[i] != plants[i + 1]) {
        equal = false;
        break;
      }
    }
    stop = equal;

    step++;
  }

  long sum = 0;
  int k;
  for (int j = 0; j < (int)plants.size(); j++) {
    if (plants[j] == 1) {
      k = j;
      break;
    }
  }

  for (int i = k; i < (int)plants.size(); i++) {
    sum += (i - offset + 50000000000 - step) * plants[i];
  }

  return sum;
}

int main() {
  set<int> spreads;
  deque<bool> input = read_input(spreads);

  cout << sum_generations(spreads, input) << endl;

  return 0;
}
