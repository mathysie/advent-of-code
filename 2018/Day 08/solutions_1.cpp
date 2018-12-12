#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<int> read_input() {
  ifstream file("input.txt");
  string line;
  vector<int> tokens;

  getline(file, line);

  istringstream buf(line);
  istream_iterator<string> beg(buf), end;
  for (auto it = beg; it != end; it++) {
    tokens.push_back(stoi(*it));
  }

  return tokens;
}

void add_sum(vector<int> input, int &i, int &sum) {
  int childs = input[i];
  i++;
  int metadatas = input[i];
  i++;

  for (int j = 0; j < childs; j++) {
    add_sum(input, i, sum);
  }

  for (int j = 0; j < metadatas; j++) {
    sum += input[i];
    i++;
  }
}

void compute_sum(vector<int> input, int &sum) {
  int i = 0;

  add_sum(input, i, sum);
}

int main() {
  vector<int> input = read_input();
  int sum = 0;
  compute_sum(input, sum);
  cout << sum << endl;

  return 0;
}
