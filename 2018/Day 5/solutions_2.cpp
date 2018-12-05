#include <fstream>
#include <iostream>
#include <locale>
#include <algorithm>
#include <string>

using namespace std;

string read_input() {
  string line;
  ifstream file("input.txt");

  getline(file, line);

  return line;
}

unsigned int reduced_size(string chain) {
  unsigned int counter = 0;

  for (unsigned int i = 0; i < chain.size(); i++) {
    if (counter > 0 && (chain[i] ^ chain[counter - 1]) == 32) {
      counter--;
    } else {
      chain[counter] = chain[i];
      counter++;
    }
  }

  return counter;
}

int min_length(string input) {
  unsigned int min = -1;

  for (char c = 'a'; c <= 'z'; c++) {
    string copy = input;
    copy.erase(remove(copy.begin(), copy.end(), c), copy.end());
    copy.erase(remove(copy.begin(), copy.end(), (char)toupper(c)), copy.end());

    unsigned int len = reduced_size(copy);

    if (len < min) {
      min = len;
    }
  }

  return min;
}

int main() {
  string input = read_input();
  int min = min_length(input);

  cout << min << endl;

  return 0;
}
