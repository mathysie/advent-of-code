#include <algorithm>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct cart {
  unsigned int x;
  unsigned int y;
  char track;
  int turn;
};

bool cart_sort(cart x, cart y) { return x.y != y.y ? x.y < y.y : x.x < y.x; }

vector<vector<char>> read_input(forward_list<cart> &carts) {
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

void crash_coordinate(vector<vector<char>> &grid, forward_list<cart> &carts) {
  while (true) {
    for (auto &cart : carts) {
      char cur = grid[cart.y][cart.x];
      grid[cart.y][cart.x] = cart.track;

      if (cur == '>') {
        cart.track = grid[cart.y][cart.x + 1];
        cart.x++;

        if (grid[cart.y][cart.x] == '\\') {
          grid[cart.y][cart.x] = 'v';
        } else if (grid[cart.y][cart.x] == '/') {
          grid[cart.y][cart.x] = '^';
        } else if (grid[cart.y][cart.x] == '+') {
          switch (cart.turn % 3) {
          case 0:
            grid[cart.y][cart.x] = '^';
            break;
          case 1:
            grid[cart.y][cart.x] = '>';
            break;
          case 2:
            grid[cart.y][cart.x] = 'v';
            break;
          }
          cart.turn++;
        } else if (grid[cart.y][cart.x] == '-') {
          grid[cart.y][cart.x] = '>';
        } else {
          cout << cart.x << "," << cart.y << endl;
          return;
        }

      } else if (cur == 'v') {
        cart.track = grid[cart.y + 1][cart.x];
        cart.y++;

        if (grid[cart.y][cart.x] == '\\') {
          grid[cart.y][cart.x] = '>';
        } else if (grid[cart.y][cart.x] == '/') {
          grid[cart.y][cart.x] = '<';
        } else if (grid[cart.y][cart.x] == '+') {
          switch (cart.turn % 3) {
          case 0:
            grid[cart.y][cart.x] = '>';
            break;
          case 1:
            grid[cart.y][cart.x] = 'v';
            break;
          case 2:
            grid[cart.y][cart.x] = '<';
            break;
          }
          cart.turn++;
        } else if (grid[cart.y][cart.x] == '|') {
          grid[cart.y][cart.x] = 'v';
        } else {
          cout << cart.x << "," << cart.y << endl;
          return;
        }

      } else if (cur == '<') {
        cart.track = grid[cart.y][cart.x - 1];
        cart.x--;

        if (grid[cart.y][cart.x] == '\\') {
          grid[cart.y][cart.x] = '^';
        } else if (grid[cart.y][cart.x] == '/') {
          grid[cart.y][cart.x] = 'v';
        } else if (grid[cart.y][cart.x] == '+') {
          switch (cart.turn % 3) {
          case 0:
            grid[cart.y][cart.x] = 'v';
            break;
          case 1:
            grid[cart.y][cart.x] = '<';
            break;
          case 2:
            grid[cart.y][cart.x] = '^';
            break;
          }
          cart.turn++;
        } else if (grid[cart.y][cart.x] == '-') {
          grid[cart.y][cart.x] = '<';
        } else {
          cout << cart.x << "," << cart.y << endl;
          return;
        }

      } else if (cur == '^') {
        cart.track = grid[cart.y - 1][cart.x];
        cart.y--;

        if (grid[cart.y][cart.x] == '\\') {
          grid[cart.y][cart.x] = '<';
        } else if (grid[cart.y][cart.x] == '/') {
          grid[cart.y][cart.x] = '>';
        } else if (grid[cart.y][cart.x] == '+') {
          switch (cart.turn % 3) {
          case 0:
            grid[cart.y][cart.x] = '<';
            break;
          case 1:
            grid[cart.y][cart.x] = '^';
            break;
          case 2:
            grid[cart.y][cart.x] = '>';
            break;
          }
          cart.turn++;
        } else if (grid[cart.y][cart.x] == '|') {
          grid[cart.y][cart.x] = '^';
        } else {
          cout << cart.x << "," << cart.y << endl;
          return;
        }
      }
    }

    carts.sort(cart_sort);
  }
}

int main() {
  forward_list<cart> carts;
  vector<vector<char>> grid = read_input(carts);

  crash_coordinate(grid, carts);

  return 0;
}
