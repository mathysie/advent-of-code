#include <array>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

using namespace std;

vector<array<int, 4>> read_input() {
  ifstream file("input.txt");
  regex pattern(
      "position=<([0-9 -]+), ([0-9 -]+)> velocity=<([0-9 -]+), ([0-9 -]+)>");
  cmatch matches;
  string line;
  vector<array<int, 4>> input;

  while (getline(file, line)) {
    regex_search(line.c_str(), matches, pattern);
    array<int, 4> pos;
    for (int i = 0; i < 4; i++) {
      pos[i] = stoi(matches[i + 1].str());
    }
    input.push_back(pos);
  }

  return input;
}

bool comp_star_x(array<int, 4> star_1, array<int, 4> star_2) {
  return star_1[0] < star_2[0];
}

bool comp_star_y(array<int, 4> star_1, array<int, 4> star_2) {
  return star_1[1] < star_2[1];
}

void print_sky(vector<array<int, 4>> stars, int min_x, int min_y, int max_x,
               int max_y) {
  vector<vector<char>> sky;
  for (int j = 0; j <= max_x - min_x; j++) {
    vector<char> line(max_y - min_y + 1, '.');
    sky.push_back(line);
  }

  for (auto star : stars) {
    sky[star[0] - min_x][star[1] - min_y] = '*';
  }

  for (unsigned int j = 0; j < sky[0].size(); j++) {
    for (unsigned int i = 0; i < sky.size(); i++) {
      cout << sky[i][j];
    }
    cout << endl;
  }
}

void update_stars(vector<array<int, 4>> &stars, int step = 1) {
  for (auto &star : stars) {
    star[0] += step * star[2];
    star[1] += step * star[3];
  }
}

int first_step(const vector<array<int, 4>> &stars) {
  double ipart;
  if (stars[0][2] != 0) {
    modf(log(abs(stars[0][0]) / abs(stars[0][2])), &ipart);
  } else {
    modf(log(abs(stars[0][1]) / abs(stars[0][3])), &ipart);
  }

  return (int)exp(ipart);
}

void print_stars(vector<array<int, 4>> stars) {
  int max_diff = INT_MAX;
  int diff = INT_MAX;
  int max_x = 0;
  int min_x = 0;
  int max_y = 0;
  int min_y = 0;

  update_stars(stars, first_step(stars));

  while (diff <= max_diff) {
    if (diff < 80) {
      print_sky(stars, min_x, min_y, max_x, max_y);
    }

    update_stars(stars, 1);

    min_x = (*min_element(stars.begin(), stars.end(), comp_star_x))[0];
    max_x = (*max_element(stars.begin(), stars.end(), comp_star_x))[0];
    min_y = (*min_element(stars.begin(), stars.end(), comp_star_y))[1];
    max_y = (*max_element(stars.begin(), stars.end(), comp_star_y))[1];

    max_diff = diff;
    diff = max_x - min_x + max_y - min_y;
  }
}

int main() {
  vector<array<int, 4>> input = read_input();
  print_stars(input);

  return 0;
}
