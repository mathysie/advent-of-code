#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <vector>

using namespace std;

enum opcode {
  addr,
  addi,
  mulr,
  muli,
  banr,
  bani,
  borr,
  bori,
  setr,
  seti,
  gtir,
  gtri,
  gtrr,
  eqir,
  eqri,
  eqrr,
  fout
};

opcode parse(char *s) {
  if (strcmp(s, "addr") == 0)
    return addr;
  if (strcmp(s, "addi") == 0)
    return addi;
  if (strcmp(s, "mulr") == 0)
    return mulr;
  if (strcmp(s, "muli") == 0)
    return muli;
  if (strcmp(s, "banr") == 0)
    return banr;
  if (strcmp(s, "bani") == 0)
    return bani;
  if (strcmp(s, "borr") == 0)
    return borr;
  if (strcmp(s, "bori") == 0)
    return bori;
  if (strcmp(s, "setr") == 0)
    return setr;
  if (strcmp(s, "seti") == 0)
    return seti;
  if (strcmp(s, "gtir") == 0)
    return gtir;
  if (strcmp(s, "gtri") == 0)
    return gtri;
  if (strcmp(s, "gtrr") == 0)
    return gtrr;
  if (strcmp(s, "eqir") == 0)
    return eqir;
  if (strcmp(s, "eqri") == 0)
    return eqri;
  if (strcmp(s, "eqrr") == 0)
    return eqrr;
  return fout;
}

int do_instruction(unsigned int x, const vector<array<int, 4>> &instr,
                   const array<int, 6> &reg) {
  switch (instr[x][0]) {
  case addr:
    return reg[instr[x][1]] + reg[instr[x][2]];
  case addi:
    return reg[instr[x][1]] + instr[x][2];
  case mulr:
    return reg[instr[x][1]] * reg[instr[x][2]];
  case muli:
    return reg[instr[x][1]] * instr[x][2];
  case banr:
    return reg[instr[x][1]] & reg[instr[x][2]];
  case bani:
    return reg[instr[x][1]] & instr[x][2];
  case borr:
    return reg[instr[x][1]] | reg[instr[x][2]];
  case bori:
    return reg[instr[x][1]] | instr[x][2];
  case setr:
    return reg[instr[x][1]];
  case seti:
    return instr[x][1];
  case gtir:
    return instr[x][1] > reg[instr[x][2]];
  case gtri:
    return reg[instr[x][1]] > instr[x][2];
  case gtrr:
    return reg[instr[x][1]] > reg[instr[x][2]];
  case eqir:
    return instr[x][1] == reg[instr[x][2]];
  case eqri:
    return reg[instr[x][1]] == instr[x][2];
  case eqrr:
    return reg[instr[x][1]] == reg[instr[x][2]];
  }

  return -1;
}

int getIP(ifstream &file) {
  string line;
  int ip;
  getline(file, line);
  sscanf(line.c_str(), "#ip %d", &ip);

  return ip;
}

vector<array<int, 4>> read_instructions(ifstream &file) {
  string line;
  vector<array<int, 4>> instr;

  while (getline(file, line)) {
    istringstream stream(line);
    char code[5];
    int x, y, z;
    stream >> code >> x >> y >> z;
    array<int, 4> rule = {parse(code), x, y, z};
    instr.push_back(rule);
  }

  file.close();

  return instr;
}

int run_program(unsigned int ip, const vector<array<int, 4>> &instr) {
  array<int, 6> reg = {0, 0, 0, 0, 0, 0};
  unsigned int x = reg[ip];

  while (x < instr.size()) {
    reg[instr[x][3]] = do_instruction(x, instr, reg);
    reg[ip]++;
    x = reg[ip];
  }

  return reg[0];
}

int main() {
  ifstream file("input.txt");
  int ip = getIP(file);
  vector<array<int, 4>> instr = read_instructions(file);

  cout << run_program(ip, instr) << endl;

  return 0;
}
