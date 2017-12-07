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
print tree
