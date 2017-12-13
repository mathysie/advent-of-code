def read_input():
    layers = dict()
    while True:
        try:
            line = raw_input().split(":")
            layers[int(line[0])] = int(line[1])
        except EOFError:
            break

    return layers


def calc_severity(layers):
    severity = 0

    for i in range(0, max(layers) + 1):
        if i in layers:
            N = 2 * layers[i] - 2
            if i % N == 0:
                severity += layers[i] * i

    return severity


layers = read_input()
print calc_severity(layers)
