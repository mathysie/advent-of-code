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

int frequency_twice(vector<int> values) {
  int sum = 0;
  unsigned int i = 0;
  vector<int> freqs;
  int T = true;

  while (T) {
    sum += values[i];
    for (unsigned int j = 0; j < freqs.size(); ++j) {
      if (freqs[j] == sum) {
        T = false;
      }
    }
    cout << endl;
    freqs.push_back(sum);

    i = i == values.size() - 1 ? 0 : i + 1;
  }

  return sum;
}

int main() {
  vector<int> input;
  int solution1;
  int solution2;

  input = read_input();
  solution1 = frequency(input);
  solution2 = frequency_twice(input);
  cout << "Oplossing 1: " << solution1 << "\n";
  cout << "Oplossing 2: " << solution2 << "\n";

  return 0;
}
