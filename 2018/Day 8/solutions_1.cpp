#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct node {
  int childs;
  int metadatas;
  int sum = 0;
  vector<node *> child_nodes = {};
  node *parent;
};

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

void create_node(node *current, vector<int> input, int &i) {
  current->childs = input[i], i++;
  current->metadatas = input[i], i++;
  for (int j = 0; j < current->childs; j++) {
    node *child = new node;
    child->parent = current;
    current->child_nodes.push_back(child);
    create_node(child, input, i);
  }
  for (int j = 0; j < current->metadatas; j++) {
    current->sum += input[i];
    i++;
  }
}

node *build_tree(vector<int> input) {
  node *start = new node;
  start->parent = NULL;
  int i = 0;

  create_node(start, input, i);

  return start;
}

void compute_sum(node *current, int &sum) {
  sum += current->sum;
  for (auto child : current->child_nodes) {
    compute_sum(child, sum);
  }

  delete current;
}

int main() {
  vector<int> input = read_input();
  node *start = build_tree(input);
  int sum = 0;
  compute_sum(start, sum);
  cout << sum << endl;

  return 0;
}
