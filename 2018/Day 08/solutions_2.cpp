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
  int value = 0;
  vector<node *> child_nodes = {};
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
    current->child_nodes.push_back(child);
    create_node(child, input, i);
  }

  for (int j = 0; j < current->metadatas; j++) {
    if (current->childs == 0)
      current->value += input[i];
    else if (current->childs >= input[i]) {
      current->value += current->child_nodes[input[i] - 1]->value;
    }
    i++;
  }
}

node *build_tree(vector<int> input) {
  node *start = new node;
  int i = 0;

  create_node(start, input, i);

  return start;
}

void delete_tree(node *current) {
  for (auto child : current->child_nodes) {
    delete_tree(child);
  }

  delete current;
}

int main() {
  vector<int> input = read_input();
  node *start = build_tree(input);
  cout << start->value << endl;
  delete_tree(start);

  return 0;
}
