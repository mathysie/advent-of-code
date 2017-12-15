def read_input():
    startA = int(raw_input().split(" ")[-1])
    startB = int(raw_input().split(" ")[-1])
    return [startA, startB]


def judge_count(start):
    count = 0
    valueA = start[0]
    valueB = start[1]

    for i in range(0, 4 * 10 ** 7):
        valueA = (valueA * 16807) % 2147483647
        valueB = (valueB * 48271) % 2147483647
        if (valueA % (2 ** 16) == valueB % (2 ** 16)):
            count += 1

    return count

start = read_input()
print judge_count(start)
