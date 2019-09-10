def part_1():
    buffer = [0]
    current = 0

    for i in range(1, 2018):
        current = (current + steps) % len(buffer) + 1
        buffer.insert(current, i)

    return buffer[buffer.index(2017) + 1]


def part_2():
    current = 0
    value = 0

    for i in range(1, 5 * 10 ** 7):
        current = (current + steps) % i + 1
        if current == 1:
            value = i

    return value

steps = int(raw_input())
print part_1()
print part_2()
