import numpy as np


def bottom_program(programs):
    return min(programs, key=programs.get)


def count_program(counter, program):
    if (program in counter):
        counter[program] += 1
    else:
        counter[program] = 1


def count_programs():
    counter = dict()

    while True:
        try:
            line = raw_input().split(' ')
            count_program(counter, line[0])

            if (len(line) > 2):
                for i in range(3, len(line) - 1):
                    count_program(counter, line[i][:-1])
                count_program(counter, line[len(line) - 1])

        except EOFError:
            break

    return bottom_program(counter)


print count_programs()
