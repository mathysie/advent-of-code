#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

array<int, 4> addr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] + reg[op[2]];

  return temp;
}

bool is_addr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return addr(reg, op) == res;
}

array<int, 4> addi(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] + op[2];

  return temp;
}

bool is_addi(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return addi(reg, op) == res;
}

array<int, 4> mulr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] * reg[op[2]];

  return temp;
}

bool is_mulr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return mulr(reg, op) == res;
}

array<int, 4> muli(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] * op[2];

  return temp;
}

bool is_muli(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return muli(reg, op) == res;
}

array<int, 4> banr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] & reg[op[2]];

  return temp;
}

bool is_banr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return banr(reg, op) == res;
}

array<int, 4> bani(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] & op[2];

  return temp;
}

bool is_bani(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return bani(reg, op) == res;
}

array<int, 4> borr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] | reg[op[2]];

  return temp;
}

bool is_borr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return borr(reg, op) == res;
}

array<int, 4> bori(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] | op[2];

  return temp;
}

bool is_bori(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return bori(reg, op) == res;
}

array<int, 4> setr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]];

  return temp;
}

bool is_setr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return setr(reg, op) == res;
}

array<int, 4> seti(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = op[1];

  return temp;
}

bool is_seti(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return seti(reg, op) == res;
}

array<int, 4> gtir(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = op[1] > reg[op[2]];

  return temp;
}

bool is_gtir(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return gtir(reg, op) == res;
}

array<int, 4> gtri(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] > op[2];

  return temp;
}

bool is_gtri(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return gtri(reg, op) == res;
}

array<int, 4> gtrr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] > reg[op[2]];

  return temp;
}

bool is_gtrr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return gtrr(reg, op) == res;
}

array<int, 4> eqir(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = op[1] == reg[op[2]];

  return temp;
}

bool is_eqir(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return eqir(reg, op) == res;
}

array<int, 4> eqri(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] == op[2];

  return temp;
}

bool is_eqri(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return eqri(reg, op) == res;
}

array<int, 4> eqrr(array<int, 4> reg, array<int, 4> op) {
  array<int, 4> temp = reg;
  temp[op[3]] = reg[op[1]] == reg[op[2]];

  return temp;
}

bool is_eqrr(array<int, 4> reg, array<int, 4> op, array<int, 4> res) {
  return eqrr(reg, op) == res;
}

void detect_programs(array<int, 4> reg, array<int, 4> op, array<int, 4> res,
                     array<vector<int>, 16> &candidates) {
  vector<int> temp = candidates[op[0]];
  vector<int> pos;

  if (is_addi(reg, op, res)) {
    pos.push_back(1);
  }
  if (is_mulr(reg, op, res)) {
    pos.push_back(2);
  }
  if (is_muli(reg, op, res)) {
    pos.push_back(3);
  }
  if (is_banr(reg, op, res)) {
    pos.push_back(4);
  }
  if (is_bani(reg, op, res)) {
    pos.push_back(5);
  }
  if (is_borr(reg, op, res)) {
    pos.push_back(6);
  }
  if (is_bori(reg, op, res)) {
    pos.push_back(7);
  }
  if (is_setr(reg, op, res)) {
    pos.push_back(8);
  }
  if (is_seti(reg, op, res)) {
    pos.push_back(9);
  }
  if (is_gtir(reg, op, res)) {
    pos.push_back(10);
  }
  if (is_gtri(reg, op, res)) {
    pos.push_back(11);
  }
  if (is_gtrr(reg, op, res)) {
    pos.push_back(12);
  }
  if (is_eqir(reg, op, res)) {
    pos.push_back(13);
  }
  if (is_eqri(reg, op, res)) {
    pos.push_back(14);
  }
  if (is_eqrr(reg, op, res)) {
    pos.push_back(15);
  }
  if (is_addr(reg, op, res)) {
    pos.push_back(16);
  }

  vector<int> temp2(16);

  set_intersection(temp.begin(), temp.end(), pos.begin(), pos.end(), temp2.begin());
  temp2.resize(distance(temp2.begin(), find(temp2.begin(), temp2.end(), 0)));
  candidates[op[0]] = temp2;
}

void fill_opcodes(array<int, 16> &opcodes) {
  fstream file("input.txt");
  string line;
  array<vector<int>, 16> candidates;
  candidates.fill(vector<int> {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15, 16});

  while (getline(file, line)) {
    array<int, 4> reg;
    sscanf(line.c_str(), "Before: [%d, %d, %d, %d]", &reg[0], &reg[1], &reg[2],
           &reg[3]);

    getline(file, line);
    array<int, 4> op;
    sscanf(line.c_str(), "%d %d %d %d", &op[0], &op[1], &op[2], &op[3]);

    getline(file, line);
    array<int, 4> res;
    sscanf(line.c_str(), "After:  [%d, %d, %d, %d]", &res[0], &res[1], &res[2],
           &res[3]);

    getline(file, line);

    detect_programs(reg, op, res, candidates);
  }

  for (int i = 0; i < 16; i++) {
    opcodes[i] = candidates[i][0];
  }

  file.close();
}

void run_instruction(array<int, 4> & reg, array<int, 4> op, array<int, 16> opcodes) {
  switch (opcodes[op[0]]) {
    case 1:
      reg = addi(reg, op);
      break;
    case 2:
      reg = mulr(reg, op);
      break;
    case 3:
      reg = muli(reg, op);
      break;
    case 4:
      reg = banr(reg, op);
      break;
    case 5:
      reg = bani(reg, op);
      break;
    case 6:
      reg = borr(reg, op);
      break;
    case 7:
      reg = bori(reg, op);
      break;
    case 8:
      reg = setr(reg, op);
      break;
    case 9:
      reg = seti(reg, op);
      break;
    case 10:
      reg = gtir(reg, op);
      break;
    case 11:
      reg = gtri(reg, op);
      break;
    case 12:
      reg = gtrr(reg, op);
      break;
    case 13:
      reg = eqir(reg, op);
      break;
    case 14:
      reg = eqri(reg, op);
      break;
    case 15:
      reg = eqrr(reg, op);
      break;
    case 16:
      reg = addr(reg, op); 
      break;
  }
}

int run_program(array<int, 16> opcodes) {
  fstream file("program.txt");
  string line;
  array<int, 4> reg = {0, 0, 0, 0};

  while (getline(file, line)) {
    array<int, 4> op;
    sscanf(line.c_str(), "%d %d %d %d", &op[0], &op[1], &op[2], &op[3]);
    run_instruction(reg, op, opcodes);
  }

  file.close();

  return reg[0];
}

int main() {
  array<int, 16> opcodes;
  opcodes.fill(-1);
  fill_opcodes(opcodes);

  for (auto code: opcodes) {
    cout << code << " ";
  }
  cout << endl;

  int x = run_program(opcodes);

  cout << x << endl;

  return 0;
}
