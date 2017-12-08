import numpy as np


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


def bottom_program(tree):
    programs = count_programs(tree)

    return min(programs, key=programs.get)


def get_weights(tree):
    weights = dict()

    for program in tree:
        weights[program] = weight_subprogram(program, tree)

    return weights


def weight_subprogram(program, tree):
    weight = tree[program][0]
    for i in range(0, len(tree[program][1])):
        weight += weight_subprogram(tree[program][1][i], tree)

    return weight


def first_disbalance(tree, weights):
    for program in tree:
        if (len(tree[program][1]) > 0):
            for i in range(1, len(tree[program][1])):
                if (weights[tree[program][1][i]] != weights[tree[program][1][0]]):
                    return [program, abs(weights[tree[program][1][i]] - weights[tree[program][1][0]])]


def wrong_program(tree, weights, start):
    for i in range(1, len(tree[start][1])):
        if (weights[tree[start][1][i]] != weights[tree[start][1][0]]):
            if (i == 1 and weights[tree[start][1][2]] != weights[tree[start][1][0]]):
                start = tree[start][1][0]
                return wrong_program(tree, weights, start)
            else:
                start = tree[start][1][i]
                return wrong_program(tree, weights, start)

    return start


def get_intended_weight(tree):
    weights = get_weights(tree)
    start = first_disbalance(tree, weights)
    end_program = wrong_program(tree, weights, start[0])
    print "Einde: ", end_program

    return tree[end_program][0] - start[1]


tree = read_input()
print bottom_program(tree)
print get_intended_weight(tree)
