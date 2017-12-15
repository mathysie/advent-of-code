def read_input():
    startA = int(raw_input().split(" ")[-1])
    startB = int(raw_input().split(" ")[-1])
    return [startA, startB]


def calc_valueA(value):
    return (value * 16807) % 2147483647


def calc_valueB(value):
    return (value * 48271) % 2147483647


def is_pair(valueA, valueB):
    return valueA % (2 ** 16) == valueB % (2 ** 16)


def judge_count(start):
    count = 0
    N = 4 * 10 ** 7
    valueA = start[0]
    valueB = start[1]

    for i in range(0, N):
        valueA = calc_valueA(valueA)
        valueB = calc_valueB(valueB)
        if is_pair(valueA, valueB):
            count += 1

    return count


def new_judge_count(start):
    count = 0
    N = 5 * 10 ** 6
    valueA = start[0]
    valueB = start[1]
    values = [[], []]

    while (len(values[0]) < N):
        valueA = calc_valueA(valueA)
        if valueA % 4 == 0:
            values[0].append(valueA)

    while (len(values[1]) < N):
        valueB = calc_valueB(valueB)
        if valueB % 8 == 0:
            values[1].append(valueB)

    for i in range(0, N):
        if is_pair(values[0][i], values[1][i]):
            count += 1

    return count

start = read_input()
print judge_count(start)
print new_judge_count(start)
