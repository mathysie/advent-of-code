#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct marble {
  int value;
  marble *next;
  marble *prev;
};

int *read_input() {
  string line;
  static int input[2];
  ifstream file("input.txt");

  getline(file, line);
  sscanf(line.c_str(), "%d players; last marble is worth %d points", &input[0],
         &input[1]);

  return input;
}

marble *create_starting_marble() {
  marble *start = new marble;
  start->value = 0;
  start->next = start->prev = start;

  return start;
}

marble *insert_marble(marble *current, int value) {
  marble *new_marble = new marble;
  new_marble->value = value;
  new_marble->next = current;
  new_marble->prev = current->prev;

  current->prev->next = new_marble;
  current->prev = new_marble;

  return new_marble;
}

marble *remove_marble(marble *current) {
  current->prev->next = current->next;
  current->next->prev = current->prev;
  marble *temp = current;
  current = current->next;
  delete temp;

  return current;
}

void delete_marbles(marble *current) {
  marble *temp = current->next;
  while (temp != current) {
    temp = temp->next;
    delete temp->prev;
  }

  delete temp;
}

int winning_score(int players, int max_points) {
  vector<unsigned int> scores(players);
  fill(scores.begin(), scores.end(), 0);

  marble *current = create_starting_marble();

  for (int i = 1; i <= max_points * 100; i++) {
    current = current->next->next;

    if (i % 23 != 0) {
      current = insert_marble(current, i);
    } else {
      int player = (i - 1) % players;
      scores[player] += i;

      for (int j = 0; j < 9; j++) {
        current = current->prev;
      }
      scores[player] += current->value;

      current = remove_marble(current);
    }
  }

  delete_marbles(current);

  return *max_element(scores.begin(), scores.end());
}

int main() {
  int *input = read_input();
  unsigned int score = winning_score(input[0], input[1]);

  cout << score << endl;

  return 0;
}