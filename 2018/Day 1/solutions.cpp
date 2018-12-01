#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int N = 995;

vector<int> read_input() {
  string line;
  vector<int> input;

  ifstream file("input.txt");
  while (getline(file, line)) {
    input.push_back(stoi(line));
  }

  file.close();

  return input;
}

int frequency(vector<int> values) {
  int sum = 0;

  for (unsigned int i = 0; i < values.size(); ++i) {
    sum += values[i];
  }

  return sum;
}

int main() {
  vector<int> input;
  int solution1;

  input = read_input();
  solution1 = frequency(input);
  solution2 = frequency_twice(input);
  cout << "Oplossing 1: " << solution1 << "\n";

  return 0;
}
