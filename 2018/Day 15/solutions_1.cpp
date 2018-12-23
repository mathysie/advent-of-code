#include <chrono>
#include <iostream>

using namespace std;

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

int main() {
  auto start = chrono::high_resolution_clock::now();

  display_time(start);
  return 0;
}
