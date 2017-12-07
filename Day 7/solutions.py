import numpy as np


def bottom_program(tree):
    programs = count_programs(tree)

    return min(programs, key=programs.get)


def count_program(counter, program):
    if (program in counter):
        counter[program] += 1
    else:
        counter[program] = 1


def count_programs(tree):
    counter = dict()

    for program in tree:
        count_program(counter, program)

        if (len(tree[program][1]) > 0):
            for i in range(0, len(tree[program][1])):
                count_program(counter, tree[program][1][i])

    return counter

def weight_subprogram(program, tree):
    weight = tree[program][0]
    for i in range(0, len(tree[program][1])):
        weight += weight_subprogram(tree[program][1][i], tree)

    return weight


def get_wrong_weight(tree):
    weights = dict()
    for program in tree:
        weights[program] = weight_subprogram(program, tree)

    for program in tree:
        if (len(tree[program][1]) > 0):
            for i in range(1, len(tree[program][1])):
                if (weights[tree[program][1][i]] != weights[tree[program][1][0]]):
                    print program
                    for j in tree[program][1]:
                        print weights[j]


def read_input():
    weights = dict()
    while True:
        try:
            line = raw_input().split(' ')
            if (len(line) > 2):
                subs = []
                for i in range(3, len(line) - 1):
                    subs.append(line[i][:-1])
                subs.append(line[len(line) - 1])
                weights[line[0]] = [int(line[1][1:-1]), subs]
            else:
                weights[line[0]] = [int(line[1][1:-1]), []]
        except EOFError:
            break

    return weights


tree = read_input()
print bottom_program(tree)
get_wrong_weight(tree)
