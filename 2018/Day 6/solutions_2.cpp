#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<int, int>> read_input() {
  string line;
  ifstream file("input.txt");
  vector<pair<int, int>> input;

  while (getline(file, line)) {
    int x, y;
    sscanf(line.c_str(), "%d, %d", &x, &y);
    input.push_back(make_pair(x, y));
  };

  return input;
}

int manhattan_distance(pair<int, int> x, pair<int, int> y) {
  return abs(x.first - y.first) + abs(x.second - y.second);
}

bool compare_pair_first(pair<int, int> x, pair<int, int> y) {
  return x.first < y.first;
}

bool compare_pair_second(pair<int, int> x, pair<int, int> y) {
  return x.second < y.second;
}

int region_area(vector<pair<int, int>> points) {
  int counter = 0;
  int max_x =
      max_element(points.begin(), points.end(), compare_pair_second)->second;
  int max_y =
      max_element(points.begin(), points.end(), compare_pair_first)->first;

  for (int i = 0; i <= max_x; i++) {
    for (int j = 0; j <= max_y; j++) {
      int sum = 0;
      for (unsigned int k = 0; k < points.size(); k++) {
        if (sum >= 10000) {
          break;
        }
        sum += manhattan_distance(points[k], make_pair(j, i));
      }
      if (sum < 10000)
        counter++;
    }
  }

  return counter;
}

int main() {
  vector<pair<int, int>> input = read_input();
  int area = region_area(input);

  cout << area << endl;

  return 0;
}
