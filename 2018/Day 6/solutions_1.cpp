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

int largest_area(vector<pair<int, int>> points) {
  unsigned int N = points.size();
  int areas[N];
  fill(&areas[0], &areas[N], 0);
  int max_x =
      max_element(points.begin(), points.end(), compare_pair_second)->second;
  int max_y =
      max_element(points.begin(), points.end(), compare_pair_first)->first;

  for (int i = 0; i <= max_x; i++) {
    for (int j = 0; j <= max_y; j++) {
      int min = INT_MAX;
      int point;

      for (unsigned int k = 0; k < points.size(); k++) {
        int dist = manhattan_distance(points[k], make_pair(j, i));
        if (dist == min) {
          point = -1;
        } else if (dist < min) {
          min = dist;
          point = k;
        }
      }

      if ((i == 0 || i == max_x || j == 0 || j == max_y) &&
          areas[point] != -1) {
        areas[point] = -1;
      } else if (areas[point] != -1) {
        areas[point]++;
      }
    }
  }

  return *max_element(&areas[0], &areas[N]);
}

int main() {
  vector<pair<int, int>> input = read_input();
  int area = largest_area(input);

  cout << area << endl;

  return 0;
}
