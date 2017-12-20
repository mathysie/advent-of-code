def read_input():
    network = []
    while True:
        try:
            line = list(input())
            network.append(line)
        except EOFError:
            break

    return network


def read_letters():
    letter = []
    i = 0
    j = 0
    d = True  # positive or negative direction
    vert = True

    for k in range(0, len(network[0])):
        if network[0][k] == "|":
            j = k
            break

    while True:
        if (network[i][j] == "+"):
            if vert:
                if (network[i][j + 1] == "-"):
                    d = True
                    j += 1
                elif (network[i][j - 1] == "-"):
                    d = False
                    j -= 1
            else:
                if (network[i + 1][j] == "|"):
                    d = True
                    i += 1
                elif (network[i - 1][j] == "|"):
                    d = False
                    i -= 1
            vert = not vert
            continue

        if (network[i][j].isalpha()):
            letter.append(network[i][j])

        if (network[i][j] == " "):
            break

        if d and vert:
            i += 1
        elif not d and vert:
            i -= 1
        elif d and not vert:
            j += 1
        elif not d and not vert:
            j -= 1

    return "".join(letter)


network = read_input()
print(read_letters())
