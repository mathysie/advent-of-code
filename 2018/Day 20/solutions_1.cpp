#include <algorithm>
#include <chrono>
#include <climits>
#include <deque>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct node {
  string route;
  node *parent;
  int level;
  vector<node *> children;
};

void display_time(const auto &start) {
  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  cout << duration.count() << " milliseconds" << endl;
}

string read_input() {
  ifstream file("input.txt");
  string line;
  file >> line;

  return line;
}

node *insert_child(node *cur, int level) {
  node *child = new node;
  child->parent = cur;
  child->level = level;
  cur->children.push_back(child);

  return child;
}

void insert_node(node *cur, auto it, int level) {
  while (*it != '(' && *it != ')' && *it != '|' && *it != '$') {
    cur->route.push_back(*it);
    it++;
  }

  if (*it == '(') {
    it++;
    node *child = insert_child(cur, level + 1);
    insert_node(child, it, level + 1);
  } else if (*it == ')') {
    it++;
    if (cur->route.empty()) {
      node *child = cur->parent->children[0];
      insert_node(child, it, level - 1);
    } else {
      for (node *child : cur->parent->children) {
        insert_node(child, it, level - 1);
      }
    }
  } else if (*it == '|' && cur == *cur->parent->children.begin()) {
    it++;
    while (cur->level != level) {
      cur = cur->parent;
    }
    node *child = insert_child(cur->parent, level);
    insert_node(child, it, level);
  }
}

node *build_tree(string line) {
  auto it = line.begin();
  it++;
  node *head = new node;
  head->level = 0;
  node *cur = head;

  insert_node(cur, it, 0);

  return head;
}

void delete_tree(node *cur) {
  for (auto child : cur->children) {
    delete_tree(child);
  }

  delete cur;
}

void print_tree(node *cur, int level) {
  for (int i = 0; i < cur->level; i++) {
    cout << "\t";
  }
  cout << cur->route << endl;
  for (auto child : cur->children) {
    print_tree(child, level + 1);
  }
}

void print_grid(const deque<deque<int>> &grid) {
  for (auto line : grid) {
    for (auto l : line) {
      if (l == -1) {
        cout << '#';
        // } else if (l < 100) {
        //   cout << l % 10;
      } else {
        cout << '.';
      }
    }
    cout << endl;
  }
}

void build_step(deque<deque<int>> &grid, node *cur, int x, int y,
                pair<int, int> &start) {
  for (auto c : cur->route) {
    switch (c) {
    case 'N':
      if (x == 1) {
        for (int i = 0; i < 2; i++) {
          deque<int> line(grid[0].size());
          fill(line.begin(), line.end(), -1);
          grid.push_front(line);
        }
        x += 2;
        start.first += 2;
      }
      grid[x - 1][y] = 0;
      grid[x - 2][y] = INT_MAX;
      x -= 2;
      break;
    case 'E':
      if (y == (int)grid[x].size() - 2) {
        for (auto &line : grid) {
          line.push_back(-1);
          line.push_back(-1);
        }
      }
      grid[x][y + 1] = 0;
      grid[x][y + 2] = INT_MAX;
      y += 2;
      break;
    case 'S':
      if (x == (int)grid.size() - 2) {
        for (int i = 0; i < 2; i++) {
          deque<int> line(grid[0].size());
          fill(line.begin(), line.end(), -1);
          grid.push_back(line);
        }
      }
      grid[x + 1][y] = 0;
      grid[x + 2][y] = INT_MAX;
      x += 2;
      break;
    case 'W':
      if (y == 1) {
        for (auto &line : grid) {
          line.push_front(-1);
          line.push_front(-1);
        }
        start.second += 2;
        y += 2;
      }
      grid[x][y - 1] = 0;
      grid[x][y - 2] = INT_MAX;
      y -= 2;
      break;
    }
  }

  int deltax = x - start.first;
  int deltay = y - start.second;
  for (auto child : cur->children) {
    build_step(grid, child, start.first + deltax, start.second + deltay, start);
  }
}

deque<deque<int>> build_grid(node *head, pair<int, int> &start) {
  start = make_pair(1, 1);
  deque<deque<int>> grid = {{-1, -1, -1}, {-1, 0, -1}, {-1, -1, -1}};
  build_step(grid, head, 1, 1, start);

  return grid;
}

void walk_grid(deque<deque<int>> &grid, pair<int, int> cur, int &max) {
  int dist = grid[cur.first][cur.second];
  if (dist > max) {
    max = dist;
  }

  vector<pair<int, int>> updated;
  if (grid[cur.first - 1][cur.second] != -1 &&
      grid[cur.first - 2][cur.second] > dist + 1) {
    grid[cur.first - 2][cur.second] = dist + 1;
    updated.push_back({cur.first - 2, cur.second});
  }
  if (grid[cur.first + 1][cur.second] != -1 &&
      grid[cur.first + 2][cur.second] > dist + 1) {
    grid[cur.first + 2][cur.second] = dist + 1;
    updated.push_back({cur.first + 2, cur.second});
  }
  if (grid[cur.first][cur.second + 1] != -1 &&
      grid[cur.first][cur.second + 2] > dist + 1) {
    grid[cur.first][cur.second + 2] = dist + 1;
    updated.push_back({cur.first, cur.second + 2});
  }
  if (grid[cur.first][cur.second - 1] != -1 &&
      grid[cur.first][cur.second - 2] > dist + 1) {
    grid[cur.first][cur.second - 2] = dist + 1;
    updated.push_back({cur.first, cur.second - 2});
  }

  for (auto update : updated) {
    walk_grid(grid, update, max);
  }
}

int furthest_room(deque<deque<int>> &grid, pair<int, int> start) {
  int max = 0;
  grid[start.first][start.second] = 0;
  walk_grid(grid, start, max);

  return max;
}

int main() {
  auto start = chrono::high_resolution_clock::now();
  string line = read_input();

  node *head = build_tree(line);

  pair<int, int> begin;
  deque<deque<int>> grid = build_grid(head, begin);

  print_tree(head, 0);

  delete_tree(head);

  print_grid(grid);

  cout << furthest_room(grid, begin) << endl;

  display_time(start);
  return 0;
}
