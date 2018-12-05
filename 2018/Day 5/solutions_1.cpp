#include <fstream>
#include <iostream>

using namespace std;

string read_input() {
  string line;
  ifstream file("input.txt");

  getline(file, line);

  return line;
}

int reduced_size(string chain) {
  int counter = 0;

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

int main() {
  string input = read_input();
  int size = reduced_size(input);

  cout << size << endl;

  return 0;
}
