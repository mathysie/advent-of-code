def read_input():
    pipes = dict()
    while True:
        try:
            line = raw_input().split(" <-> ")
            pipes[int(line[0])] = set([int(i) for i in line[1].split(",")])
        except EOFError:
            break

    return pipes


def count_programs(pipes):
    group = set([0])
    new = set(pipes[0])

    while (len(new) > 0):
        temp = set(new)
        for i in new:
            temp |= pipes[i] - group
            group |= pipes[i]
            temp.remove(i)
        new = set(temp)

    return len(group)


pipes = read_input()
print count_programs(pipes)
