def read_input():
    pipes = dict()
    while True:
        try:
            line = raw_input().split(" <-> ")
            pipes[int(line[0])] = set([int(i) for i in line[1].split(",")])
        except EOFError:
            break

    return pipes


def count_groups(pipes):
    print len(form_group(pipes, 0))

    group_count = 0
    numbers = set(range(0, len(pipes)))

    while len(numbers) > 0:
        numbers -= form_group(pipes, list(numbers)[0])
        group_count += 1

    return group_count


def form_group(pipes, start):
    group = set([start])
    new = set(pipes[start])

    while (len(new) > 0):
        temp = set(new)
        for i in iter(new):
            temp |= pipes[i] - group
            group |= pipes[i] | set([i])
            temp.remove(i)
        new = set(temp)

    return group


pipes = read_input()
print count_groups(pipes)
