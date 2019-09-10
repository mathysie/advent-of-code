#include <algorithm>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

struct cart {
  unsigned int x;
  unsigned int y;
  char track;
  int turn;
  bool crash = false;
};

bool cart_sort(cart x, cart y) { return x.y != y.y ? x.y < y.y : x.x < y.x; }

vector<vector<char>> read_input(list<cart> &carts) {
  ifstream file("input.txt");
  string line;
  vector<vector<char>> grid;

  for (unsigned int y = 0; getline(file, line); y++) {
    vector<char> row;

    for (unsigned int x = 0; x < line.size(); x++) {
      if (line[x] == '>') {
        cart car{x, y, '-', 0};
        carts.push_front(car);
      } else if (line[x] == '<') {
        cart car{x, y, '-', 0};
        carts.push_front(car);
      } else if (line[x] == '^') {
        cart car{x, y, '|', 0};
        carts.push_front(car);
      } else if (line[x] == 'v') {
        cart car{x, y, '|', 0};
        carts.push_front(car);
      }

      row.push_back(line[x]);
    }

    grid.push_back(row);
  }

  carts.sort(cart_sort);

  return grid;
}

void remove_crashed(list<cart> &carts) {
  for (auto it = carts.begin(); it != carts.end(); it++) {
    if (it->crash) {
      auto it2 = it;
      it--;
      carts.erase(it2);
    }
  }
}

cart *find_crash(unsigned int y, unsigned int x, list<cart> &carts, cart car) {
  for (auto &cart : carts) {
    if (cart.x == x && cart.y == y && cart.track != car.track) {
      return &cart;
    }
  }
}

void crash_coordinate(vector<vector<char>> &grid, list<cart> &carts) {
  while (carts.size() > 1) {
    for (auto &car : carts) {
      char cur = grid[car.y][car.x];
      grid[car.y][car.x] = car.track;

      if (cur == '>') {
        car.track = grid[car.y][car.x + 1];
        car.x++;

        if (grid[car.y][car.x] == '\\') {
          grid[car.y][car.x] = 'v';
        } else if (grid[car.y][car.x] == '/') {
          grid[car.y][car.x] = '^';
        } else if (grid[car.y][car.x] == '+') {
          switch (car.turn % 3) {
          case 0:
            grid[car.y][car.x] = '^';
            break;
          case 1:
            grid[car.y][car.x] = '>';
            break;
          case 2:
            grid[car.y][car.x] = 'v';
            break;
          }
          car.turn++;
        } else if (grid[car.y][car.x] == '-') {
          grid[car.y][car.x] = '>';
        } else {
          cart *crash = find_crash(car.y, car.x, carts, car);
          car.crash = true;
          crash->crash = true;
          grid[car.y][car.x] = crash->track;
        }

      } else if (cur == 'v') {
        car.track = grid[car.y + 1][car.x];
        car.y++;

        if (grid[car.y][car.x] == '\\') {
          grid[car.y][car.x] = '>';
        } else if (grid[car.y][car.x] == '/') {
          grid[car.y][car.x] = '<';
        } else if (grid[car.y][car.x] == '+') {
          switch (car.turn % 3) {
          case 0:
            grid[car.y][car.x] = '>';
            break;
          case 1:
            grid[car.y][car.x] = 'v';
            break;
          case 2:
            grid[car.y][car.x] = '<';
            break;
          }
          car.turn++;
        } else if (grid[car.y][car.x] == '|') {
          grid[car.y][car.x] = 'v';
        } else {
          cart *crash = find_crash(car.y, car.x, carts, car);
          car.crash = true;
          crash->crash = true;
          grid[car.y][car.x] = crash->track;
        }

      } else if (cur == '<') {
        car.track = grid[car.y][car.x - 1];
        car.x--;

        if (grid[car.y][car.x] == '\\') {
          grid[car.y][car.x] = '^';
        } else if (grid[car.y][car.x] == '/') {
          grid[car.y][car.x] = 'v';
        } else if (grid[car.y][car.x] == '+') {
          switch (car.turn % 3) {
          case 0:
            grid[car.y][car.x] = 'v';
            break;
          case 1:
            grid[car.y][car.x] = '<';
            break;
          case 2:
            grid[car.y][car.x] = '^';
            break;
          }
          car.turn++;
        } else if (grid[car.y][car.x] == '-') {
          grid[car.y][car.x] = '<';
        } else {
          cart *crash = find_crash(car.y, car.x, carts, car);
          car.crash = true;
          crash->crash = true;
          grid[car.y][car.x] = crash->track;
        }

      } else if (cur == '^') {
        car.track = grid[car.y - 1][car.x];
        car.y--;

        if (grid[car.y][car.x] == '\\') {
          grid[car.y][car.x] = '<';
        } else if (grid[car.y][car.x] == '/') {
          grid[car.y][car.x] = '>';
        } else if (grid[car.y][car.x] == '+') {
          switch (car.turn % 3) {
          case 0:
            grid[car.y][car.x] = '<';
            break;
          case 1:
            grid[car.y][car.x] = '^';
            break;
          case 2:
            grid[car.y][car.x] = '>';
            break;
          }
          car.turn++;
        } else if (grid[car.y][car.x] == '|') {
          grid[car.y][car.x] = '^';
        } else {
          cart *crash = find_crash(car.y, car.x, carts, car);
          car.crash = true;
          crash->crash = true;
          grid[car.y][car.x] = crash->track;
        }
      }
    }

    remove_crashed(carts);
    carts.sort(cart_sort);
  }

  cout << carts.begin()->x << "," << carts.begin()->y << endl;
}

int main() {
  list<cart> carts;
  vector<vector<char>> grid = read_input(carts);

  crash_coordinate(grid, carts);

  return 0;
}
