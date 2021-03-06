#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

int *read_input() {
  string line;
  static int input[2];
  ifstream file("input.txt");

  getline(file, line);
  sscanf(line.c_str(), "%d players; last marble is worth %d points", &input[0],
         &input[1]);

  return input;
}

long winning_score(int players, int max_points) {
  vector<long> scores(players);
  fill(scores.begin(), scores.end(), 0L);

  list<int> marbles(1, 0);
  auto it = marbles.begin();

  for (int i = 1; i <= max_points * 100; i++) {
    if (i % 23 != 0) {
      it++;
      if (it == marbles.end()) {
        it = marbles.begin();
      }
      it++;

      it = marbles.insert(it, i);
    } else {
      int player = (i - 1) % players;
      scores[player] += i;

      for (int j = 0; j < 7; j++) {
        if (it == marbles.begin()) {
          it = marbles.end();
        }
        it--;
      }
      scores[player] += *it;

      it = marbles.erase(it);
    }
  }

  return *max_element(scores.begin(), scores.end());
}

int main() {
  int *input = read_input();
  long score = winning_score(input[0], input[1]);

  cout << score << endl;

  return 0;
}
