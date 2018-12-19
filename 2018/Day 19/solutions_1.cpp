#include <array>
#include <fstream>
#include <iostream>
#include <regex>
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

opcode parse(string s) {
  if (s == "addr")
    return addr;
  if (s == "addi")
    return addi;
  if (s == "mulr")
    return mulr;
  if (s == "muli")
    return muli;
  if (s == "banr")
    return banr;
  if (s == "bani")
    return bani;
  if (s == "borr")
    return borr;
  if (s == "bori")
    return bori;
  if (s == "setr")
    return setr;
  if (s == "seti")
    return seti;
  if (s == "gtir")
    return gtir;
  if (s == "gtri")
    return gtri;
  if (s == "gtrr")
    return gtrr;
  if (s == "eqir")
    return eqir;
  if (s == "eqri")
    return eqri;
  if (s == "eqrr")
    return eqrr;
  return fout;
}

int do_instruction(unsigned int x, vector<array<int, 4>> instr,
                   array<int, 6> reg) {
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
    regex pattern("([a-z]{4}) ([0-9]+) ([0-9]+) ([0-9]+)");
    cmatch matches;
    regex_match(line.c_str(), matches, pattern);
    array<int, 4> rule = {parse(matches[1].str()), stoi(matches[2].str()),
                          stoi(matches[3].str()), stoi(matches[4].str())};
    instr.push_back(rule);
  }

  file.close();

  return instr;
}

int run_program(unsigned int ip, vector<array<int, 4>> instr) {
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
