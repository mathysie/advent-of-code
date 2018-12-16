#include <array>
#include <fstream>
#include <iostream>

using namespace std;

bool is_addr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] + reg[op[1]];

  return temp == res;
}

bool is_addi(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] + op[1];

  return temp == res;
}

bool is_mulr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] * reg[op[1]];

  return temp == res;
}

bool is_muli(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] * op[1];

  return temp == res;
}

bool is_banr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] & reg[op[1]];

  return temp == res;
}

bool is_bani(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] & op[1];

  return temp == res;
}

bool is_borr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] | reg[op[1]];

  return temp == res;
}

bool is_bori(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] | op[1];

  return temp == res;
}

bool is_setr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]];

  return temp == res;
}

bool is_seti(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = op[0];

  return temp == res;
}

bool is_gtir(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = op[0] > reg[op[1]];

  return temp == res;
}

bool is_gtri(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] > op[1];

  return temp == res;
}

bool is_gtrr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] > reg[op[1]];

  return temp == res;
}

bool is_eqir(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = op[0] == reg[op[1]];

  return temp == res;
}

bool is_eqri(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] == op[1];

  return temp == res;
}

bool is_eqrr(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  array<int, 4> temp = reg;
  temp[op[2]] = reg[op[0]] == reg[op[1]];

  return temp == res;
}

bool behave_like_three(array<int, 4> reg, array<int, 3> op, array<int, 4> res) {
  int counter = 0;

  counter += is_addr(reg, op, res);
  counter += is_addi(reg, op, res);
  counter += is_mulr(reg, op, res);
  counter += is_muli(reg, op, res);
  counter += is_banr(reg, op, res);
  counter += is_bani(reg, op, res);
  counter += is_borr(reg, op, res);
  counter += is_bori(reg, op, res);
  counter += is_setr(reg, op, res);
  counter += is_seti(reg, op, res);
  counter += is_gtir(reg, op, res);
  counter += is_gtri(reg, op, res);
  counter += is_gtrr(reg, op, res);
  counter += is_eqir(reg, op, res);
  counter += is_eqri(reg, op, res);
  counter += is_eqrr(reg, op, res);

  return counter >= 3;
}

int main() {
  fstream file("input.txt");
  string line;

  int counter = 0;

  while (getline(file, line)) {
    array<int, 4> reg;
    sscanf(line.c_str(), "Before: [%d, %d, %d, %d]", &reg[0], &reg[1], &reg[2],
           &reg[3]);

    getline(file, line);
    array<int, 3> op;
    sscanf(line.c_str(), "%*d %d %d %d", &op[0], &op[1], &op[2]);

    getline(file, line);
    array<int, 4> res;
    sscanf(line.c_str(), "After:  [%d, %d, %d, %d]", &res[0], &res[1], &res[2],
           &res[3]);

    getline(file, line);

    counter += behave_like_three(reg, op, res);
  }

  file.close();

  cout << counter << endl;

  return 0;
}
